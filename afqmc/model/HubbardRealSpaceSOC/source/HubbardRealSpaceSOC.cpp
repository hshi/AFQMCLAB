//
// Created by boruoshihao on 1/11/17.
//

#include "../include/HubbardRealSpaceSOC.h"
#include "../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

HubbardRealSpaceSOC::HubbardRealSpaceSOC():L(0),N(0),KEigenStatus(false) { }

HubbardRealSpaceSOC::HubbardRealSpaceSOC(const string &filename) { read(filename); }

HubbardRealSpaceSOC::~HubbardRealSpaceSOC() { }

size_t HubbardRealSpaceSOC::getL() const { return L; }

size_t HubbardRealSpaceSOC::getN() const { return N; }

const TensorHao<complex<double>, 2> &HubbardRealSpaceSOC::getK() const { return K; }

const TensorHao<double, 1> &HubbardRealSpaceSOC::getMu() const { return mu; }

const TensorHao<double, 1> &HubbardRealSpaceSOC::getHx() const { return hx; }

const TensorHao<double, 1> &HubbardRealSpaceSOC::getHy() const { return hy; }

const TensorHao<double, 1> &HubbardRealSpaceSOC::getHz() const { return hz; }

const TensorHao<double, 1> &HubbardRealSpaceSOC::getU() const  { return U; }

bool HubbardRealSpaceSOC::getKEigenStatus() const { return KEigenStatus; }

const TensorHao<double, 1> &HubbardRealSpaceSOC::getKEigenValue() const { return KEigenValue; }

const TensorHao<complex<double>, 2> &HubbardRealSpaceSOC::getKEigenVector() const { return KEigenVector; }

void HubbardRealSpaceSOC::read(const string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}

    readFile( L, file );
    readFile( N, file );
    K.resize(L,L); readFile( K.size(),  K.data(),  file );
    mu.resize(L);  readFile( mu.size(), mu.data(), file );
    hx.resize(L);  readFile( hx.size(), hx.data(), file );
    hy.resize(L);  readFile( hy.size(), hy.data(), file );
    hz.resize(L);  readFile( hz.size(), hz.data(), file );
    U.resize(L);   readFile( U.size(),  U.data(),  file );

    file.close();

    KEigenStatus = false;
    KEigenValue.resize( static_cast<size_t>(0) );
    KEigenVector.resize( 0, 0 );
}

void HubbardRealSpaceSOC::write(const string &filename) const
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

void MPIBcast(HubbardRealSpaceSOC &buffer, int root, MPI_Comm const &comm)
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

HubbardRealSpaceSOC::HubbardRealSpaceSOC(const HubbardRealSpaceSOC &x) { }

HubbardRealSpaceSOC &HubbardRealSpaceSOC::operator=(const HubbardRealSpaceSOC &x) { return *this; }