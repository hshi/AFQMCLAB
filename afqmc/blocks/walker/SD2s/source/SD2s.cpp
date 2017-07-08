//
// Created by boruoshihao on 5/17/17.
//

#include "../include/SD2s.h"
#include "../../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

SD2s::SD2s():logw(0.0) {}

SD2s::SD2s(size_t L, size_t Nup, size_t Ndn):logw(0.0)
{
    wfUp.resize(L, Nup);
    wfDn.resize(L, Ndn);
}

SD2s::SD2s(const SD2s &x) { copy_deep(x); }

SD2s::SD2s(SD2s &&x) { move_deep(x); }

SD2s::~SD2s() { }

SD2s &SD2s::operator=(const SD2s &x) { copy_deep(x); return *this; }

SD2s &SD2s::operator=(SD2s &&x) { move_deep(x); return *this; }

const complex<double> &SD2s::getLogw() const { return logw; }

const TensorHao<complex<double>, 2> &SD2s::getWfUp() const { return wfUp; }

const TensorHao<complex<double>, 2> &SD2s::getWfDn() const { return wfDn; }

complex<double> &SD2s::logwRef() { return logw; }

TensorHao<complex<double>, 2> &SD2s::wfUpRef() { return wfUp; }

TensorHao<complex<double>, 2> &SD2s::wfDnRef() { return wfDn; }

size_t SD2s::getL() const { return wfUp.rank(0); }

size_t SD2s::getNup() const { return wfUp.rank(1); }

size_t SD2s::getNdn() const { return wfDn.rank(1); }

void SD2s::resize(size_t L, size_t Nup, size_t Ndn)
{
    wfUp.resize(L, Nup);
    wfDn.resize(L, Ndn);
}

void SD2s::stabilize()
{
    logw += log( BL_NAME(QRMatrix)(wfUp) * BL_NAME(QRMatrix)(wfDn)  );
}

void SD2s::stabilize(double &ratio)
{
    size_t Nup = wfUp.rank(1), Ndn = wfDn.rank(1);
    TensorHao<double,1> detListUp( Nup ), detListDn( Ndn );

    logw += log( BL_NAME(QRMatrix)(wfUp, detListUp) );
    logw += log( BL_NAME(QRMatrix)(wfDn, detListDn) );

    TensorHao<double,1> absDetListUp = abs( detListUp );
    double ratioUp = absDetListUp.min()/absDetListUp.max();

    TensorHao<double,1> absDetListDn = abs( detListDn );
    double ratioDn = absDetListDn.min()/absDetListDn.max();

    ratio = min( ratioUp, ratioDn );
}

std::complex<double> SD2s::normalize()
{
    stabilize();
    complex<double> logwTemp(logw);
    logw=0.0;
    return logwTemp;
}

std::complex<double> SD2s::normalize(double &ratio)
{
    stabilize(ratio);
    complex<double> logwTemp(logw);
    logw=0.0;
    return logwTemp;
}

void SD2s::addLogw(std::complex<double> logw_add)
{
    logw += logw_add;
}

void SD2s::randomFill()
{
    tensor_hao::randomFill(wfUp);
    tensor_hao::randomFill(wfDn);
    normalize();
}

void SD2s::read(const std::string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) { cout << "Error opening file in File!!! "<<filename<<endl; exit(1); }
    readFile(logw, file);
    wfUp.read(file);
    wfDn.read(file);
    file.close();
}

void SD2s::write(const std::string &filename) const
{
    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if ( ! file.is_open() ) { cout << "Error opening file in File!!! "<<filename<<endl; exit(1); }
    writeFile(logw, file);
    wfUp.write(file);
    wfDn.write(file);
    file.close();
}

int SD2s::returnNbuf() const
{
    return 16 + 16*wfUp.size() + 16*wfDn.size();
}

double SD2s::getMemory() const
{
    return 16.0+wfUp.getMemory()+wfDn.getMemory();
}

#ifdef MPI_HAO
void MPIBcast(SD2s &buffer, int root, MPI_Comm const &comm)
{
    MPIBcast( buffer.logw, root, comm );
    MPIBcast( buffer.wfUp, root, comm );
    MPIBcast( buffer.wfDn, root, comm );
}

void SD2s::pack(std::vector<char> &buf, int &posit) const
{
    MPI_Pack(&logw, 1, MPI_DOUBLE_COMPLEX, buf.data(), buf.size(), &posit, MPI_COMM_WORLD);
    MPI_Pack(wfUp.data(), wfUp.size(), MPI_DOUBLE_COMPLEX, buf.data(), buf.size(), &posit, MPI_COMM_WORLD);
    MPI_Pack(wfDn.data(), wfDn.size(), MPI_DOUBLE_COMPLEX, buf.data(), buf.size(), &posit, MPI_COMM_WORLD);
}

void SD2s::unpack(const std::vector<char> &buf, int &posit)
{
    MPI_Unpack(buf.data(), buf.size(), &posit, &logw, 1, MPI_DOUBLE_COMPLEX, MPI_COMM_WORLD);
    MPI_Unpack(buf.data(), buf.size(), &posit, wfUp.data(), wfUp.size(), MPI_DOUBLE_COMPLEX, MPI_COMM_WORLD);
    MPI_Unpack(buf.data(), buf.size(), &posit, wfDn.data(), wfDn.size(), MPI_DOUBLE_COMPLEX, MPI_COMM_WORLD);

}
#endif

void SD2s::copy_deep(const SD2s &x)
{
    logw = x.logw;
    wfUp = x.wfUp;
    wfDn = x.wfDn;
}

void SD2s::move_deep(SD2s &x)
{
    logw = x.logw;
    wfUp = move( x.wfUp );
    wfDn = move( x.wfDn );
}

