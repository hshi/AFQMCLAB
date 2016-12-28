//
// Created by boruoshihao on 12/25/16.
//

#include "../include/singleDeterminant.h"
#include "../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

SingleDeterminant::SingleDeterminant():logw(0.0) {}

SingleDeterminant::SingleDeterminant(size_t L, size_t N) :logw(0.0) { wf.resize(L, N); }

SingleDeterminant::SingleDeterminant(const SingleDeterminant &x) { copy_deep(x); }

SingleDeterminant::SingleDeterminant(SingleDeterminant &&x) { move_deep(x); }

SingleDeterminant::~SingleDeterminant() { }

SingleDeterminant &SingleDeterminant::operator=(const SingleDeterminant &x) { copy_deep(x); return *this; }

SingleDeterminant &SingleDeterminant::operator=(SingleDeterminant &&x) { move_deep(x); return *this; }

const complex<double> &SingleDeterminant::getLogw() const { return logw; }

const TensorHao<complex<double>, 2> &SingleDeterminant::getWf() const { return wf; }

complex<double> &SingleDeterminant::logwRef() { return logw; }

TensorHao<complex<double>, 2> &SingleDeterminant::wfRef() { return wf; }

size_t SingleDeterminant::getL() const { return wf.rank(0); }

size_t SingleDeterminant::getN() const { return wf.rank(1); }

void SingleDeterminant::stabilize()
{
    logw += log( BL_NAME(QRMatrix)(wf) );
}

complex<double> SingleDeterminant::normalize()
{
    complex<double> logwTemp = logw + log( BL_NAME(QRMatrix)(wf) );
    logw=0.0;
    return logwTemp;
}

void SingleDeterminant::randomFill()
{
    tensor_hao::randomFill(wf);
    normalize();
}

void SingleDeterminant::read(const string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) { cout << "Error opening file in File!!! "<<filename<<endl; exit(1); }
    readFile(logw, file);
    wf.read(file);
    file.close();
}

void SingleDeterminant::write(const string &filename) const
{
    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if ( ! file.is_open() ) { cout << "Error opening file in File!!! "<<filename<<endl; exit(1); }
    writeFile(logw, file);
    wf.write(file);
    file.close();
}

void SingleDeterminant::copy_deep(const SingleDeterminant &x)
{
    logw = x.logw;
    wf = x.wf;
}

void SingleDeterminant::move_deep(SingleDeterminant &x)
{
    logw = x.logw;
    wf = move( x.wf );
}

void MPIBcast(SingleDeterminant &buffer, int root, MPI_Comm const &comm)
{
    MPIBcast( buffer.logw, root, comm );
    MPIBcast( buffer.wf, root, comm );
}
