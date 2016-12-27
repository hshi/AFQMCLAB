#ifndef TENSOR_HAO_MPI_H
#define TENSOR_HAO_MPI_H

#include "../../mpiHao/include/mpi_fun.h"
#include <complex>
#include "tensor_core.h"
#include "tensor_hao_ref.h"
#include "tensor_hao.h"
#include "tensor_element_wise.h"

#ifdef MPI_HAO

template<class T, size_t D >
void MPIBcast(tensor_hao::TensorHao<T, D> & buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD)
{
    size_t n[D];
    for(size_t i = 0; i < D; ++i) n[i] = buffer.rank(i);
    MPIBcast(D, n, root, comm);

    buffer.resize(n);
    MPIBcast(buffer.size(), buffer.data(), root, comm);
}

template<class T, size_t D >
void MPIBcast(tensor_hao::TensorHaoRef<T, D> & buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD)
{
    size_t n[D];
    for(size_t i = 0; i < D; ++i) n[i] = buffer.rank(i);
    MPIBcast(D, n, root, comm);

    for(size_t i = 0; i < D; ++i)
    {
        if( n[i] !=  buffer.rank(i) )
        {
            std::cerr<<"Error!!! Tensor rank size is not consistent for MPIBcast TensorHaoRef! "<<MPIRank()<<std::endl;
            exit(1);
        }
    }

    MPIBcast(buffer.size(), buffer.data(), root, comm);
}

#endif

#endif