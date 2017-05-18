//
// Created by boruoshihao on 5/18/17.
//

#ifndef AFQMCLAB_SD2IS_H
#define AFQMCLAB_SD2IS_H

#include "../../../../../common/tensorHao/include/tensor_all.h"

//Single Determinant, two identical spin species.

class SD2IS
{
 private:
    std::complex<double> logw;
    size_t Nup, Ndn;
    tensor_hao::TensorHao<std::complex<double>,2> wf;

 public:
    SD2IS();
    SD2IS(size_t L, size_t Nup, size_t Ndn);
    SD2IS(const SD2IS& x);
    SD2IS(SD2IS&& x);
    ~SD2IS();

    SD2IS & operator  = (const SD2IS& x);
    SD2IS & operator  = (SD2IS&& x);

    const std::complex<double> &getLogw() const;
    const tensor_hao::TensorHao<std::complex<double>, 2> &getWf() const;
    std::complex<double> &logwRef();
    tensor_hao::TensorHao<std::complex<double>, 2> &wfRef();
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
    friend void MPIBcast(SD2IS &buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
    void pack( std::vector<char> &buf,  int &posit ) const;
    void unpack( const std::vector<char> &buf, int &posit );
#endif

 private:
    void copy_deep(const SD2IS &x);
    void move_deep(SD2IS &x);
};

#endif //AFQMCLAB_SD2IS_H
