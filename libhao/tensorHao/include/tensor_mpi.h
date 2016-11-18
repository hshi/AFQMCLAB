#ifndef TENSOR_HAO_MPI_H
#define TENSOR_HAO_MPI_H

#include "../../mpiHao/include/mpi_fun.h"
#include <complex>
#include "tensor_core.h"
#include "tensor_hao_ref.h"
#include "tensor_hao.h"
#include "tensor_element_wise.h"

#ifdef MPI_HAO

//WARNING!!! We need to make sure buffer has the same size before call MPIBcast!

template<class T, size_t D >
void MPIBcast(tensor_hao::TensorCore<T, D> & buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD)
{
    MPIBcast(buffer.size(), buffer.data(), root, comm);
}

#endif

#endif
