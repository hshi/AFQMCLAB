#ifndef TENSOR_FILL_H
#define TENSOR_FILL_H

#include "tensor_core.h"
#include "../../lapackblasHao/blas_lapack_wrap.h"

namespace tensor_hao
{
    extern HAO_INT lapack_ran_ISEED[4];

    template <size_t D>
    void randomFill(TensorCore<float, D> &A)
    {
        HAO_INT itwo = 2; HAO_INT size_A = A.size();
        slarnv( &itwo, lapack_ran_ISEED, &size_A, A.data() );
    }

    template <size_t D>
    void randomFill(TensorCore<double, D> &A)
    {
        HAO_INT itwo = 2; HAO_INT size_A = A.size();
        dlarnv( &itwo, lapack_ran_ISEED, &size_A, A.data() );
    }

    template <size_t D>
    void randomFill(TensorCore<std::complex<float>, D> &A)
    {
        HAO_INT itwo = 2; HAO_INT size_A = A.size();
        clarnv( &itwo, lapack_ran_ISEED, &size_A, A.data() );
    }

    template <size_t D>
    void randomFill(TensorCore<std::complex<double>, D> &A)
    {
        HAO_INT itwo = 2; HAO_INT size_A = A.size();
        zlarnv( &itwo, lapack_ran_ISEED, &size_A, A.data() );
    }

}  //end namespace tensor_hao

#endif
