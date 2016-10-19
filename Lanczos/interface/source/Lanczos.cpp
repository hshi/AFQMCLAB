//
// Created by boruoshihao on 9/24/16.
//

#include "../include/Lanczos.h"

using namespace tensor_hao;

using namespace std;

Lanczos::Lanczos(const ModelInterface &modelInterface)
{
    model = &modelInterface;
    wfSize = model->getWfSize();
}

void Lanczos::randomInitWf()
{
    LanczosBasisWf wfNew(wfSize);
    wfNew.randomFill();
    eigenstates.push_back( move(wfNew) );
    projectWaveFunction( eigenstates.back() );
}

void Lanczos::readInitWf(const string &filename)
{
    LanczosBasisWf wfNew(wfSize);
    wfNew.read(filename);
    eigenstates.push_back( move(wfNew) );
    projectWaveFunction( eigenstates.back() );

}

void Lanczos::readConvergedWfs(size_t numberOfWaveFunctions)
{
    string filename;
    eigenstates.resize(numberOfWaveFunctions);
    for(size_t i = 0; i < numberOfWaveFunctions; ++i)
    {
        filename="eigenstate_" + to_string(i) +".dat";
        eigenstates[i].resize(wfSize);
        eigenstates[i].read(filename);
    }
}

void Lanczos::writeWf(const string &filename) const
{
    const LanczosBasisWf &currentState = eigenstates.back();
    currentState.write(filename);
}

void Lanczos::writeAllWfs(size_t startIndex) const
{
    string filename;
    for(size_t i = startIndex; i < eigenstates.size(); ++i)
    {
        filename="eigenstate_" + to_string(i) +".dat";
        eigenstates[i].write(filename);
    }
}

void Lanczos::findEigen(const size_t L, LanczosParam lanczosParam)
{
    eigenstates.reserve( eigenstates.size() + L );
    for(size_t i = 0; i < L; ++i)
    {
        randomInitWf();
        FindOneEigen(lanczosParam);
    }
}

void Lanczos::FindOneEigen(LanczosParam lanczosParam)
{
    vector<double> a, b, lanczosMatrixVector;
    double energy, energyBackup;

    for(size_t lanIndex = 0; lanIndex < lanczosParam.maxLoop; ++lanIndex)
    {
        tie( a, b ) = getLanczosMatrix(lanczosParam.matrixSize, lanczosParam.accuracy, lanczosParam.litForProjection);
        energyBackup = a[0];

        if( a.size() == 1 )
        {
            cout<<setprecision(16)<<"\nSUCCESS! Find Eigenstate #" << eigenstates.size() <<" : "<<a[0]<<"\n"<<endl;
            return;
        }

        tie( energy, lanczosMatrixVector ) = diagonalizeLanczosMatrix(a, b);

        cout<<setprecision(16)<<"Variational energy for "<< eigenstates.size()<<" is "<<energy<<endl;

        if( energyBackup < energy )
        {
            if(lanczosParam.convergeFlag == 'E')
            {
                cout<<setprecision(16)<<"\nSUCCESS! Find Eigenstate #" << eigenstates.size() <<" : "<<a[0]<<"\n"<< endl;
                return;
            }
            else if(lanczosParam.convergeFlag == 'W')
            {
                cout<<"Energy is converged! Wait for the convergence of wave function!"<<endl;
            }
        }

        getNewEigenstate(a, b, lanczosMatrixVector);
    }

    throw LanczosNotConverge_error("Lanczos does not converge, increase lanczos maxloop or lanczos matrixSize!");
}

tuple<vector<double>, vector<double> > Lanczos::getLanczosMatrix(size_t L, double accuracy, double litForProjection)
{
    wfTwo = eigenstates.back();

    vector<double> a, b;

    b.push_back(0);

    for(size_t i = 0; i < (L-1); ++i)
    {
        a.push_back( getLanczosDiagonalElement() );
        b.push_back( getLanczosOffdiagonalElement( a[i], b[i]) );

        recurseWaveFunctions();

        if( abs( b.back() ) < accuracy ) break;
        if( abs( b.back() ) < litForProjection ) projectWaveFunction(wfTwo);
    }

    if( abs( b.back() ) < accuracy ) b.pop_back();
    else a.push_back( getLanczosDiagonalElement() );

    return make_tuple( move(a),  move(b) );
}

double Lanczos::getLanczosDiagonalElement()
{
    model->applyHToWf(wfTwo, wfThree);
    complex<double> a = wfThree.calculateOverlapWith(wfTwo);
    return a.real();
}

double Lanczos::getLanczosOffdiagonalElement(complex<double> a, complex<double> b)
{
    wfThree.addEqual(-a, wfTwo);
    if( abs(b) > 1e-100 ) wfThree.addEqual(-b, wfOne);
    return wfThree.normalize();
}

void Lanczos::recurseWaveFunctions()
{
    LanczosBasisWf wfTemp;
    wfTemp  = move(wfOne);
    wfOne   = move(wfTwo);
    wfTwo   = move(wfThree);
    wfThree = move(wfTemp);
}

tuple<double, vector<double> > Lanczos::diagonalizeLanczosMatrix(vector<double> a, vector<double> b) const
{
    if( a.size() != b.size() )
    {
        cerr<<"Input size is not consistent in Lanczos::diagonalizeLanczosMatrix!"<<endl;
        exit(1);
    }

    HAO_INT L = a.size();
    HAO_INT lwork = 2*L -2; if( lwork < 1 ) lwork = 1;
    vector<double> work(lwork);
    vector<double> fullvector(L*L);
    char compz = 'I'; HAO_INT info;
    dsteqr( &compz , &L, a.data() , b.data()+1 , fullvector.data() , &L , work.data() , &info );
    if( info != 0 )
    {
        cerr<<"Dsteqr in Lanczos::diagonalizeLanczosMatrix does not execute well "<<info<<endl;
        exit(1);
    }

    double  lowestValue = a[0];
    vector<double> lowestVector(L);
    copy( fullvector.data(), fullvector.data()+L, lowestVector.data() );

    return make_tuple( lowestValue,  move( lowestVector ) );
}

void Lanczos::getNewEigenstate(const vector<double> &a, const vector<double> &b, const vector<double> &vec)
{
    LanczosBasisWf &currentEigenstate = eigenstates.back();
    wfTwo = currentEigenstate;

    currentEigenstate.scale( vec[0] );

    size_t L = vec.size();
    for(size_t i = 0; i < (L-1); ++i)
    {
        model->applyHToWf(wfTwo, wfThree);
        getLanczosOffdiagonalElement( a[i], b[i]);
        currentEigenstate.addEqual( vec[i+1], wfThree );
        recurseWaveFunctions();
    }
    projectWaveFunction(currentEigenstate);
}

void Lanczos::projectWaveFunction(LanczosBasisWf &wfToProject)
{
    size_t L = eigenstates.size()-1;
    for(size_t i = 0; i < L; ++i)
    {
        wfToProject.orthogonalizeWith( eigenstates[i] );
    }

    model->projectSymmetry( wfToProject );

    double nrm2 = wfToProject.normalize();

    cout<<scientific<<"After projection, the normalized factor is "<<nrm2<<endl;
}

Lanczos::Lanczos(const Lanczos& x)  {};

Lanczos & Lanczos::operator  = (const Lanczos& x) { return *this; }