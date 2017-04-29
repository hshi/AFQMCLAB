#ifndef _CUSTOMIZED_LAPACK_H_
#define _CUSTOMIZED_LAPACK_H_

#include "Hao_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define slarnv FORTRAN_WRAPPER(slarnv)
void slarnv(
    const HAO_INT* idist,
    HAO_INT* iseed,
    const HAO_INT* n,
    float* x );

#define dlarnv FORTRAN_WRAPPER(dlarnv)
void dlarnv(
    const HAO_INT* idist,
    HAO_INT* iseed,
    const HAO_INT* n,
    double* x );

#define clarnv FORTRAN_WRAPPER(clarnv)
void clarnv(
    const HAO_INT* idist,
    HAO_INT* iseed,
    const HAO_INT* n,
    HAO_Complex8* x );

#define zlarnv FORTRAN_WRAPPER(zlarnv)
void zlarnv(
    const HAO_INT* idist,
    HAO_INT* iseed,
    const HAO_INT* n,
    HAO_Complex16* x );

#define dsyevd FORTRAN_WRAPPER(dsyevd)
void dsyevd(
    const char* jobz,
    const char* uplo,
    const HAO_INT* n,
    double* a,
    const HAO_INT* lda,
    double* w,
    double* work,
    const HAO_INT* lwork,
    HAO_INT* iwork,
    const HAO_INT* liwork,
    HAO_INT* info );

#define zheevd FORTRAN_WRAPPER(zheevd)
void zheevd(
    const char* jobz,
    const char* uplo,
    const HAO_INT* n,
    HAO_Complex16* a,
    const HAO_INT* lda,
    double* w,
    HAO_Complex16* work,
    const HAO_INT* lwork,
    double* rwork,
    const HAO_INT* lrwork,
    HAO_INT* iwork,
    const HAO_INT* liwork,
    HAO_INT* info );

#define dgetrf FORTRAN_WRAPPER(dgetrf)
void dgetrf(
    const HAO_INT* m,
    const HAO_INT* n,
    double* a,
    const HAO_INT* lda,
    HAO_INT* ipiv,
    HAO_INT* info );

#define zgetrf FORTRAN_WRAPPER(zgetrf)
void zgetrf(
    const HAO_INT* m,
    const HAO_INT* n,
    HAO_Complex16* a,
    const HAO_INT* lda,
    HAO_INT* ipiv,
    HAO_INT* info );

#define zgetri FORTRAN_WRAPPER(zgetri)
void zgetri(
    const HAO_INT* n,
    HAO_Complex16* a,
    const HAO_INT* lda,
    const HAO_INT* ipiv,
    HAO_Complex16* work,
    const HAO_INT* lwork,
    HAO_INT* info );

#define dgetrs FORTRAN_WRAPPER(dgetrs)
void dgetrs(
    const char* trans,
    const HAO_INT* n,
    const HAO_INT* nrhs,
    const double* a,
    const HAO_INT* lda,
    const HAO_INT* ipiv,
    double* b,
    const HAO_INT* ldb,
    HAO_INT* info );

#define zgetrs FORTRAN_WRAPPER(zgetrs)
void zgetrs(
    const char* trans,
    const HAO_INT* n,
    const HAO_INT* nrhs,
    const HAO_Complex16* a,
    const HAO_INT* lda,
    const HAO_INT* ipiv,
    HAO_Complex16* b,
    const HAO_INT* ldb,
    HAO_INT* info );

#define zgeqrf FORTRAN_WRAPPER(zgeqrf)
void zgeqrf(
    const HAO_INT* m,
    const HAO_INT* n,
    HAO_Complex16* a,
    const HAO_INT* lda,
    HAO_Complex16* tau,
    HAO_Complex16* work,
    const HAO_INT* lwork,
    HAO_INT* info );

#define zungqr FORTRAN_WRAPPER(zungqr)
void zungqr(
    const HAO_INT* m,
    const HAO_INT* n,
    const HAO_INT* k,
    HAO_Complex16* a,
    const HAO_INT* lda,
    const HAO_Complex16* tau,
    HAO_Complex16* work,
    const HAO_INT* lwork,
    HAO_INT* info );

#define zgesdd FORTRAN_WRAPPER(zgesdd)
void zgesdd(
    const char* jobz,
    const HAO_INT* m,
    const HAO_INT* n,
    HAO_Complex16* a,
    const HAO_INT* lda,
    double* s,
    HAO_Complex16* u,
    const HAO_INT* ldu,
    HAO_Complex16* vt,
    const HAO_INT* ldvt,
    HAO_Complex16* work,
    const HAO_INT* lwork,
    double* rwork,
    HAO_INT* iwork,
    HAO_INT* info );

#define zgesvd FORTRAN_WRAPPER(zgesvd)
void zgesvd(
    const char* jobu,
    const char* jobvt,
    const HAO_INT* m,
    const HAO_INT* n,
    HAO_Complex16* a,
    const HAO_INT* lda,
    double* s,
    HAO_Complex16* u,
    const HAO_INT* ldu,
    HAO_Complex16* vt,
    const HAO_INT* ldvt,
    HAO_Complex16* work,
    const HAO_INT* lwork,
    double* rwork, HAO_INT* info );

#define dsteqr FORTRAN_WRAPPER(dsteqr)
void dsteqr(
    const char* compz,
    const HAO_INT* n,
    double* d,
    double* e,
    double* z,
    const HAO_INT* ldz,
    double* work,
    HAO_INT* info );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CUSTOMIZED_LAPACK_H_ */


