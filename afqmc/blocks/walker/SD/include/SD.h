//
// Created by boruoshihao on 12/25/16.
//

#ifndef AFQMCLAB_SINGLEDETERMINANT_H
#define AFQMCLAB_SINGLEDETERMINANT_H

#include "../../../../../common/tensorHao/include/tensor_all.h"

//Single Determinant.

#ifdef MPI_HAO
class SD;
void MPIBcast(SD &buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
#endif

class SD
{
 private:
    std::complex<double> logw;
    tensor_hao::TensorHao<std::complex<double>,2> wf;

 public:
    SD();
    SD(size_t L, size_t N);
    SD(const SD& x);
    SD(SD&& x);
    ~SD();

    SD & operator  = (const SD& x);
    SD & operator  = (SD&& x);

    const std::complex<double> &getLogw() const;
    const tensor_hao::TensorHao<std::complex<double>, 2> &getWf() const;
    std::complex<double> &logwRef();
    tensor_hao::TensorHao<std::complex<double>, 2> &wfRef();
    size_t getL() const;
    size_t getN() const;

    void resize(size_t L, size_t N);
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
    friend void MPIBcast(SD &buffer, int root,  const MPI_Comm& comm);
    void pack( std::vector<char> &buf,  int &posit ) const;
    void unpack( const std::vector<char> &buf, int &posit );
#endif

 private:
    void copy_deep(const SD &x);
    void move_deep(SD &x);
};

#endif //AFQMCLAB_SINGLEDETERMINANT_H
