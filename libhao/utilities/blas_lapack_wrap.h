#ifndef BLAS_LAPACK_WRAP_H
#define BLAS_LAPACK_WRAP_H

#include<complex>

#ifdef USE_MKL

  #include "Hao_types.h"
  #define MKL_INT HAO_INT
  #define MKL_Complex8  std::complex<float>
  #define MKL_Complex16 std::complex<double>
  #include "mkl.h"
  #define F77NAME(x) x

#endif


#if defined(USE_ACML) || defined(USE_BLAS_LAPACK)

  #define HAO_Complex8  std::complex<float>
  #define HAO_Complex16 std::complex<double>
  #include "customized_blas.h"
  #include "customized_lapack.h"

  #ifdef FORTRAN_NO_UNDERSCORE
  #define F77NAME(x) x
  #else
  #define F77NAME(x) x##_
  #endif

#endif

#endif