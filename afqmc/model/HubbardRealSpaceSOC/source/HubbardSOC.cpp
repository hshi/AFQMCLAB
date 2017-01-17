//
// Created by boruoshihao on 1/11/17.
//

#include "../include/HubbardSOC.h"
#include "../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

HubbardSOC::HubbardSOC():L(0),N(0),KEigenStatus(false) { }

HubbardSOC::HubbardSOC(const string &filename) { read(filename); }

HubbardSOC::~HubbardSOC() { }

size_t HubbardSOC::getL() const { return L; }

size_t HubbardSOC::getN() const { return N; }

const TensorHao<complex<double>, 2> &HubbardSOC::getK() const { return K; }

const TensorHao<double, 1> &HubbardSOC::getMu() const { return mu; }

const TensorHao<double, 1> &HubbardSOC::getHx() const { return hx; }

const TensorHao<double, 1> &HubbardSOC::getHy() const { return hy; }

const TensorHao<double, 1> &HubbardSOC::getHz() const { return hz; }

const TensorHao<double, 1> &HubbardSOC::getU() const  { return U; }

bool HubbardSOC::getKEigenStatus() const { return KEigenStatus; }

const TensorHao<double, 1> &HubbardSOC::getKEigenValue() const { return KEigenValue; }

const TensorHao<complex<double>, 2> &HubbardSOC::getKEigenVector() const { return KEigenVector; }

void HubbardSOC::read(const string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}

    readFile( L, file );
    readFile( N, file );
    K.resize(2*L,2*L); readFile( K.size(),  K.data(),  file );
    mu.resize(L);      readFile( mu.size(), mu.data(), file );
    hx.resize(L);      readFile( hx.size(), hx.data(), file );
    hy.resize(L);      readFile( hy.size(), hy.data(), file );
    hz.resize(L);      readFile( hz.size(), hz.data(), file );
    U.resize(L);       readFile( U.size(),  U.data(),  file );

    file.close();

    KEigenStatus = false;
    KEigenValue.resize( static_cast<size_t>(0) );
    KEigenVector.resize( 0, 0 );
}

void HubbardSOC::write(const string &filename) const
{
    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}

    writeFile( L, file );
    writeFile( N, file );
    writeFile( K.size(),  K.data(),  file );
    writeFile( mu.size(), mu.data(), file );
    writeFile( hx.size(), hx.data(), file );
    writeFile( hy.size(), hy.data(), file );
    writeFile( hz.size(), hz.data(), file );
    writeFile( U.size(),  U.data(),  file );

    file.close();
}

void MPIBcast(HubbardSOC &buffer, int root, MPI_Comm const &comm)
{
    MPIBcast( buffer.L  );
    MPIBcast( buffer.N  );
    MPIBcast( buffer.K  );
    MPIBcast( buffer.mu );
    MPIBcast( buffer.hx );
    MPIBcast( buffer.hy );
    MPIBcast( buffer.hz );
    MPIBcast( buffer.U  );

    MPIBcast( buffer.KEigenStatus );
    MPIBcast( buffer.KEigenValue );
    MPIBcast( buffer.KEigenVector );
}

void HubbardSOC::setKEigenValueAndVector()
{
    if( KEigenStatus ) return;

    checkHermitian(K);
    KEigenVector = K;
    KEigenValue.resize(2*L);
    BL_NAME(eigen)(KEigenVector, KEigenValue);

    KEigenStatus = true;
}

Hop HubbardSOC::returnExpMinusAlphaK(double alpha)
{
    setKEigenValueAndVector();

    Hop expAlphaK(2*L);

    BL_NAME(gmm)( KEigenVector, dMultiMatrix( exp(-alpha*KEigenValue), conjtrans(KEigenVector) ), expAlphaK.matrix);

    return expAlphaK;
}

NiupNidn HubbardSOC::returnExpMinusAlphaV(double alpha, const std::string &decompType)
{
    return NiupNidn(alpha, decompType, U, mu, hx, hy, hz);
}

HubbardSOC::HubbardSOC(const HubbardSOC &x) { }

HubbardSOC &HubbardSOC::operator=(const HubbardSOC &x) { return *this; }
