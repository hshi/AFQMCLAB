#ifndef TENSOR_1D_BL_CPU_H
#define TENSOR_1D_BL_CPU_H

#include <vector>
#include "tensor_core.h"
#include "tensor_hao_ref.h"
#include "tensor_hao.h"
#include "tensor_element_wise.h"

namespace tensor_hao
{
    void copyBlas_cpu(const TensorCore<std::complex<double>, 1>& x, TensorCore<std::complex<double>,1>& y,
                      HAO_INT incx=1, HAO_INT incy=1);

    std::complex<double> normBlas_cpu(const TensorCore<std::complex<double>, 1> &x, HAO_INT incx = 1);

    void scalBlas_cpu(std::complex<double> a, TensorCore<std::complex<double>, 1> &x, HAO_INT incx = 1);

    std::complex<double> dotcBlas_cpu(const TensorCore<std::complex<double>, 1> &x,
                                      const TensorCore<std::complex<double>, 1> &y, HAO_INT incx = 1, HAO_INT incy = 1);

    void axpyBlas_cpu(std::complex<double> a, const TensorCore<std::complex<double>, 1> &x,
                      TensorCore<std::complex<double>, 1> &y, HAO_INT incx=1, HAO_INT incy=1);

    void gemvBlas_cpu(const TensorCore<std::complex<double>, 2> & A,
                      const TensorCore<std::complex<double>, 1> & x, TensorCore<std::complex<double>, 1> &y,
                      char TRANSA='N', std::complex<double> alpha=1.0, std::complex<double> beta=0.0);
} //end namespace tensor_hao

#endif
