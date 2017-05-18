//
// Created by boruoshihao on 5/18/17.
//

#include "../include/SD2IS.h"
#include "../../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

SD2IS::SD2IS():logw(0.0), Nup(0), Ndn(0) {}

SD2IS::SD2IS(size_t L, size_t Nup, size_t Ndn):logw(0.0), Nup(Nup), Ndn(Ndn)
{
    wf.resize(L, max(Nup, Ndn) );
}

SD2IS::SD2IS(const SD2IS &x) { copy_deep(x); }

SD2IS::SD2IS(SD2IS &&x) { move_deep(x); }

SD2IS::~SD2IS() { }

SD2IS &SD2IS::operator=(const SD2IS &x) { copy_deep(x); return *this; }

SD2IS &SD2IS::operator=(SD2IS &&x) { move_deep(x); return *this; }

const complex<double> &SD2IS::getLogw() const { return logw; }

const TensorHao<complex<double>, 2> &SD2IS::getWf() const { return wf; }

complex<double> &SD2IS::logwRef() { return logw; }

TensorHao<complex<double>, 2> &SD2IS::wfRef() { return wf; }

size_t SD2IS::getL() const { return wf.rank(0); }

size_t SD2IS::getNup() const { return Nup; }

size_t SD2IS::getNdn() const { return Ndn; }

void SD2IS::resize(size_t L, size_t Nup, size_t Ndn)
{
    SD2IS::Nup = Nup; SD2IS::Ndn = Ndn;
    wf.resize(L, max(Nup, Ndn) );
}

void SD2IS::stabilize()
{
    if( Nup == Ndn ) logw += 2.0 * log( BL_NAME(QRMatrix)(wf)  );
    else
    {
        TensorHao<double,1> det_list( max(Nup, Ndn) );
        logw += log( BL_NAME(QRMatrix)(wf, det_list) );

        size_t Nmin = min( Nup, Ndn );
        double norm(1.0); for(size_t i = 0; i < Nmin; ++i) norm *= det_list(i);
        logw += log( norm );
    }
}

std::complex<double> SD2IS::normalize()
{
    stabilize();
    complex<double> logwTemp(logw);
    logw=0.0;
    return logwTemp;
}

void SD2IS::addLogw(std::complex<double> logw_add)
{
    logw += logw_add;
}

void SD2IS::randomFill()
{
    tensor_hao::randomFill(wf);
    normalize();
}

void SD2IS::read(const std::string &filename)
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

void SD2IS::write(const std::string &filename) const
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

int SD2IS::returnNbuf() const
{
    return 16 + 16*wf.size();
}

double SD2IS::getMemory() const
{
    return 16.0 + 8.0*2 + wf.getMemory();
}

#ifdef MPI_HAO
void MPIBcast(SD2IS &buffer, int root, MPI_Comm const &comm)
{
    MPIBcast( buffer.logw, root, comm );
    MPIBcast( buffer.Nup, root, comm );
    MPIBcast( buffer.Ndn, root, comm );
    MPIBcast( buffer.wf, root, comm );
}

void SD2IS::pack(std::vector<char> &buf, int &posit) const
{
    MPI_Pack(&logw, 1, MPI_DOUBLE_COMPLEX, buf.data(), buf.size(), &posit, MPI_COMM_WORLD);
    MPI_Pack(wf.data(), wf.size(), MPI_DOUBLE_COMPLEX, buf.data(), buf.size(), &posit, MPI_COMM_WORLD);
}

void SD2IS::unpack(const std::vector<char> &buf, int &posit)
{
    MPI_Unpack(buf.data(), buf.size(), &posit, &logw, 1, MPI_DOUBLE_COMPLEX, MPI_COMM_WORLD);
    MPI_Unpack(buf.data(), buf.size(), &posit, wf.data(), wf.size(), MPI_DOUBLE_COMPLEX, MPI_COMM_WORLD);
}
#endif

void SD2IS::copy_deep(const SD2IS &x)
{
    logw = x.logw;
    Nup  = x.Nup;
    Ndn  = x.Ndn;
    wf   = x.wf;
}

void SD2IS::move_deep(SD2IS &x)
{
    logw = x.logw;
    Nup  = x.Nup;
    Ndn  = x.Ndn;
    wf   = move( x.wf );
}