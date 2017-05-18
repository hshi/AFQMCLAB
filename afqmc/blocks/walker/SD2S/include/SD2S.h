//
// Created by boruoshihao on 5/17/17.
//

#ifndef AFQMCLAB_SD2S_H
#define AFQMCLAB_SD2S_H

#include "../../../../../common/tensorHao/include/tensor_all.h"

//Single Determinant, two spin species.

class SD2S
{
 private:
    std::complex<double> logw;
    tensor_hao::TensorHao<std::complex<double>,2> wfUp, wfDn;

 public:
    SD2S();
    SD2S(size_t L, size_t Nup, size_t Ndn);
    SD2S(const SD2S& x);
    SD2S(SD2S&& x);
    ~SD2S();

    SD2S & operator  = (const SD2S& x);
    SD2S & operator  = (SD2S&& x);

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
    std::complex<double> normalize();
    void addLogw(std::complex<double> logw_add);
    void randomFill();

    void read(const std::string& filename);
    void write(const std::string& filename) const;
    int returnNbuf() const;
    double getMemory() const;

#ifdef MPI_HAO
    friend void MPIBcast(SD2S &buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
    void pack( std::vector<char> &buf,  int &posit ) const;
    void unpack( const std::vector<char> &buf, int &posit );
#endif

 private:
    void copy_deep(const SD2S &x);
    void move_deep(SD2S &x);
};

#endif //AFQMCLAB_SD2S_H
