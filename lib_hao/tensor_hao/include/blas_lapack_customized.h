#ifndef BLAS_LAPACK_CUSTOMIZED_H
#define BLAS_LAPACK_CUSTOMIZED_H

#ifdef FORTRAN_NO_UNDERSCORE
#define F77NAME(x) x
#else
#define F77NAME(x) x##_
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef BLAS_LAPACK_Complex8
typedef struct
{
  float real, imag;
} BLAS_LAPACK_Complex8;
#endif

#ifndef BLAS_LAPACK_Complex16
typedef struct
{
  double real, imag;
} BLAS_LAPACK_Complex16;
#endif


void F77NAME(sgemm)(const char *transa, const char *transb, const int *m, const int *n, const int *k,
           const float *alpha, const float *a, const int *lda, const float *b, const int *ldb,
           const float *beta, float *c, const int *ldc);

void F77NAME(dgemm)(const char *transa, const char *transb, const int *m, const int *n, const int *k,
           const double *alpha, const double *a, const int *lda, const double *b, const int *ldb,
           const double *beta, double *c, const int *ldc);

void F77NAME(cgemm)(const char *transa, const char *transb, const int *m, const int *n, const int *k,
           const BLAS_LAPACK_Complex8 *alpha, const BLAS_LAPACK_Complex8 *a, const int *lda,
           const BLAS_LAPACK_Complex8 *b, const int *ldb, const BLAS_LAPACK_Complex8 *beta,
           BLAS_LAPACK_Complex8 *c, const int *ldc);

void F77NAME(zgemm)(const char *transa, const char *transb, const int *m, const int *n, const int *k,
           const BLAS_LAPACK_Complex16 *alpha, const BLAS_LAPACK_Complex16 *a, const int *lda,
           const BLAS_LAPACK_Complex16 *b, const int *ldb, const BLAS_LAPACK_Complex16 *beta,
           BLAS_LAPACK_Complex16 *c, const int *ldc);

void F77NAME(dsyevd)( const char* jobz, const char* uplo, const int* n, double* a,
             const int* lda, double* w, double* work, const int* lwork,
             int* iwork, const int* liwork, int* info );

void F77NAME(zheev)( const char* jobz, const char* uplo, const int* n,
            BLAS_LAPACK_Complex16* a, const int* lda, double* w,
            BLAS_LAPACK_Complex16* work, const int* lwork, double* rwork,
            int* info );

void F77NAME(zheevd)( const char* jobz, const char* uplo, const int* n,
             BLAS_LAPACK_Complex16* a, const int* lda, double* w,
             BLAS_LAPACK_Complex16* work, const int* lwork, double* rwork,
             const int* lrwork, int* iwork, const int* liwork,
             int* info );

void F77NAME(zgetrf)( const int* m, const int* n, BLAS_LAPACK_Complex16* a,
             const int* lda, int* ipiv, int* info );

void F77NAME(zgetri)( const int* n, BLAS_LAPACK_Complex16* a, const int* lda,
             const int* ipiv, BLAS_LAPACK_Complex16* work, const int* lwork,
             int* info );

void F77NAME(zgetrs)( const char* trans, const int* n, const int* nrhs,
             const BLAS_LAPACK_Complex16* a, const int* lda, const int* ipiv,
             BLAS_LAPACK_Complex16* b, const int* ldb, int* info );

void F77NAME(zgeqrf)( const int* m, const int* n, BLAS_LAPACK_Complex16* a,
             const int* lda, BLAS_LAPACK_Complex16* tau, BLAS_LAPACK_Complex16* work,
             const int* lwork, int* info );

void F77NAME(zungqr)( const int* m, const int* n, const int* k,
             BLAS_LAPACK_Complex16* a, const int* lda, const BLAS_LAPACK_Complex16* tau,
             BLAS_LAPACK_Complex16* work, const int* lwork, int* info );

void F77NAME(zgesdd)( const char* jobz, const int* m, const int* n,
             BLAS_LAPACK_Complex16* a, const int* lda, double* s, BLAS_LAPACK_Complex16* u,
             const int* ldu, BLAS_LAPACK_Complex16* vt, const int* ldvt,
             BLAS_LAPACK_Complex16* work, const int* lwork, double* rwork,
             int* iwork, int* info );

void F77NAME(zgesvd)( const char* jobu, const char* jobvt, const int* m,
             const int* n, BLAS_LAPACK_Complex16* a, const int* lda, double* s,
             BLAS_LAPACK_Complex16* u, const int* ldu, BLAS_LAPACK_Complex16* vt,
             const int* ldvt, BLAS_LAPACK_Complex16* work, const int* lwork,
             double* rwork, int* info );

void F77NAME(slarnv)( const int* idist, int* iseed, const int* n,
             float* x );

void F77NAME(dlarnv)( const int* idist, int* iseed, const int* n,
             double* x );

void F77NAME(clarnv)( const int* idist, int* iseed, const int* n,
             BLAS_LAPACK_Complex8* x );

void F77NAME(zlarnv)( const int* idist, int* iseed, const int* n,
             BLAS_LAPACK_Complex16* x );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
