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
                      int incx=1, int incy=1);

    std::complex<double> normBlas_cpu(const TensorCore<std::complex<double>, 1> &x, int incx = 1);

    void scalBlas_cpu(std::complex<double> a, TensorCore<std::complex<double>, 1> &x, int incx = 1);
} //end namespace tensor_hao

#endif
