//
// Created by boruoshihao on 5/18/17.
//

#include "../include/SD2is.h"
#include "../../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

SD2is::SD2is():logw(0.0), Nup(0), Ndn(0) {}

SD2is::SD2is(size_t L, size_t Nup, size_t Ndn):logw(0.0), Nup(Nup), Ndn(Ndn)
{
    wf.resize(L, max(Nup, Ndn) );
}

SD2is::SD2is(const SD2is &x) { copy_deep(x); }

SD2is::SD2is(SD2is &&x) { move_deep(x); }

SD2is::~SD2is() { }

SD2is &SD2is::operator=(const SD2is &x) { copy_deep(x); return *this; }

SD2is &SD2is::operator=(SD2is &&x) { move_deep(x); return *this; }

const complex<double> &SD2is::getLogw() const { return logw; }

const TensorHao<complex<double>, 2> &SD2is::getWf() const { return wf; }

complex<double> &SD2is::logwRef() { return logw; }

TensorHao<complex<double>, 2> &SD2is::wfRef() { return wf; }

size_t SD2is::getL() const { return wf.rank(0); }

size_t SD2is::getNup() const { return Nup; }

size_t SD2is::getNdn() const { return Ndn; }

void SD2is::resize(size_t L, size_t Nup, size_t Ndn)
{
    SD2is::Nup = Nup; SD2is::Ndn = Ndn;
    wf.resize(L, max(Nup, Ndn) );
}

void SD2is::stabilize()
{
    if( Nup == Ndn ) logw += 2.0 * log( BL_NAME(QRMatrix)(wf)  );
    else
    {
        TensorHao<double,1> detList( max(Nup, Ndn) );
        logw += log( BL_NAME(QRMatrix)(wf, detList) );
        size_t Nmin = min( Nup, Ndn );
        //norm can be a negative number, use complex for log function
        complex<double> norm(1.0, 0.0); for(size_t i = 0; i < Nmin; ++i) norm *= detList(i);
        logw += log( norm );
    }
}

void SD2is::stabilize(double &ratio)
{
    size_t Nmax = max( Nup, Ndn );
    size_t Nmin = min( Nup, Ndn );

    TensorHao<double,1> detList( Nmax );
    logw += log( BL_NAME(QRMatrix)(wf, detList) );

    //norm can be a negative number, use complex for log function
    complex<double> norm(1.0, 0.0); for(size_t i = 0; i < Nmin; ++i) norm *= detList(i);
    logw += log( norm );

    TensorHao<double,1> absDetList = abs( detList );
    ratio = absDetList.min()/absDetList.max();
}

complex<double> SD2is::normalize()
{
    stabilize();
    complex<double> logwTemp(logw);
    logw=0.0;
    return logwTemp;
}

complex<double> SD2is::normalize(double &ratio)
{
    stabilize(ratio);
    complex<double> logwTemp(logw);
    logw=0.0;
    return logwTemp;
}

void SD2is::addLogw(complex<double> logw_add)
{
    logw += logw_add;
}

void SD2is::randomFill()
{
    tensor_hao::randomFill(wf);
    normalize();
}

void SD2is::read(const string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) { cout << "Error opening file in File!!! "<<filename<<endl; exit(1); }
    readFile(logw, file);
    readFile(Nup, file);
    readFile(Ndn, file);
    wf.read(file);
    file.close();
}

void SD2is::write(const string &filename) const
{
    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if ( ! file.is_open() ) { cout << "Error opening file in File!!! "<<filename<<endl; exit(1); }
    writeFile(logw, file);
    writeFile(Nup, file);
    writeFile(Ndn, file);
    wf.write(file);
    file.close();
}

int SD2is::returnNbuf() const
{
    return 16 + 16*wf.size();
}

double SD2is::getMemory() const
{
    return 16.0 + 8.0*2 + wf.getMemory();
}

#ifdef MPI_HAO
void MPIBcast(SD2is &buffer, int root, MPI_Comm const &comm)
{
    MPIBcast( buffer.logw, root, comm );
    MPIBcast( buffer.Nup, root, comm );
    MPIBcast( buffer.Ndn, root, comm );
    MPIBcast( buffer.wf, root, comm );
}

void SD2is::pack(vector<char> &buf, int &posit) const
{
    MPI_Pack(&logw, 1, MPI_DOUBLE_COMPLEX, buf.data(), buf.size(), &posit, MPI_COMM_WORLD);
    MPI_Pack(wf.data(), wf.size(), MPI_DOUBLE_COMPLEX, buf.data(), buf.size(), &posit, MPI_COMM_WORLD);
}

void SD2is::unpack(const vector<char> &buf, int &posit)
{
    MPI_Unpack(buf.data(), buf.size(), &posit, &logw, 1, MPI_DOUBLE_COMPLEX, MPI_COMM_WORLD);
    MPI_Unpack(buf.data(), buf.size(), &posit, wf.data(), wf.size(), MPI_DOUBLE_COMPLEX, MPI_COMM_WORLD);
}
#endif

void SD2is::copy_deep(const SD2is &x)
{
    logw = x.logw;
    Nup  = x.Nup;
    Ndn  = x.Ndn;
    wf   = x.wf;
}

void SD2is::move_deep(SD2is &x)
{
    logw = x.logw;
    Nup  = x.Nup;
    Ndn  = x.Ndn;
    wf   = move( x.wf );
}


