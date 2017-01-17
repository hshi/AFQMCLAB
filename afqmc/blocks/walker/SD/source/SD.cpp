//
// Created by boruoshihao on 12/25/16.
//

#include "../include/SD.h"
#include "../../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

SD::SD():logw(0.0) {}

SD::SD(size_t L, size_t N) :logw(0.0) { wf.resize(L, N); }

SD::SD(const SD &x) { copy_deep(x); }

SD::SD(SD &&x) { move_deep(x); }

SD::~SD() { }

SD &SD::operator=(const SD &x) { copy_deep(x); return *this; }

SD &SD::operator=(SD &&x) { move_deep(x); return *this; }

const complex<double> &SD::getLogw() const { return logw; }

const TensorHao<complex<double>, 2> &SD::getWf() const { return wf; }

complex<double> &SD::logwRef() { return logw; }

TensorHao<complex<double>, 2> &SD::wfRef() { return wf; }

size_t SD::getL() const { return wf.rank(0); }

size_t SD::getN() const { return wf.rank(1); }

void SD::resize(size_t L, size_t N)
{
    wf.resize(L, N);
}

void SD::stabilize()
{
    logw += log( BL_NAME(QRMatrix)(wf) );
}

complex<double> SD::normalize()
{
    complex<double> logwTemp = logw + log( BL_NAME(QRMatrix)(wf) );
    logw=0.0;
    return logwTemp;
}

void SD::randomFill()
{
    tensor_hao::randomFill(wf);
    normalize();
}

void SD::read(const string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) { cout << "Error opening file in File!!! "<<filename<<endl; exit(1); }
    readFile(logw, file);
    wf.read(file);
    file.close();
}

void SD::write(const string &filename) const
{
    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if ( ! file.is_open() ) { cout << "Error opening file in File!!! "<<filename<<endl; exit(1); }
    writeFile(logw, file);
    wf.write(file);
    file.close();
}

void SD::copy_deep(const SD &x)
{
    logw = x.logw;
    wf = x.wf;
}

void SD::move_deep(SD &x)
{
    logw = x.logw;
    wf = move( x.wf );
}

void MPIBcast(SD &buffer, int root, MPI_Comm const &comm)
{
    MPIBcast( buffer.logw, root, comm );
    MPIBcast( buffer.wf, root, comm );
}
