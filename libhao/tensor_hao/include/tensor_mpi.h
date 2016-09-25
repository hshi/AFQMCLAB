#ifndef TENSOR_HAO_MPI_H
#define TENSOR_HAO_MPI_H

#include "../../mpi_hao/mpi_fun.h"
#include <complex>
#include "tensor_core.h"
#include "tensor_hao_ref.h"
#include "tensor_hao.h"
#include "tensor_element_wise.h"

#ifdef MPI_HAO

namespace tensor_hao
{

 //WARNING!!! We need to make sure buffer has the same size before call MPIBcast!

 template<int D>  
 void MPIBcast(TensorCore<double, D> & buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD)
 {
     MPI_Bcast(buffer.data(), buffer.size(), MPI_DOUBLE, root, comm);
 }

 template<int D>
 void MPIBcast(TensorCore<std::complex<double>,D> & buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD)
 {
     MPI_Bcast(buffer.data(), buffer.size(), MPI_DOUBLE_COMPLEX, root, comm);
 }
}

#endif

#endif
