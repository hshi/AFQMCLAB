//
// Created by boruoshihao on 5/18/17.
//

#ifndef AFQMCLAB_SD2IS_H
#define AFQMCLAB_SD2IS_H

#include "../../../../../common/tensorHao/include/tensor_all.h"

//Single Determinant, two identical spin species.

#ifdef MPI_HAO
class SD2is;
void MPIBcast(SD2is &buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
#endif

class SD2is
{
 private:
    std::complex<double> logw;
    size_t Nup, Ndn;
    tensor_hao::TensorHao<std::complex<double>,2> wf;

 public:
    SD2is();
    SD2is(size_t L, size_t Nup, size_t Ndn);
    SD2is(const SD2is& x);
    SD2is(SD2is&& x);
    ~SD2is();

    SD2is & operator  = (const SD2is& x);
    SD2is & operator  = (SD2is&& x);

    const std::complex<double> &getLogw() const;
    const tensor_hao::TensorHao<std::complex<double>, 2> &getWf() const;
    std::complex<double> &logwRef();
    tensor_hao::TensorHao<std::complex<double>, 2> &wfRef();
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
    friend void MPIBcast(SD2is &buffer, int root,  const MPI_Comm& comm);
    void pack( std::vector<char> &buf,  int &posit ) const;
    void unpack( const std::vector<char> &buf, int &posit );
#endif

 private:
    void copy_deep(const SD2is &x);
    void move_deep(SD2is &x);
};

#endif //AFQMCLAB_SD2IS_H
