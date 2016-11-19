//
// Created by boruoshihao on 9/24/16.
//

#include "../include/LanczosInterface.h"

using namespace tensor_hao;

using namespace std;

Lanczos::Lanczos(const ModelInterface &modelInterface)
{
    model = &modelInterface;
    wfSize = model->getWfSize();
    lanStatus = 'N';
    reserve(300, 1000);
}

size_t Lanczos::getEigenSize() const
{
    return eigenvalues.size();
}

double Lanczos::getEigenvalue(size_t eigenIndex) const
{
    return eigenvalues[eigenIndex];
}

const LanczosBasisWf &Lanczos::getEigenstate(size_t eigenIndex) const
{
    return eigenstates[eigenIndex];
}

tuple<const vector<double> &, const vector<double> &> Lanczos::getLanElements() const
{
    return forward_as_tuple(lana, lanb );
}

const LanczosBasisWf &Lanczos::getLanWavefunction(size_t lanIndex) const
{
    return lanwfs[lanIndex];
}

void Lanczos::readEigens(size_t numberOfWaveFunctions)
{
    readEigenValues(numberOfWaveFunctions);
    readEigenStates(numberOfWaveFunctions);
}

void Lanczos::writeEigens(size_t startIndex) const
{
    writeEigenValues(startIndex);
    writeEigenStates(startIndex);
}

void Lanczos::readLanMatrix()
{
    readLanMatrixStatus();
    readLanMatrixElements();
    readLanMatrixWavefunctions();
}

void Lanczos::writeLanMatrix() const
{
    if( lanStatus == 'N' ) return;
    writeLanMatrixStatus();
    writeLanMatrixElements();
    writeLanMatrixWavefunctions();
}

void Lanczos::writeLanWavefunction(const string &filename, size_t lanIndex) const
{
    lanwfs[lanIndex].write(filename);
}

void Lanczos::reserve(size_t targetLanSize, size_t targetEigenSize)
{
    lana.reserve(targetLanSize);
    lanb.reserve(targetLanSize);
    lanwfs.reserve(targetLanSize);
    eigenvalues.reserve(targetEigenSize);
    eigenstates.reserve(targetEigenSize);
}

void Lanczos::clear()
{
    lanStatus = 'N';
    lana.resize(0);
    lanb.resize(0);
    lanwfs.resize(0);
}

void Lanczos::randomWfInit()
{
    cout<<"\nInitial Lanczos matrix by setting wave function randomly."<<endl;
    LanczosBasisWf wfNew(wfSize);
    wfNew.randomFill();
    if( lanwfs.size() > 0 ) lanwfs[0] = move(wfNew);
    else lanwfs.push_back( move(wfNew) );
    initLanczosMatrixFromLanwfsZero();
    cout<<endl;
}

void Lanczos::readWfInit(const string &filename)
{
    cout<<"\nInitial Lanczos matrix by reading wave function from "<<filename<<" ."<<endl;
    LanczosBasisWf wfNew(wfSize);
    wfNew.read(filename);
    if( lanwfs.size() > 0 ) lanwfs[0] = move(wfNew);
    else lanwfs.push_back( move(wfNew) );
    initLanczosMatrixFromLanwfsZero();
    cout<<endl;
}

void Lanczos::inputWfInit(LanczosBasisWf &wfNew)
{
    cout<<"\nInitial Lanczos matrix by inputting wave function."<<endl;
    if( lanwfs.size() > 0 ) lanwfs[0] = move(wfNew);
    else lanwfs.push_back( move(wfNew) );
    initLanczosMatrixFromLanwfsZero();
    cout<<endl;
}

void Lanczos::readLanInit()
{
    cout<<"\nInitial Lanczos matrix by reading everything from file."<<endl;
    readLanMatrix();
    cout<<endl;
}

void Lanczos::findEigen(const size_t L, LanczosParam lanczosParam)
{
    for(size_t i = 0; i < L; ++i)
    {
        randomWfInit();
        FindOneEigen(lanczosParam);
    }
}

tuple<double, vector<double> > diagonalizeLanczosMatrix(vector<double> a, vector<double> b);

void Lanczos::FindOneEigen(LanczosParam lanczosParam)
{
    double energyBackup = 1e100;
    double energy;
    vector<double> lanczosMatrixVector;

    for(size_t lanIndex = 0; lanIndex < lanczosParam.maxLoop; ++lanIndex)
    {
        getLanczosMatrix(lanczosParam.matrixSize-lana.size(), lanczosParam.accuracy,
                         lanczosParam.litForProjection, lanczosParam.lanwfsFlag);

        if( lana.size() == 1 ) { saveToEigen(); return; }

        tie( energy, lanczosMatrixVector ) = diagonalizeLanczosMatrix(lana, lanb);

        cout<<setprecision(16)<<"Variational energy for #"<< eigenstates.size()<<" is "<<energy<<endl;

        if( lana[0] < energy || energyBackup < energy )
        {
            if(lanczosParam.convergeFlag == 'E') { saveToEigen(); return; }
            else if(lanczosParam.convergeFlag == 'W')
            {
                cout<<"Energy is converged! Wait for the convergence of wave function!"<<endl;
            }
        }
        energyBackup = energy;

        getNewLanwfsZero(lanczosMatrixVector, lanczosParam.litForProjection);

        if( abs( lana[0]-energy ) / abs(energy) > 1e-8 )
        {
            cout<<"Error!!! New lanwfs[0] does not have the same energy with variational energy! "
                <<lana[0]<<" "<<lana[0]-energy<<" "<<abs( lana[0]-energy )/abs(energy)<<endl;
            throw LanczosLoseAccuracy_error
                ("Lanczos loses accuracy, please decrease matrixSize or litForProjection, or add more symmetry!");
        }
    }

    throw LanczosNotConverge_error("Lanczos does not converge, increase lanczos maxloop or lanczos matrixSize!");
}

tuple<const vector<double> &, const vector<double> &>
Lanczos::getLanczosMatrix(size_t L, double accuracy, double litForProjection, char wfFlag)
{
    if( lanStatus == 'N' )  { cout<<"Error!!! Lanczos Matrix has not been initialized!"<<endl; exit(1); }

    if( L + lana.size() + eigenvalues.size() > wfSize ) L = wfSize - lana.size() - eigenvalues.size();

    if( wfFlag == 'F' )
    {
        if( lanStatus == 'R' )
        {
            cout<<"Error!!! Lanczos Matrix is in Recurse status, can not build full matrix!"<<endl;
            exit(1);
        }
        getLanczosMatrixFull(L, accuracy, litForProjection);
    }

    if( wfFlag == 'R' )
    {
        if( lanStatus == 'F' ) changeLanStatusToRecurse();
        getLanczosMatrixRecurse(L, accuracy, litForProjection);
    }

    return getLanElements();
}