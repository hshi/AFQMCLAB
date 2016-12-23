#ifndef BLAS_LAPACK_WRAP_H
#define BLAS_LAPACK_WRAP_H

#include<complex>
#define HAO_Complex8  std::complex<float>
#define HAO_Complex16 std::complex<double>


#ifdef USE_MKL

  #define FORTRAN_WRAPPER(x) x
  #define FORTRAN_COMPLEX_FUNCTIONS_RETURN_VOID

#endif



#ifdef USE_ACML

  #ifdef FORTRAN_NO_UNDERSCORE
      #define FORTRAN_WRAPPER(x) x
  #else
      #define FORTRAN_WRAPPER(x) x##_
  #endif

#endif



#ifdef USE_BLAS_LAPACK

  #ifdef FORTRAN_NO_UNDERSCORE
     #define FORTRAN_WRAPPER(x) x
  #else
     #define FORTRAN_WRAPPER(x) x##_
  #endif

#endif

#include "customized_blas.h"
#include "customized_lapack.h"

#endif //BLAS_LAPACK_WRAP_H
