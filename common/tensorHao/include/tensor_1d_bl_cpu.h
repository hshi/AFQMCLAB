#ifndef TENSOR_1D_BL_CPU_H
#define TENSOR_1D_BL_CPU_H

#include <vector>
#include "tensor_core.h"
#include "tensor_hao_ref.h"
#include "tensor_hao.h"
#include "tensor_element_wise.h"
#include "../../lapackblasHao/blas_lapack_wrap.h"

namespace tensor_hao
{
    template <size_t D =1 >
    void copy_cpu(const TensorCore<std::complex<double>, D> &x, TensorCore<std::complex<double>, D> &y,
                  size_t incx = 1, size_t incy = 1)
    {
        HAO_INT L = x.size(); HAO_INT inc_x = incx; HAO_INT inc_y = incy;
        if( x.size() != y.size() )
        {
            std::cerr<<"Size not consistent in copy_cpu"<<std::endl; exit(1);
        }
        zcopy(&L, x.data(), &inc_x, y.data(), &inc_y);
    }

    double nrm2_cpu(const TensorCore<std::complex<double>, 1> &x, size_t incx = 1);

    void scal_cpu(std::complex<double> a, TensorCore<std::complex<double>, 1> &x, size_t incx = 1);

    std::complex<double> dotc_cpu(const TensorCore<std::complex<double>, 1> &x,
                                  const TensorCore<std::complex<double>, 1> &y, size_t incx = 1, size_t incy = 1);

    void axpy_cpu(std::complex<double> a, const TensorCore<std::complex<double>, 1> &x,
                  TensorCore<std::complex<double>, 1> &y, size_t incx = 1, size_t incy = 1);

    void gemv_cpu(const TensorCore<double, 2> &A, const TensorCore<double, 1> &x, TensorCore<double, 1> &y,
                  char TRANSA = 'N', double alpha = 1.0, double beta = 0.0);

    void gemv_cpu(const TensorCore<std::complex<double>, 2> &A,
                  const TensorCore<std::complex<double>, 1> &x, TensorCore<std::complex<double>, 1> &y,
                  char TRANSA = 'N', std::complex<double> alpha = 1.0, std::complex<double> beta = 0.0);
} //end namespace tensor_hao

#endif
