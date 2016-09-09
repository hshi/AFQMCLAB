#ifndef TENSOR_FILL_H
#define TENSOR_FILL_H

#include "tensor_core.h"
#include "blas_lapack_wrap.h"

namespace tensor_hao
{
    extern int lapack_ran_ISEED[4];

    template <int D>
    void fill_random(Tensor_core<float,D> &A)
    {
        int itwo = 2; int size_A = A.size();
        F77NAME(slarnv)( &itwo, lapack_ran_ISEED, &size_A, A.data() );
    }

    template <int D>
    void fill_random(Tensor_core<double,D> &A)
    {
        int itwo = 2; int size_A = A.size();
        F77NAME(dlarnv)( &itwo, lapack_ran_ISEED, &size_A, A.data() );
    }

    template <int D>
    void fill_random(Tensor_core<std::complex<float>,D> &A)
    {
        int itwo = 2; int size_A = A.size();
        F77NAME(clarnv)( &itwo, lapack_ran_ISEED, &size_A, A.data() );
    }

    template <int D>
    void fill_random(Tensor_core<std::complex<double>,D> &A)
    {
        int itwo = 2; int size_A = A.size();
        F77NAME(zlarnv)( &itwo, lapack_ran_ISEED, &size_A, A.data() );
    }

}  //end namespace tensor_hao

#endif
