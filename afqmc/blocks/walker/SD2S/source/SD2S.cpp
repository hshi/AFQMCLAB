//
// Created by boruoshihao on 5/17/17.
//

#include "../include/SD2S.h"
#include "../../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

SD2S::SD2S():logw(0.0) {}

SD2S::SD2S(size_t L, size_t Nup, size_t Ndn):logw(0.0)
{
    wfUp.resize(L, Nup);
    wfDn.resize(L, Ndn);
}

SD2S::SD2S(const SD2S &x) { copy_deep(x); }

SD2S::SD2S(SD2S &&x) { move_deep(x); }

SD2S::~SD2S() { }

SD2S &SD2S::operator=(const SD2S &x) { copy_deep(x); return *this; }

SD2S &SD2S::operator=(SD2S &&x) { move_deep(x); return *this; }

const complex<double> &SD2S::getLogw() const { return logw; }

const TensorHao<complex<double>, 2> &SD2S::getWfUp() const { return wfUp; }

const TensorHao<complex<double>, 2> &SD2S::getWfDn() const { return wfDn; }

complex<double> &SD2S::logwRef() { return logw; }

TensorHao<complex<double>, 2> &SD2S::wfUpRef() { return wfUp; }

TensorHao<complex<double>, 2> &SD2S::wfDnRef() { return wfDn; }

size_t SD2S::getL() const { return wfUp.rank(0); }

size_t SD2S::getNup() const { return wfUp.rank(1); }

size_t SD2S::getNdn() const { return wfDn.rank(1); }

void SD2S::resize(size_t L, size_t Nup, size_t Ndn)
{
    wfUp.resize(L, Nup);
    wfDn.resize(L, Ndn);
}

void SD2S::stabilize()
{
    logw += log( BL_NAME(QRMatrix)(wfUp) * BL_NAME(QRMatrix)(wfDn)  );
}

std::complex<double> SD2S::normalize()
{
    stabilize();
    complex<double> logwTemp(logw);
    logw=0.0;
    return logwTemp;
}

void SD2S::addLogw(std::complex<double> logw_add)
{
    logw += logw_add;
}

void SD2S::randomFill()
{
    tensor_hao::randomFill(wfUp);
    tensor_hao::randomFill(wfDn);
    normalize();
}

void SD2S::read(const std::string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) { cout << "Error opening file in File!!! "<<filename<<endl; exit(1); }
    readFile(logw, file);
    wfUp.read(file);
    wfDn.read(file);
    file.close();
}

void SD2S::write(const std::string &filename) const
{
    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if ( ! file.is_open() ) { cout << "Error opening file in File!!! "<<filename<<endl; exit(1); }
    writeFile(logw, file);
    wfUp.write(file);
    wfDn.write(file);
    file.close();
}

int SD2S::returnNbuf() const
{
    return 16 + 16*wfUp.size() + 16*wfDn.size();
}

double SD2S::getMemory() const
{
    return 16.0+wfUp.getMemory()+wfDn.getMemory();
}

#ifdef MPI_HAO
void MPIBcast(SD2S &buffer, int root, MPI_Comm const &comm)
{
    MPIBcast( buffer.logw, root, comm );
    MPIBcast( buffer.wfUp, root, comm );
    MPIBcast( buffer.wfDn, root, comm );
}

void SD2S::pack(std::vector<char> &buf, int &posit) const
{
    MPI_Pack(&logw, 1, MPI_DOUBLE_COMPLEX, buf.data(), buf.size(), &posit, MPI_COMM_WORLD);
    MPI_Pack(wfUp.data(), wfUp.size(), MPI_DOUBLE_COMPLEX, buf.data(), buf.size(), &posit, MPI_COMM_WORLD);
    MPI_Pack(wfDn.data(), wfDn.size(), MPI_DOUBLE_COMPLEX, buf.data(), buf.size(), &posit, MPI_COMM_WORLD);
}

void SD2S::unpack(const std::vector<char> &buf, int &posit)
{
    MPI_Unpack(buf.data(), buf.size(), &posit, &logw, 1, MPI_DOUBLE_COMPLEX, MPI_COMM_WORLD);
    MPI_Unpack(buf.data(), buf.size(), &posit, wfUp.data(), wfUp.size(), MPI_DOUBLE_COMPLEX, MPI_COMM_WORLD);
    MPI_Unpack(buf.data(), buf.size(), &posit, wfDn.data(), wfDn.size(), MPI_DOUBLE_COMPLEX, MPI_COMM_WORLD);

}
#endif

void SD2S::copy_deep(const SD2S &x)
{
    logw = x.logw;
    wfUp = x.wfUp;
    wfDn = x.wfDn;
}

void SD2S::move_deep(SD2S &x)
{
    logw = x.logw;
    wfUp = move( x.wfUp );
    wfDn = move( x.wfDn );
}
