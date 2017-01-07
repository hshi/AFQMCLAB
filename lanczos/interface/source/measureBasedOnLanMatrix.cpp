//
// Created by boruoshihao on 12/8/16.
//

#include "../include/measureBasedOnLanMatrix.h"
#include "../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

MeasureBasedOnLanMatrix::MeasureBasedOnLanMatrix(const ModelInterface &modelInterface, string prefixName)
{
    lan.set(modelInterface);
    read(prefixName);
}

MeasureBasedOnLanMatrix::MeasureBasedOnLanMatrix(const ModelInterface &modelInterface, LanczosBasisWf &wf)
{
    lan.set(modelInterface);

    wfNorm = wf.normalize();
    lan.inputWfInit(wf);
}

void diagonalizeTriagonalMatrixGetEigenvalueAndOneRowOfEigenvector(vector<double> &a, vector<double> &b)
{
    if( a.size()  != b.size() )
    {
        cerr<<"Diagonal and offDiagonal size is not consistent in "
            "diagonalizeTriagonalMatrixGetEigenvalueAndOneRowOfEigenvector!"<<endl;
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
        cerr<<"Dsteqr in diagonalizeTriagonalMatrixGetEigenvalueAndOneRowOfEigenvector does not execute well "<<info<<endl;
        exit(1);
    }

    for(HAO_INT i = 0; i < L; ++i) b[i] = fullvector[i*L];
}

TensorHao<double,1> MeasureBasedOnLanMatrix::returnLogExpMinusTauModel(const TensorHao<double, 1> &tau, size_t L,
                                                                       double accuracy, double litForProjection, char wfFlag)
{
    auto lanabTuple = lan.getLanElements();
    const vector<double> &lana = get<0>(lanabTuple);
    const vector<double> &lanb = get<1>(lanabTuple);

    if( L > lana.size() )
    {
        lan.getLanczosMatrix( L-lana.size(), accuracy, litForProjection, wfFlag );
    }

    vector<double> a(L), b(L);
    if( lana.size() >= L )
    {
        copy( lana.data(), lana.data()+L, a.data() );
        copy( lanb.data(), lanb.data()+L, b.data() );
    }
    else
    {
        cout<<"Lanczos Matrix size is "<<lana.size()<<" instead of "<<L<<" ."<<endl;
        a = lana;
        b = lanb;
    }

    diagonalizeTriagonalMatrixGetEigenvalueAndOneRowOfEigenvector(a,b);

    size_t abSize = a.size();
    double E0 = a[0]; for(size_t i = 0; i <abSize; ++i) a[i] -= E0;
    for(size_t j = 0; j < abSize; ++j) b[j] = b[j] * b[j] * wfNorm * wfNorm;

    size_t tauSize = tau.size();
    TensorHao<double, 1> expMinusTauModel( tauSize );
    for(size_t i = 0; i < tauSize; ++i)
    {
        expMinusTauModel(i) = 0.0;
        for(size_t j = 0; j < abSize; ++j)
        {
            expMinusTauModel(i) += exp( -tau(i) * a[j]  ) * b[j];
        }
    }

    return tensor_hao::log( expMinusTauModel ) - tau * E0;
}

TensorHao<complex<double>,1> MeasureBasedOnLanMatrix::returnGreenFunction(const TensorHao<complex<double>, 1> &omega, size_t L,
                                                                          double accuracy, double litForProjection, char wfFlag)
{
    auto lanabTuple = lan.getLanElements();
    const vector<double> &lana = get<0>(lanabTuple);
    const vector<double> &lanb = get<1>(lanabTuple);

    if( L > lana.size() )
    {
        lan.getLanczosMatrix( L-lana.size(), accuracy, litForProjection, wfFlag );
    }

    vector<double> a(L), b(L);
    if( lana.size() >= L )
    {
        copy( lana.data(), lana.data()+L, a.data() );
        copy( lanb.data(), lanb.data()+L, b.data() );
    }
    else
    {
        cout<<"Lanczos Matrix size is "<<lana.size()<<" instead of "<<L<<" ."<<endl;
        a = lana;
        b = lanb;
    }
    b.push_back(1.0); //b.size > a.size Used for PE[aSize] and QE[bSize].

    size_t omegaSize = omega.size();
    size_t aSize = a.size();
    TensorHao<complex<double>,1> greenFunction( omegaSize );
    vector<complex<double>> PE(aSize+1), QE(aSize+1);
    for(size_t i = 0; i < omegaSize; ++i)
    {
        PE[0] = 1.0;
        PE[1] = ( omega(i) - a[0] ) / b[1];
        QE[0] = 0;
        QE[1] = 1;
        for(size_t j = 2; j < aSize+1; ++j)
        {
            PE[j] = ( ( omega(i) - a[j-1] )* PE[j-1] - b[j-1]*PE[j-2] ) / b[j];
            QE[j] = ( ( omega(i) - a[j-1] )* QE[j-1] - b[j-1]*QE[j-2] ) / b[j];
        }
        greenFunction(i) = QE[aSize] / ( b[1]*PE[aSize] ) * wfNorm * wfNorm;
    }

    return greenFunction;
}

double MeasureBasedOnLanMatrix::getWfNorm() const
{
    return wfNorm;
}

tuple<const vector<double> &, const vector<double> &> MeasureBasedOnLanMatrix::getLanElements() const
{
    return lan.getLanElements();
}

void MeasureBasedOnLanMatrix::read(string prefixName)
{
    lan.readLanMatrix(prefixName);
    readFile(wfNorm, prefixName+"wfNorm.dat");
}

void MeasureBasedOnLanMatrix::write(string prefixName) const
{
    lan.writeLanMatrix(prefixName);
    writeFile(wfNorm, prefixName+"wfNorm.dat");
}

MeasureBasedOnLanMatrix::MeasureBasedOnLanMatrix(const MeasureBasedOnLanMatrix &x) { }

MeasureBasedOnLanMatrix &MeasureBasedOnLanMatrix::operator=(const MeasureBasedOnLanMatrix &x) { return *this; }
