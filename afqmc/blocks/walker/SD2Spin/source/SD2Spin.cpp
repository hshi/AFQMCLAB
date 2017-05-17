//
// Created by boruoshihao on 5/17/17.
//

#include "../include/SD2Spin.h"
#include "../../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

SD2Spin::SD2Spin():logw(0.0) {}

SD2Spin::SD2Spin(size_t L, size_t Nup, size_t Ndn):logw(0.0)
{
    wfUp.resize(L, Nup);
    wfDn.resize(L, Ndn);
}

SD2Spin::SD2Spin(const SD2Spin &x) { copy_deep(x); }

SD2Spin::SD2Spin(SD2Spin &&x) { move_deep(x); }

SD2Spin::~SD2Spin() { }

SD2Spin &SD2Spin::operator=(const SD2Spin &x) { copy_deep(x); return *this; }

SD2Spin &SD2Spin::operator=(SD2Spin &&x) { move_deep(x); return *this; }

const complex<double> &SD2Spin::getLogw() const { return logw; }

const TensorHao<complex<double>, 2> &SD2Spin::getWfUp() const { return wfUp; }

const TensorHao<complex<double>, 2> &SD2Spin::getWfDn() const { return wfDn; }

complex<double> &SD2Spin::logwRef() { return logw; }

TensorHao<complex<double>, 2> &SD2Spin::wfUpRef() { return wfUp; }

TensorHao<complex<double>, 2> &SD2Spin::wfDnRef() { return wfDn; }

size_t SD2Spin::getL() const { return wfUp.rank(0); }

size_t SD2Spin::getNup() const { return wfUp.rank(1); }

size_t SD2Spin::getNdn() const { return wfDn.rank(1); }

void SD2Spin::resize(size_t L, size_t Nup, size_t Ndn)
{
    wfUp.resize(L, Nup);
    wfDn.resize(L, Ndn);
}

void SD2Spin::stabilize()
{
    logw += log( BL_NAME(QRMatrix)(wfUp) * BL_NAME(QRMatrix)(wfDn)  );
}

std::complex<double> SD2Spin::normalize()
{
    complex<double> logwTemp = logw + log( BL_NAME(QRMatrix)(wfUp) * BL_NAME(QRMatrix)(wfDn) );
    logw=0.0;
    return logwTemp;
}

void SD2Spin::addLogw(std::complex<double> logw_add)
{
    logw += logw_add;
}

void SD2Spin::randomFill()
{
    tensor_hao::randomFill(wfUp);
    tensor_hao::randomFill(wfDn);
    normalize();
}

void SD2Spin::read(const std::string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) { cout << "Error opening file in File!!! "<<filename<<endl; exit(1); }
    readFile(logw, file);
    wfUp.read(file);
    wfDn.read(file);
    file.close();
}

void SD2Spin::write(const std::string &filename) const
{
    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if ( ! file.is_open() ) { cout << "Error opening file in File!!! "<<filename<<endl; exit(1); }
    writeFile(logw, file);
    wfUp.write(file);
    wfDn.write(file);
    file.close();
}

int SD2Spin::returnNbuf() const
{
    return 16 + 16*wfUp.size() + 16*wfDn.size();
}

double SD2Spin::getMemory() const
{
    return 16.0+wfUp.getMemory()+wfDn.getMemory();
}

#ifdef MPI_HAO
void MPIBcast(SD2Spin &buffer, int root, MPI_Comm const &comm)
{
    MPIBcast( buffer.logw, root, comm );
    MPIBcast( buffer.wfUp, root, comm );
    MPIBcast( buffer.wfDn, root, comm );
}

void SD2Spin::pack(std::vector<char> &buf, int &posit) const
{
    MPI_Pack(&logw, 1, MPI_DOUBLE_COMPLEX, buf.data(), buf.size(), &posit, MPI_COMM_WORLD);
    MPI_Pack(wfUp.data(), wfUp.size(), MPI_DOUBLE_COMPLEX, buf.data(), buf.size(), &posit, MPI_COMM_WORLD);
    MPI_Pack(wfDn.data(), wfDn.size(), MPI_DOUBLE_COMPLEX, buf.data(), buf.size(), &posit, MPI_COMM_WORLD);
}

void SD2Spin::unpack(const std::vector<char> &buf, int &posit)
{
    MPI_Unpack(buf.data(), buf.size(), &posit, &logw, 1, MPI_DOUBLE_COMPLEX, MPI_COMM_WORLD);
    MPI_Unpack(buf.data(), buf.size(), &posit, wfUp.data(), wfUp.size(), MPI_DOUBLE_COMPLEX, MPI_COMM_WORLD);
    MPI_Unpack(buf.data(), buf.size(), &posit, wfDn.data(), wfDn.size(), MPI_DOUBLE_COMPLEX, MPI_COMM_WORLD);

}
#endif

void SD2Spin::copy_deep(const SD2Spin &x)
{
    logw = x.logw;
    wfUp = x.wfUp;
    wfDn = x.wfDn;
}

void SD2Spin::move_deep(SD2Spin &x)
{
    logw = x.logw;
    wfUp = move( x.wfUp );
    wfDn = move( x.wfDn );
}
