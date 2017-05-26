#ifndef _CUSTOMIZED_BLAS_H_
#define _CUSTOMIZED_BLAS_H_

#include "Hao_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* BLAS Level1 */

#define zcopy FORTRAN_WRAPPER(zcopy)
void zcopy(
    const HAO_INT *n,
    const HAO_Complex16 *x,
    const HAO_INT *incx,
    HAO_Complex16 *y,
    const HAO_INT *incy);

#define dznrm2 FORTRAN_WRAPPER(dznrm2)
double dznrm2(
    const HAO_INT *n,
    const HAO_Complex16 *x,
    const HAO_INT *incx);

#define zscal FORTRAN_WRAPPER(zscal)
void zscal(
    const HAO_INT *n,
    const HAO_Complex16 *a,
    HAO_Complex16 *x,
    const HAO_INT *incx);

#define zdotc FORTRAN_WRAPPER(zdotc)
#ifndef FORTRAN_COMPLEX_FUNCTIONS_RETURN_VOID
HAO_Complex16 zdotc(
#else
void zdotc( HAO_Complex16 *pres,
#endif
    const HAO_INT *n,
    const HAO_Complex16 *x,
    const HAO_INT *incx,
    const HAO_Complex16 *y,
    const HAO_INT *incy);

#define zaxpy FORTRAN_WRAPPER(zaxpy)
void zaxpy(
    const HAO_INT *n,
    const HAO_Complex16 *alpha,
    const HAO_Complex16 *x,
    const HAO_INT *incx,
    HAO_Complex16 *y,
    const HAO_INT *incy);

/* blas level2 */

#define dgemv FORTRAN_WRAPPER(dgemv)
void dgemv(
        const char *trans,
        const HAO_INT *m,
        const HAO_INT *n,
        const double *alpha,
        const double *a,
        const HAO_INT *lda,
        const double *x,
        const HAO_INT *incx,
        const double *beta,
        double *y,
        const HAO_INT *incy);

#define zgemv FORTRAN_WRAPPER(zgemv)
void zgemv(
    const char *trans,
    const HAO_INT *m,
    const HAO_INT *n,
    const HAO_Complex16 *alpha,
    const HAO_Complex16 *a,
    const HAO_INT *lda,
    const HAO_Complex16 *x,
    const HAO_INT *incx,
    const HAO_Complex16 *beta,
    HAO_Complex16 *y,
    const HAO_INT *incy);

/* blas level3 */

#define sgemm FORTRAN_WRAPPER(sgemm)
void sgemm(
    const char *transa,
    const char *transb,
    const HAO_INT *m,
    const HAO_INT *n,
    const HAO_INT *k,
    const float *alpha,
    const float *a,
    const HAO_INT *lda,
    const float *b,
    const HAO_INT *ldb,
    const float *beta,
    float *c,
    const HAO_INT *ldc);

#define cgemm FORTRAN_WRAPPER(cgemm)
void cgemm(
    const char *transa,
    const char *transb,
    const HAO_INT *m,
    const HAO_INT *n,
    const HAO_INT *k,
    const HAO_Complex8 *alpha,
    const HAO_Complex8 *a,
    const HAO_INT *lda,
    const HAO_Complex8 *b,
    const HAO_INT *ldb,
    const HAO_Complex8 *beta,
    HAO_Complex8 *c,
    const HAO_INT *ldc);

#define dgemm FORTRAN_WRAPPER(dgemm)
void dgemm(
    const char *transa,
    const char *transb,
    const HAO_INT *m,
    const HAO_INT *n,
    const HAO_INT *k,
    const double *alpha,
    const double *a,
    const HAO_INT *lda,
    const double *b,
    const HAO_INT *ldb,
    const double *beta,
    double *c,
    const HAO_INT *ldc);

#define zgemm FORTRAN_WRAPPER(zgemm)
void zgemm(
    const char *transa,
    const char *transb,
    const HAO_INT *m,
    const HAO_INT *n,
    const HAO_INT *k,
    const HAO_Complex16 *alpha,
    const HAO_Complex16 *a,
    const HAO_INT *lda,
    const HAO_Complex16 *b,
    const HAO_INT *ldb,
    const HAO_Complex16 *beta,
    HAO_Complex16 *c,
    const HAO_INT *ldc);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CUSTOMIZED_BLAS_H_ */
