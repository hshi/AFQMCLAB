//
// Created by boruoshihao on 5/17/17.
//

#ifndef AFQMCLAB_SD2S_H
#define AFQMCLAB_SD2S_H

#include "../../../../../common/tensorHao/include/tensor_all.h"

//Single Determinant, two spin species.

#ifdef MPI_HAO
class SD2s;
void MPIBcast(SD2s &buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
#endif

class SD2s
{
 private:
    std::complex<double> logw;
    tensor_hao::TensorHao<std::complex<double>,2> wfUp, wfDn;

 public:
    SD2s();
    SD2s(size_t L, size_t Nup, size_t Ndn);
    SD2s(const SD2s& x);
    SD2s(SD2s&& x);
    ~SD2s();

    SD2s & operator  = (const SD2s& x);
    SD2s & operator  = (SD2s&& x);

    const std::complex<double> &getLogw() const;
    const tensor_hao::TensorHao<std::complex<double>, 2> &getWfUp() const;
    const tensor_hao::TensorHao<std::complex<double>, 2> &getWfDn() const;
    std::complex<double> &logwRef();
    tensor_hao::TensorHao<std::complex<double>, 2> &wfUpRef();
    tensor_hao::TensorHao<std::complex<double>, 2> &wfDnRef();
    size_t getL() const;
    size_t getNup() const;
    size_t getNdn() const;

    void resize(size_t L, size_t Nup, size_t Ndn);
    void stabilize();
    void stabilize(double &ratio);
    std::complex<double> normalize();
    std::complex<double> normalize(double &ratio);
    void addLogw(std::complex<double> logw_add);
    void randomFill();

    void read(const std::string& filename);
    void write(const std::string& filename) const;
    int returnNbuf() const;
    double getMemory() const;

#ifdef MPI_HAO
    friend void MPIBcast(SD2s &buffer, int root,  const MPI_Comm& comm);
    void pack( std::vector<char> &buf,  int &posit ) const;
    void unpack( const std::vector<char> &buf, int &posit );
#endif

 private:
    void copy_deep(const SD2s &x);
    void move_deep(SD2s &x);
};

#endif //AFQMCLAB_SD2S_H
