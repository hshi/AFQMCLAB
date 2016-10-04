#ifndef _CUSTOMIZED_BLAS_H_
#define _CUSTOMIZED_BLAS_H_

#include "Hao_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

//===============================
//FUNTION NAME WITH NO UNDERSCORE
//===============================

/* Upper case declaration */

void XERBLA(const char *srname, const int *info, const int lsrname);
int LSAME(const char *ca, const char *cb, const HAO_INT lca, const HAO_INT lcb);

/* BLAS Level1 */

float   SCABS1(const HAO_Complex8 *c);
float   SASUM(const HAO_INT *n, const float *x, const HAO_INT *incx);
void    SAXPY(const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx, float *y, const HAO_INT *incy);
void    SAXPBY(const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx, const float *beta, float *y, const HAO_INT *incy);
void    SAXPYI(const HAO_INT *nz, const float *a, const float *x, const HAO_INT *indx,float *y);
float   SCASUM(const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx);
float   SCNRM2(const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx);
void    SCOPY(const HAO_INT *n, const float *x, const HAO_INT *incx, float *y, const HAO_INT *incy);
float   SDOT(const HAO_INT *n, const float *x, const HAO_INT *incx, const float *y, const HAO_INT *incy);
float   SDSDOT(const HAO_INT *n, const float *sb, const float *x, const HAO_INT *incx, const float *y, const HAO_INT *incy);
float   SDOTI(const HAO_INT *nz, const float *x, const HAO_INT *indx, const float *y);
void    SGTHR(const HAO_INT *nz, const float *y, float *x, const HAO_INT *indx);
void    SGTHRZ(const HAO_INT *nz, float *y, float *x, const HAO_INT *indx);
float   SNRM2(const HAO_INT *n, const float *x, const HAO_INT *incx);
void    SROT(const HAO_INT *n, float *x, const HAO_INT *incx, float *y, const HAO_INT *incy, const float *c, const float *s);
void    SROTG(float *a,float *b,float *c,float *s);
void    SROTI(const HAO_INT *nz, float *x, const HAO_INT *indx, float *y, const float *c, const float *s);
void    SROTM(const HAO_INT *n, float *x, const HAO_INT *incx, float *y, const HAO_INT *incy, const float *param);
void    SROTMG(float *d1, float *d2, float *x1, const float *y1, float *param);
void    SSCAL(const HAO_INT *n, const float *a, float *x, const HAO_INT *incx);
void    SSCTR(const HAO_INT *nz, const float *x, const HAO_INT *indx, float *y);
void    SSWAP(const HAO_INT *n, float *x, const HAO_INT *incx, float *y, const HAO_INT *incy);
HAO_INT ISAMAX(const HAO_INT *n, const float *x, const HAO_INT *incx);
HAO_INT ISAMIN(const HAO_INT *n, const float *x, const HAO_INT *incx);

void    CAXPY(const HAO_INT *n, const HAO_Complex8 *alpha, const HAO_Complex8 *x, const HAO_INT *incx, HAO_Complex8 *y, const HAO_INT *incy);
void    CAXPBY(const HAO_INT *n, const HAO_Complex8 *alpha, const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *beta, HAO_Complex8 *y, const HAO_INT *incy);
void    CAXPYI(const HAO_INT *nz, const HAO_Complex8 *a, const HAO_Complex8 *x, const HAO_INT *indx, HAO_Complex8 *y);
void    CCOPY(const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx, HAO_Complex8 *y, const HAO_INT *incy);
void    CDOTC(HAO_Complex8 *pres, const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx, const  HAO_Complex8 *y, const HAO_INT *incy);
void    CDOTCI(HAO_Complex8 *pres, const HAO_INT *nz, const HAO_Complex8 *x, const HAO_INT *indx, const HAO_Complex8 *y);
void    CDOTU(HAO_Complex8 *pres, const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx, const  HAO_Complex8 *y, const HAO_INT *incy);
void    CDOTUI(HAO_Complex8 *pres, const HAO_INT *nz, const HAO_Complex8 *x, const HAO_INT *indx, const HAO_Complex8 *y);
void    CGTHR(const HAO_INT *nz, const HAO_Complex8 *y, HAO_Complex8 *x, const HAO_INT *indx);
void    CGTHRZ(const HAO_INT *nz, HAO_Complex8 *y, HAO_Complex8 *x, const HAO_INT *indx);
void    CROTG(HAO_Complex8 *a, const HAO_Complex8 *b, float *c, HAO_Complex8 *s);
void    CSCAL(const HAO_INT *n, const HAO_Complex8 *a, HAO_Complex8 *x, const HAO_INT *incx);
void    CSCTR(const HAO_INT *nz, const HAO_Complex8 *x, const HAO_INT *indx, HAO_Complex8 *y);
void    CSROT(const HAO_INT *n, HAO_Complex8 *x, const HAO_INT *incx, HAO_Complex8 *y, const HAO_INT *incy, const float *c, const float *s);
void    CSSCAL(const HAO_INT *n, const float *a, HAO_Complex8 *x, const HAO_INT *incx);
void    CSWAP(const HAO_INT *n, HAO_Complex8 *x, const HAO_INT *incx, HAO_Complex8 *y, const HAO_INT *incy);
HAO_INT ICAMAX(const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx);
HAO_INT ICAMIN(const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx);

double  DCABS1(const HAO_Complex16 *z);
double  DASUM(const HAO_INT *n, const double *x, const HAO_INT *incx);
void    DAXPY(const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx, double *y, const HAO_INT *incy);
void    DAXPBY(const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx, const double *beta, double *y, const HAO_INT *incy);
void    DAXPYI(const HAO_INT *nz, const double *a, const double *x, const HAO_INT *indx, double *y);
void    DCOPY(const HAO_INT *n, const double *x, const HAO_INT *incx, double *y, const HAO_INT *incy);
double  DDOT(const  HAO_INT *n, const double *x, const HAO_INT *incx, const double *y, const HAO_INT *incy);
double  DSDOT(const HAO_INT *n, const float *x, const HAO_INT *incx, const float *y, const HAO_INT *incy);
double  DDOTI(const HAO_INT *nz, const double *x, const HAO_INT *indx, const double *y);
void    DGTHR(const HAO_INT *nz, const double *y, double *x, const HAO_INT *indx);
void    DGTHRZ(const HAO_INT *nz, double *y, double *x, const HAO_INT *indx);
double  DNRM2(const HAO_INT *n, const double *x, const HAO_INT *incx);
void    DROT(const HAO_INT *n, double *x, const HAO_INT *incx, double *y, const HAO_INT *incy, const double *c, const double *s);
void    DROTG(double *a,double *b,double *c,double *s);
void    DROTI(const HAO_INT *nz, double *x, const HAO_INT *indx, double *y, const double *c, const double *s);
void    DROTM(const HAO_INT *n, double *x, const HAO_INT *incx, double *y, const HAO_INT *incy, const double *param);
void    DROTMG(double *d1, double *d2, double *x1, const double *y1, double *param);
void    DSCAL(const HAO_INT *n, const double *a, double *x, const HAO_INT *incx);
void    DSCTR(const HAO_INT *nz, const double *x, const HAO_INT *indx, double *y);
void    DSWAP(const HAO_INT *n, double *x, const HAO_INT *incx, double *y, const HAO_INT *incy);
double  DZASUM(const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx);
double  DZNRM2(const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx);
HAO_INT IDAMAX(const HAO_INT *n, const double *x, const HAO_INT *incx);
HAO_INT IDAMIN(const HAO_INT *n, const double *x, const HAO_INT *incx);

void    ZAXPY(const HAO_INT *n, const HAO_Complex16 *alpha, const HAO_Complex16 *x, const HAO_INT *incx, HAO_Complex16 *y, const HAO_INT *incy);
void    ZAXPBY(const HAO_INT *n, const HAO_Complex16 *alpha, const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *beta, HAO_Complex16 *y, const HAO_INT *incy);
void    ZAXPYI(const HAO_INT *nz, const HAO_Complex16 *a, const HAO_Complex16 *x, const HAO_INT *indx, HAO_Complex16 *y);
void    ZCOPY(const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx, HAO_Complex16 *y, const HAO_INT *incy);
void    ZDOTC(HAO_Complex16 *pres, const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx, const  HAO_Complex16 *y, const HAO_INT *incy);
void    ZDOTCI(HAO_Complex16 *pres,const HAO_INT *nz, const HAO_Complex16 *x, const HAO_INT *indx, const HAO_Complex16 *y);
void    ZDOTU(HAO_Complex16 *pres, const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *y, const HAO_INT *incy);
void    ZDOTUI(HAO_Complex16 *pres, const HAO_INT *nz, const HAO_Complex16 *x, const HAO_INT *indx, const HAO_Complex16 *y);
void    ZDROT(const HAO_INT *n, HAO_Complex16 *x, const HAO_INT *incx, HAO_Complex16 *y, const HAO_INT *incy, const double *c, const double *s);
void    ZDSCAL(const HAO_INT *n, const double *a, HAO_Complex16 *x, const HAO_INT *incx);
void    ZGTHR(const HAO_INT *nz, const HAO_Complex16 *y, HAO_Complex16 *x, const HAO_INT *indx);
void    ZGTHRZ(const HAO_INT *nz, HAO_Complex16 *y, HAO_Complex16 *x, const HAO_INT *indx);
void    ZROTG(HAO_Complex16 *a, const HAO_Complex16 *b, double *c, HAO_Complex16 *s);
void    ZSCAL(const HAO_INT *n, const HAO_Complex16 *a, HAO_Complex16 *x, const HAO_INT *incx);
void    ZSCTR(const HAO_INT *nz, const HAO_Complex16 *x, const HAO_INT *indx, HAO_Complex16 *y);
void    ZSWAP(const HAO_INT *n, HAO_Complex16 *x, const HAO_INT *incx, HAO_Complex16 *y, const HAO_INT *incy);
HAO_INT IZAMAX(const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx);
HAO_INT IZAMIN(const  HAO_INT *n,const  HAO_Complex16 *x, const HAO_INT *incx);

/* BLAS Level2 */

void SGBMV(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_INT *kl, const HAO_INT *ku,
           const float *alpha, const float *a, const HAO_INT *lda, const float *x, const HAO_INT *incx,
           const float *beta, float *y, const HAO_INT *incy);
void SGEMV(const char *trans, const HAO_INT *m, const HAO_INT *n, const float *alpha,
           const float *a, const HAO_INT *lda, const float *x, const HAO_INT *incx,
           const float *beta, float *y, const HAO_INT *incy);
void SGER(const HAO_INT *m, const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx,
          const float *y, const HAO_INT *incy, float *a, const HAO_INT *lda);
void SSBMV(const char *uplo, const HAO_INT *n, const HAO_INT *k,
           const float *alpha, const float *a, const HAO_INT *lda, const float *x, const HAO_INT *incx,
           const float *beta, float *y, const HAO_INT *incy);
void SSPMV(const char *uplo, const HAO_INT *n, const float *alpha, const float *ap,
           const float *x, const HAO_INT *incx, const float *beta, float *y, const HAO_INT *incy);
void SSPR(const char *uplo, const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx, float *ap);
void SSPR2(const char *uplo, const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx,
           const float *y, const HAO_INT *incy, float *ap);
void SSYMV(const char *uplo, const HAO_INT *n, const float *alpha, const float *a, const HAO_INT *lda,
           const float *x, const HAO_INT *incx, const float *beta, float *y, const HAO_INT *incy);
void SSYR(const char *uplo, const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx,
          float *a, const HAO_INT *lda);
void SSYR2(const char *uplo, const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx,
           const float *y, const HAO_INT *incy, float *a, const HAO_INT *lda);
void STBMV(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const float *a, const HAO_INT *lda, float *x, const HAO_INT *incx);
void STBSV(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const float *a, const HAO_INT *lda, float *x, const HAO_INT *incx);
void STPMV(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const float *ap, float *x, const HAO_INT *incx);
void STPSV(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const float *ap, float *x, const HAO_INT *incx);
void STRMV(const char *uplo, const char *transa, const char *diag, const HAO_INT *n,
           const float *a, const HAO_INT *lda, float *b, const HAO_INT *incx);
void STRSV(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const float *a, const HAO_INT *lda, float *x, const HAO_INT *incx);
void SGEM2VU(const HAO_INT *m, const HAO_INT *n, const float *alpha, const float *a, const HAO_INT *lda,
           const float *x1, const HAO_INT *incx1, const float *x2, const HAO_INT *incx2,
           const float *beta, float *y1, const HAO_INT *incy1, float *y2, const HAO_INT *incy2);

void CGBMV(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_INT *kl, const HAO_INT *ku,
           const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *beta,
           HAO_Complex8 *y, const HAO_INT *incy);
void CGEMV(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, const HAO_Complex8 *x, const HAO_INT *incx,
           const HAO_Complex8 *beta, HAO_Complex8 *y, const HAO_INT *incy);
void CGERC(const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *y, const HAO_INT *incy,
           HAO_Complex8 *a, const HAO_INT *lda);
void CGERU(const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *y, const HAO_INT *incy,
           HAO_Complex8 *a, const HAO_INT *lda);
void CHBMV(const char *uplo, const HAO_INT *n, const HAO_INT *k, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, const HAO_Complex8 *x, const HAO_INT *incx,
           const HAO_Complex8 *beta, HAO_Complex8 *y, const HAO_INT *incy);
void CHEMV(const char *uplo, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, const HAO_Complex8 *x, const HAO_INT *incx,
           const HAO_Complex8 *beta, HAO_Complex8 *y, const HAO_INT *incy);
void CHER(const char *uplo, const HAO_INT *n, const float *alpha, const HAO_Complex8 *x, const HAO_INT *incx,
          HAO_Complex8 *a, const HAO_INT *lda);
void CHER2(const char *uplo, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *y, const HAO_INT *incy,
           HAO_Complex8 *a, const HAO_INT *lda);
void CHPMV(const char *uplo, const HAO_INT *n, const HAO_Complex8 *alpha, const HAO_Complex8 *ap,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *beta,
           HAO_Complex8 *y, const HAO_INT *incy);
void CHPR(const char *uplo, const HAO_INT *n, const float *alpha, const HAO_Complex8 *x, const HAO_INT *incx,
          HAO_Complex8 *ap);
void CHPR2(const char *uplo, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *y, const HAO_INT *incy,
           HAO_Complex8 *ap);
void CTBMV(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex8 *a, const HAO_INT *lda, HAO_Complex8 *x, const HAO_INT *incx);
void CTBSV(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex8 *a, const HAO_INT *lda, HAO_Complex8 *x, const HAO_INT *incx);
void CTPMV(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex8 *ap, HAO_Complex8 *x, const HAO_INT *incx);
void CTPSV(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex8 *ap, HAO_Complex8 *x, const HAO_INT *incx);
void CTRMV(const char *uplo, const char *transa, const char *diag, const HAO_INT *n,
           const HAO_Complex8 *a, const HAO_INT *lda, HAO_Complex8 *b, const HAO_INT *incx);
void CTRSV(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex8 *a, const HAO_INT *lda, HAO_Complex8 *x, const HAO_INT *incx);
void CGEM2VC(const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, const HAO_Complex8 *x1, const HAO_INT *incx1,
           const HAO_Complex8 *x2, const HAO_INT *incx2, const HAO_Complex8 *beta,
           HAO_Complex8 *y1, const HAO_INT *incy1, HAO_Complex8 *y2, const HAO_INT *incy2);
void SCGEMV(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const float *a, const HAO_INT *lda, const HAO_Complex8 *x, const HAO_INT *incx,
           const HAO_Complex8 *beta, HAO_Complex8 *y, const HAO_INT *incy);

void DGBMV(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_INT *kl, const HAO_INT *ku,
           const double *alpha, const double *a, const HAO_INT *lda, const double *x, const HAO_INT *incx,
           const double *beta, double *y, const HAO_INT *incy);
void DGEMV(const char *trans, const HAO_INT *m, const HAO_INT *n, const double *alpha,
           const double *a, const HAO_INT *lda, const double *x, const HAO_INT *incx,
           const double *beta, double *y, const HAO_INT *incy);
void DGER(const HAO_INT *m, const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx,
          const double *y, const HAO_INT *incy, double *a, const HAO_INT *lda);
void DSBMV(const char *uplo, const HAO_INT *n, const HAO_INT *k, const double *alpha,
           const double *a, const HAO_INT *lda, const double *x, const HAO_INT *incx,
           const double *beta, double *y, const HAO_INT *incy);
void DSPMV(const char *uplo, const HAO_INT *n, const double *alpha, const double *ap,
           const double *x, const HAO_INT *incx, const double *beta, double *y, const HAO_INT *incy);
void DSPR(const char *uplo, const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx, double *ap);
void DSPR2(const char *uplo, const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx,
           const double *y, const HAO_INT *incy, double *ap);
void DSYMV(const char *uplo, const HAO_INT *n, const double *alpha, const double *a, const HAO_INT *lda,
           const double *x, const HAO_INT *incx, const double *beta, double *y, const HAO_INT *incy);
void DSYR(const char *uplo, const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx,
          double *a, const HAO_INT *lda);
void DSYR2(const char *uplo, const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx,
           const double *y, const HAO_INT *incy, double *a, const HAO_INT *lda);
void DTBMV(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const double *a, const HAO_INT *lda, double *x, const HAO_INT *incx);
void DTBSV(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const double *a, const HAO_INT *lda, double *x, const HAO_INT *incx);
void DTPMV(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const double *ap, double *x, const HAO_INT *incx);
void DTPSV(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const double *ap, double *x, const HAO_INT *incx);
void DTRMV(const char *uplo, const char *transa, const char *diag, const HAO_INT *n,
           const double *a, const HAO_INT *lda, double *b, const HAO_INT *incx);
void DTRSV(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const double *a, const HAO_INT *lda, double *x, const HAO_INT *incx);
void DGEM2VU(const HAO_INT *m, const HAO_INT *n, const double *alpha,
           const double *a, const HAO_INT *lda, const double *x1, const HAO_INT *incx1,
           const double *x2, const HAO_INT *incx2, const double *beta,
           double *y1, const HAO_INT *incy1, double *y2, const HAO_INT *incy2);

void ZGBMV(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_INT *kl, const HAO_INT *ku,
           const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *beta,
           HAO_Complex16 *y, const HAO_INT *incy);
void ZGEMV(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *beta, HAO_Complex16 *y, const HAO_INT *incy);
void ZGERC(const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *y, const HAO_INT *incy,
           HAO_Complex16 *a, const HAO_INT *lda);
void ZGERU(const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *y, const HAO_INT *incy,
           HAO_Complex16 *a, const HAO_INT *lda);
void ZHBMV(const char *uplo, const HAO_INT *n, const HAO_INT *k, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *beta, HAO_Complex16 *y, const HAO_INT *incy);
void ZHEMV(const char *uplo, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *beta, HAO_Complex16 *y, const HAO_INT *incy);
void ZHER(const char *uplo, const HAO_INT *n, const double *alpha,
          const HAO_Complex16 *x, const HAO_INT *incx, HAO_Complex16 *a, const HAO_INT *lda);
void ZHER2(const char *uplo, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *y, const HAO_INT *incy,
           HAO_Complex16 *a, const HAO_INT *lda);
void ZHPMV(const char *uplo, const HAO_INT *n, const HAO_Complex16 *alpha, const HAO_Complex16 *ap,
           const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *beta,
           HAO_Complex16 *y, const HAO_INT *incy);
void ZHPR(const char *uplo, const HAO_INT *n, const double *alpha, const HAO_Complex16 *x,
          const HAO_INT *incx, HAO_Complex16 *ap);
void ZHPR2(const char *uplo, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *y, const HAO_INT *incy,
           HAO_Complex16 *ap);
void ZTBMV(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *x, const HAO_INT *incx);
void ZTBSV(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *x, const HAO_INT *incx);
void ZTPMV(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex16 *ap, HAO_Complex16 *x, const HAO_INT *incx);
void ZTPSV(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           HAO_Complex16 *ap, HAO_Complex16 *x, const HAO_INT *incx);
void ZTRMV(const char *uplo, const char *transa, const char *diag, const HAO_INT *n,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *b, const HAO_INT *incx);
void ZTRSV(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *x, const HAO_INT *incx);
void ZGEM2VC(const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, const HAO_Complex16 *x1, const HAO_INT *incx1,
           const HAO_Complex16 *x2, const HAO_INT *incx2, const HAO_Complex16 *beta,
           HAO_Complex16 *y1, const HAO_INT *incy1, HAO_Complex16 *y2, const HAO_INT *incy2);
void DZGEMV(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const double *a, const HAO_INT *lda, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *beta, HAO_Complex16 *y, const HAO_INT *incy);

/* BLAS Level3 */

void SGEMM(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const float *alpha, const float *a, const HAO_INT *lda, const float *b, const HAO_INT *ldb,
           const float *beta, float *c, const HAO_INT *ldc);
void SGEMM_BATCH(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const float *alpha_array, const float **a_array, const HAO_INT *lda_array, const float **b_array, const HAO_INT *ldb_array,
           const float *beta_array, float **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void SGEMMT(const char *uplo, const char *transa, const char *transb, const HAO_INT *n, const HAO_INT *k,
            const float *alpha, const float *a, const HAO_INT *lda, const float *b, const HAO_INT *ldb,
            const float *beta, float *c, const HAO_INT *ldc);
void SSYMM(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const float *alpha, const float *a, const HAO_INT *lda, const float *b, const HAO_INT *ldb,
           const float *beta, float *c, const HAO_INT *ldc);
void SSYR2K(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const float *alpha, const float *a, const HAO_INT *lda, const float *b, const HAO_INT *ldb,
            const float *beta, float *c, const HAO_INT *ldc);
void SSYRK(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const float *alpha, const float *a, const HAO_INT *lda,
           const float *beta, float *c, const HAO_INT *ldc);
void STRMM(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const float *alpha, const float *a, const HAO_INT *lda,
           float *b, const HAO_INT *ldb);
void STRSM(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const float *alpha, const float *a, const HAO_INT *lda,
           float *b, const HAO_INT *ldb);

void CGEMM(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
           const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
           HAO_Complex8 *c, const HAO_INT *ldc);

void CGEMM_BATCH(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const HAO_Complex8 *alpha_array, const HAO_Complex8 **a_array, const HAO_INT *lda_array, const HAO_Complex8 **b_array, const HAO_INT *ldb_array,
           const HAO_Complex8 *beta_array, HAO_Complex8 **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void SCGEMM(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex8 *alpha, const float *a, const HAO_INT *lda,
           const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
           HAO_Complex8 *c, const HAO_INT *ldc);
void CGEMM3M(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
             const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
             const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
             HAO_Complex8 *c, const HAO_INT *ldc);
void CGEMM3M_BATCH(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const HAO_Complex8 *alpha_array, const HAO_Complex8 **a_array, const HAO_INT *lda_array, const HAO_Complex8 **b_array, const HAO_INT *ldb_array,
           const HAO_Complex8 *beta_array, HAO_Complex8 **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void CGEMMT(const char *uplo, const char *transa, const char *transb, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
            const HAO_Complex8 *b, const HAO_INT *ldb,
            const HAO_Complex8 *beta, HAO_Complex8 *c, const HAO_INT *ldc);

void CHEMM(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
           const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
           HAO_Complex8 *c, const HAO_INT *ldc);
void CHER2K(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
            const HAO_Complex8 *b, const HAO_INT *ldb, const float *beta,
            HAO_Complex8 *c, const HAO_INT *ldc);
void CHERK(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const float *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
           const float *beta, HAO_Complex8 *c, const HAO_INT *ldc);
void CSYMM(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, const HAO_Complex8 *b, const HAO_INT *ldb,
           const HAO_Complex8 *beta, HAO_Complex8 *c, const HAO_INT *ldc);
void CSYR2K(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
            const HAO_Complex8 *b, const HAO_INT *ldb,
            const HAO_Complex8 *beta, HAO_Complex8 *c, const HAO_INT *ldc);
void CSYRK(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
           const HAO_Complex8 *beta, HAO_Complex8 *c, const HAO_INT *ldc);
void CTRMM(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda,
           HAO_Complex8 *b, const HAO_INT *ldb);
void CTRSM(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda,
           HAO_Complex8 *b, const HAO_INT *ldb);

void DGEMM(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const double *alpha, const double *a, const HAO_INT *lda, const double *b, const HAO_INT *ldb,
           const double *beta, double *c, const HAO_INT *ldc);

void DGEMM_BATCH(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const double *alpha_array, const double **a_array, const HAO_INT *lda_array, const double **b_array, const HAO_INT *ldb_array,
           const double *beta_array, double **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void DGEMMT(const char *uplo, const char *transa, const char *transb, const HAO_INT *n, const HAO_INT *k,
            const double *alpha, const double *a, const HAO_INT *lda, const double *b, const HAO_INT *ldb,
            const double *beta, double *c, const HAO_INT *ldc);

void DSYMM(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const double *alpha, const double *a, const HAO_INT *lda, const double *b, const HAO_INT *ldb,
           const double *beta, double *c, const HAO_INT *ldc);
void DSYR2K(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const double *alpha, const double *a, const HAO_INT *lda, const double *b, const HAO_INT *ldb,
            double *beta, double *c, const HAO_INT *ldc);
void DSYRK(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const double *alpha, const double *a, const HAO_INT *lda, const double *beta,
           double *c, const HAO_INT *ldc);
void DTRMM(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const double *alpha, const double *a, const HAO_INT *lda,
           double *b, const HAO_INT *ldb);
void DTRSM(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const double *alpha, const double *a, const HAO_INT *lda,
           double *b, const HAO_INT *ldb);

void ZGEMM(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
           HAO_Complex16 *c, const HAO_INT *ldc);
void ZGEMM_BATCH(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const HAO_Complex16 *alpha_array, const HAO_Complex16 **a_array, const HAO_INT *lda_array, const HAO_Complex16 **b_array, const HAO_INT *ldb_array,
           const HAO_Complex16 *beta_array, HAO_Complex16 **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void DZGEMM(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex16 *alpha, const double *a, const HAO_INT *lda,
           const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
           HAO_Complex16 *c, const HAO_INT *ldc);
void ZGEMM3M(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
             const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
             const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
             HAO_Complex16 *c, const HAO_INT *ldc);
void ZGEMM3M_BATCH(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const HAO_Complex16 *alpha_array, const HAO_Complex16 **a_array, const HAO_INT *lda_array, const HAO_Complex16 **b_array, const HAO_INT *ldb_array,
           const HAO_Complex16 *beta_array, HAO_Complex16 **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void ZGEMMT(const char *uplo, const char *transa, const char *transb, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
            const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
            HAO_Complex16 *c, const HAO_INT *ldc);
void ZHEMM(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
           HAO_Complex16 *c, const HAO_INT *ldc);
void ZHER2K(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
            const HAO_Complex16 *b, const HAO_INT *ldb, const double *beta,
            HAO_Complex16 *c, const HAO_INT *ldc);
void ZHERK(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const double *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const double *beta, HAO_Complex16 *c, const HAO_INT *ldc);
void ZSYMM(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
           HAO_Complex16 *c, const HAO_INT *ldc);
void ZSYR2K(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
            const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
            HAO_Complex16 *c, const HAO_INT *ldc);
void ZSYRK(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const HAO_Complex16 *beta, HAO_Complex16 *c, const HAO_INT *ldc);
void ZTRMM(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *b, const HAO_INT *ldb);
void ZTRSM(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *b, const HAO_INT *ldb);

/* Lower case declaration */

void xerbla(const char *srname, const int *info, const int lsrname);
int lsame(const char *ca, const char *cb, const HAO_INT lca, const HAO_INT lcb);

/* BLAS Level1 */
float   scabs1(const HAO_Complex8 *c);
float   sasum(const HAO_INT *n, const float *x, const HAO_INT *incx);
void    saxpy(const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx, float *y, const HAO_INT *incy);
void    saxpby(const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx, const float *beta, float *y, const HAO_INT *incy);
void    saxpyi(const HAO_INT *nz, const float *a, const float *x, const HAO_INT *indx, float *y);
float   scasum(const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx);
float   scnrm2(const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx);
void    scopy(const HAO_INT *n, const float *x, const HAO_INT *incx, float *y, const HAO_INT *incy);
float   sdot(const HAO_INT *n, const float *x, const HAO_INT *incx, const float *y, const HAO_INT *incy);
float   sdoti(const HAO_INT *nz, const float *x, const HAO_INT *indx, const float *y);
float   sdsdot(const HAO_INT *n, const float *sb, const float *x, const HAO_INT *incx, const float *y, const HAO_INT *incy);
void    sgthr(const HAO_INT *nz, const float *y, float *x, const HAO_INT *indx);
void    sgthrz(const HAO_INT *nz, float *y, float *x, const HAO_INT *indx);
float   snrm2(const HAO_INT *n, const float *x, const HAO_INT *incx);
void    srot(const HAO_INT *n, float *x, const HAO_INT *incx, float *y, const HAO_INT *incy, const float *c, const float *s);
void    srotg(float *a,float *b,float *c,float *s);
void    sroti(const HAO_INT *nz, float *x, const HAO_INT *indx, float *y, const float *c, const float *s);
void    srotm(const HAO_INT *n, float *x, const HAO_INT *incx, float *y, const HAO_INT *incy, const float *param);
void    srotmg(float *d1, float *d2, float *x1, const float *y1, float *param);
void    sscal(const HAO_INT *n, const float *a, float *x, const HAO_INT *incx);
void    ssctr(const HAO_INT *nz, const float *x, const HAO_INT *indx, float *y);
void    sswap(const HAO_INT *n, float *x, const HAO_INT *incx, float *y, const HAO_INT *incy);
HAO_INT isamax(const HAO_INT *n, const float *x, const HAO_INT *incx);
HAO_INT isamin(const HAO_INT *n, const float *x, const HAO_INT *incx);

void    caxpy(const HAO_INT *n, const HAO_Complex8 *alpha, const HAO_Complex8 *x, const HAO_INT *incx, HAO_Complex8 *y, const HAO_INT *incy);
void    caxpby(const HAO_INT *n, const HAO_Complex8 *alpha, const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *beta, HAO_Complex8 *y, const HAO_INT *incy);
void    caxpyi(const HAO_INT *nz, const HAO_Complex8 *a, const HAO_Complex8 *x, const HAO_INT *indx, HAO_Complex8 *y);
void    ccopy(const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx, HAO_Complex8 *y, const HAO_INT *incy);
void    cdotc(HAO_Complex8 *pres, const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *y, const HAO_INT *incy);
void    cdotci(HAO_Complex8 *pres, const HAO_INT *nz, const HAO_Complex8 *x, const HAO_INT *indx, const HAO_Complex8 *y);
void    cdotu(HAO_Complex8 *pres, const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *y, const HAO_INT *incy);
void    cdotui(HAO_Complex8 *pres, const HAO_INT *nz, const HAO_Complex8 *x, const HAO_INT *indx, const HAO_Complex8 *y);
void    cgthr(const HAO_INT *nz, const HAO_Complex8 *y, HAO_Complex8 *x, const HAO_INT *indx);
void    cgthrz(const HAO_INT *nz, HAO_Complex8 *y, HAO_Complex8 *x, const HAO_INT *indx);
void    crotg(HAO_Complex8 *a, const HAO_Complex8 *b, float *c, HAO_Complex8 *s);
void    cscal(const HAO_INT *n, const HAO_Complex8 *a, HAO_Complex8 *x, const HAO_INT *incx);
void    csctr(const HAO_INT *nz, const HAO_Complex8 *x, const HAO_INT *indx, HAO_Complex8 *y);
void    csrot(const HAO_INT *n, HAO_Complex8 *x, const HAO_INT *incx, HAO_Complex8 *y, const HAO_INT *incy, const float *c, const float *s);
void    csscal(const HAO_INT *n, const float *a, HAO_Complex8 *x, const HAO_INT *incx);
void    cswap(const HAO_INT *n, HAO_Complex8 *x, const HAO_INT *incx, HAO_Complex8 *y, const HAO_INT *incy);
HAO_INT icamax(const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx);
HAO_INT icamin(const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx);

double  dcabs1(const HAO_Complex16 *z);
double  dasum(const HAO_INT *n, const double *x, const HAO_INT *incx);
void    daxpy(const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx, double *y, const HAO_INT *incy);
void    daxpby(const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx, const double *beta, double *y, const HAO_INT *incy);
void    daxpyi(const HAO_INT *nz, const double *a, const double *x, const HAO_INT *indx, double *y);
void    dcopy(const HAO_INT *n, const double *x, const HAO_INT *incx, double *y, const HAO_INT *incy);
double  ddot(const HAO_INT *n, const double *x, const HAO_INT *incx, const double *y, const HAO_INT *incy);
double  dsdot(const HAO_INT *n, const float *x, const HAO_INT *incx, const float *y, const HAO_INT *incy);
double  ddoti(const HAO_INT *nz, const double *x, const HAO_INT *indx, const double *y);
void    dgthr(const HAO_INT *nz, const double *y, double *x, const HAO_INT *indx);
void    dgthrz(const HAO_INT *nz, double *y, double *x, const HAO_INT *indx);
double  dnrm2(const HAO_INT *n, const double *x, const HAO_INT *incx);
void    drot(const HAO_INT *n, double *x, const HAO_INT *incx, double *y, const HAO_INT *incy, const double *c, const double *s);
void    drotg(double *a, double *b, double *c, double *s);
void    droti(const HAO_INT *nz, double *x, const HAO_INT *indx, double *y, const double *c, const double *s);
void    drotm(const HAO_INT *n, double *x, const HAO_INT *incx, double *y, const HAO_INT *incy, const double *param);
void    drotmg(double *d1, double *d2, double *x1, const double *y1, double *param);
void    dscal(const HAO_INT *n, const double *a, double *x, const HAO_INT *incx);
void    dsctr(const HAO_INT *nz, const double *x, const HAO_INT *indx, double *y);
void    dswap(const HAO_INT *n, double *x, const HAO_INT *incx, double *y, const HAO_INT *incy);
double  dzasum(const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx);
double  dznrm2(const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx);
HAO_INT idamax(const HAO_INT *n, const double *x, const HAO_INT *incx);
HAO_INT idamin(const HAO_INT *n, const double *x, const HAO_INT *incx);

void    zaxpy(const HAO_INT *n, const HAO_Complex16 *alpha, const HAO_Complex16 *x, const HAO_INT *incx, HAO_Complex16 *y, const HAO_INT *incy);
void    zaxpby(const HAO_INT *n, const HAO_Complex16 *alpha, const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *beta, HAO_Complex16 *y, const HAO_INT *incy);
void    zaxpyi(const HAO_INT *nz, const HAO_Complex16 *a, const HAO_Complex16 *x, const HAO_INT *indx, HAO_Complex16 *y);
void    zcopy(const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx, HAO_Complex16 *y, const HAO_INT *incy);
void    zdotc(HAO_Complex16 *pres, const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *y, const HAO_INT *incy);
void    zdotci(HAO_Complex16 *pres, const HAO_INT *nz, const HAO_Complex16 *x, const HAO_INT *indx, const HAO_Complex16 *y);
void    zdotu(HAO_Complex16 *pres, const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *y, const HAO_INT *incy);
void    zdotui(HAO_Complex16 *pres, const HAO_INT *nz, const HAO_Complex16 *x, const HAO_INT *indx, const HAO_Complex16 *y);
void    zdrot(const HAO_INT *n, HAO_Complex16 *x, const HAO_INT *incx, HAO_Complex16 *y, const HAO_INT *incy, const double *c, const double *s);
void    zdscal(const HAO_INT *n, const double *a, HAO_Complex16 *x, const HAO_INT *incx);
void    zgthr(const HAO_INT *nz, const HAO_Complex16 *y, HAO_Complex16 *x, const HAO_INT *indx);
void    zgthrz(const HAO_INT *nz, HAO_Complex16 *y, HAO_Complex16 *x, const HAO_INT *indx);
void    zrotg(HAO_Complex16 *a, const HAO_Complex16 *b, double *c, HAO_Complex16 *s);
void    zscal(const HAO_INT *n, const HAO_Complex16 *a, HAO_Complex16 *x, const HAO_INT *incx);
void    zsctr(const HAO_INT *nz, const HAO_Complex16 *x, const HAO_INT *indx, HAO_Complex16 *y);
void    zswap(const HAO_INT *n, HAO_Complex16 *x, const HAO_INT *incx, HAO_Complex16 *y, const HAO_INT *incy);
HAO_INT izamax(const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx);
HAO_INT izamin(const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx);

/* blas level2 */

void sgbmv(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_INT *kl, const HAO_INT *ku,
           const float *alpha, const float *a, const HAO_INT *lda, const float *x, const HAO_INT *incx,
           const float *beta, float *y, const HAO_INT *incy);
void sgemv(const char *trans, const HAO_INT *m, const HAO_INT *n, const float *alpha,
           const float *a, const HAO_INT *lda, const float *x, const HAO_INT *incx,
           const float *beta, float *y, const HAO_INT *incy);
void sger(const HAO_INT *m, const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx,
          const float *y, const HAO_INT *incy, float *a, const HAO_INT *lda);
void ssbmv(const char *uplo, const HAO_INT *n, const HAO_INT *k, const float *alpha,
           const float *a, const HAO_INT *lda, const float *x, const HAO_INT *incx,
           const float *beta, float *y, const HAO_INT *incy);
void sspmv(const char *uplo, const HAO_INT *n, const float *alpha, const float *ap,
           const float *x, const HAO_INT *incx, const float *beta, float *y, const HAO_INT *incy);
void sspr(const char *uplo, const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx,
          float *ap);
void sspr2(const char *uplo, const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx,
           const float *y, const HAO_INT *incy, float *ap);
void ssymv(const char *uplo, const HAO_INT *n, const float *alpha, const float *a, const HAO_INT *lda,
           const float *x, const HAO_INT *incx, const float *beta, float *y, const HAO_INT *incy);
void ssyr(const char *uplo, const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx,
          float *a, const HAO_INT *lda);
void ssyr2(const char *uplo, const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx,
           const float *y, const HAO_INT *incy, float *a, const HAO_INT *lda);
void stbmv(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const float *a, const HAO_INT *lda, float *x, const HAO_INT *incx);
void stbsv(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const float *a, const HAO_INT *lda, float *x, const HAO_INT *incx);
void stpmv(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const float *ap,
           float *x, const HAO_INT *incx);
void stpsv(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const float *ap,
           float *x, const HAO_INT *incx);
void strmv(const char *uplo, const char *transa, const char *diag, const HAO_INT *n, const float *a,
           const HAO_INT *lda, float *b, const HAO_INT *incx);
void strsv(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const float *a, const HAO_INT *lda, float *x, const HAO_INT *incx);
void sgem2vu(const HAO_INT *m, const HAO_INT *n, const float *alpha, const float *a, const HAO_INT *lda,
           const float *x1, const HAO_INT *incx1, const float *x2, const HAO_INT *incx2,
           const float *beta, float *y1, const HAO_INT *incy1, float *y2, const HAO_INT *incy2);

void cgbmv(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_INT *kl, const HAO_INT *ku,
           const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *beta,
           HAO_Complex8 *y, const HAO_INT *incy);
void cgemv(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, const HAO_Complex8 *x, const HAO_INT *incx,
           const HAO_Complex8 *beta, HAO_Complex8 *y, const HAO_INT *incy);
void cgerc(const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *y, const HAO_INT *incy,
           HAO_Complex8 *a, const HAO_INT *lda);
void cgeru(const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *y, const HAO_INT *incy,
           HAO_Complex8 *a, const HAO_INT *lda);
void chbmv(const char *uplo, const HAO_INT *n, const HAO_INT *k, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, const HAO_Complex8 *x, const HAO_INT *incx,
           const HAO_Complex8 *beta, HAO_Complex8 *y, const HAO_INT *incy);
void chemv(const char *uplo, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, const HAO_Complex8 *x, const HAO_INT *incx,
           const HAO_Complex8 *beta, HAO_Complex8 *y, const HAO_INT *incy);
void cher(const char *uplo, const HAO_INT *n, const float *alpha, const HAO_Complex8 *x, const HAO_INT *incx,
          HAO_Complex8 *a, const HAO_INT *lda);
void cher2(const char *uplo, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *y, const HAO_INT *incy,
           HAO_Complex8 *a, const HAO_INT *lda);
void chpmv(const char *uplo, const HAO_INT *n, const HAO_Complex8 *alpha, const HAO_Complex8 *ap,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *beta,
           HAO_Complex8 *y, const HAO_INT *incy);
void chpr(const char *uplo, const HAO_INT *n, const float *alpha, const HAO_Complex8 *x, const HAO_INT *incx,
          HAO_Complex8 *ap);
void chpr2(const char *uplo, const HAO_INT *n, const HAO_Complex8 *alpha, const HAO_Complex8 *x, const HAO_INT *incx,
           const HAO_Complex8 *y, const HAO_INT *incy, HAO_Complex8 *ap);
void ctbmv(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex8 *a, const HAO_INT *lda, HAO_Complex8 *x, const HAO_INT *incx);
void ctbsv(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex8 *a, const HAO_INT *lda, HAO_Complex8 *x, const HAO_INT *incx);
void ctpmv(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex8 *ap, HAO_Complex8 *x, const HAO_INT *incx);
void ctpsv(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex8 *ap, HAO_Complex8 *x, const HAO_INT *incx);
void ctrmv(const char *uplo, const char *transa, const char *diag, const HAO_INT *n,
           const HAO_Complex8 *a, const HAO_INT *lda, HAO_Complex8 *b, const HAO_INT *incx);
void ctrsv(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex8 *a, const HAO_INT *lda, HAO_Complex8 *x, const HAO_INT *incx);
void cgem2vc(const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, const HAO_Complex8 *x1, const HAO_INT *incx1,
           const HAO_Complex8 *x2, const HAO_INT *incx2, const HAO_Complex8 *beta,
           HAO_Complex8 *y1, const HAO_INT *incy1, HAO_Complex8 *y2, const HAO_INT *incy2);
void scgemv(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const float *a, const HAO_INT *lda, const HAO_Complex8 *x, const HAO_INT *incx,
           const HAO_Complex8 *beta, HAO_Complex8 *y, const HAO_INT *incy);

void dgbmv(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_INT *kl, const HAO_INT *ku,
           const double *alpha, const double *a, const HAO_INT *lda, const double *x, const HAO_INT *incx,
           const double *beta, double *y, const HAO_INT *incy);
void dgemv(const char *trans, const HAO_INT *m, const HAO_INT *n, const double *alpha,
           const double *a, const HAO_INT *lda, const double *x, const HAO_INT *incx,
           const double *beta, double *y, const HAO_INT *incy);
void dger(const HAO_INT *m, const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx,
          const double *y, const HAO_INT *incy, double *a, const HAO_INT *lda);
void dsbmv(const char *uplo, const HAO_INT *n, const HAO_INT *k, const double *alpha,
           const double *a, const HAO_INT *lda, const double *x, const HAO_INT *incx,
           const double *beta, double *y, const HAO_INT *incy);
void dspmv(const char *uplo, const HAO_INT *n, const double *alpha, const double *ap,
           const double *x, const HAO_INT *incx, const double *beta,
           double *y, const HAO_INT *incy);
void dspr(const char *uplo, const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx,
          double *ap);
void dspr2(const char *uplo, const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx,
           const double *y, const HAO_INT *incy, double *ap);
void dsymv(const char *uplo, const HAO_INT *n, const double *alpha, const double *a, const HAO_INT *lda,
           const double *x, const HAO_INT *incx, const double *beta, double *y, const HAO_INT *incy);
void dsyr(const char *uplo, const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx,
          double *a, const HAO_INT *lda);
void dsyr2(const char *uplo, const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx,
           const double *y, const HAO_INT *incy, double *a, const HAO_INT *lda);
void dtbmv(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const double *a, const HAO_INT *lda, double *x, const HAO_INT *incx);
void dtbsv(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const double *a, const HAO_INT *lda, double *x, const HAO_INT *incx);
void dtpmv(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const double *ap, double *x, const HAO_INT *incx);
void dtpsv(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const double *ap, double *x, const HAO_INT *incx);
void dtrmv(const char *uplo, const char *transa, const char *diag, const HAO_INT *n,
           const double *a, const HAO_INT *lda, double *b, const HAO_INT *incx);
void dtrsv(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const double *a, const HAO_INT *lda, double *x, const HAO_INT *incx);
void dgem2vu(const HAO_INT *m, const HAO_INT *n, const double *alpha,
           const double *a, const HAO_INT *lda, const double *x1, const HAO_INT *incx1,
           const double *x2, const HAO_INT *incx2, const double *beta,
           double *y1, const HAO_INT *incy1, double *y2, const HAO_INT *incy2);

void zgbmv(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_INT *kl, const HAO_INT *ku,
           const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *beta,
           HAO_Complex16 *y, const HAO_INT *incy);
void zgemv(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *beta, HAO_Complex16 *y, const HAO_INT *incy);
void zgerc(const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *y, const HAO_INT *incy, HAO_Complex16 *a, const HAO_INT *lda);
void zgeru(const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *y, const HAO_INT *incy, HAO_Complex16 *a, const HAO_INT *lda);
void zhbmv(const char *uplo, const HAO_INT *n, const HAO_INT *k, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *beta, HAO_Complex16 *y, const HAO_INT *incy);
void zhemv(const char *uplo, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *beta, HAO_Complex16 *y, const HAO_INT *incy);
void zher(const char *uplo, const HAO_INT *n, const double *alpha, const HAO_Complex16 *x, const HAO_INT *incx,
          HAO_Complex16 *a, const HAO_INT *lda);
void zher2(const char *uplo, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *y, const HAO_INT *incy,
           HAO_Complex16 *a, const HAO_INT *lda);
void zhpmv(const char *uplo, const HAO_INT *n, const HAO_Complex16 *alpha, const HAO_Complex16 *ap,
           const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *beta,
           HAO_Complex16 *y, const HAO_INT *incy);
void zhpr(const char *uplo, const HAO_INT *n, const double *alpha, const HAO_Complex16 *x, const HAO_INT *incx,
          HAO_Complex16 *ap);
void zhpr2(const char *uplo, const HAO_INT *n, const HAO_Complex16 *alpha, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *y, const HAO_INT *incy, HAO_Complex16 *ap);
void ztbmv(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *x, const HAO_INT *incx);
void ztbsv(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *x, const HAO_INT *incx);
void ztpmv(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex16 *ap, HAO_Complex16 *x, const HAO_INT *incx);
void ztpsv(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex16 *ap, HAO_Complex16 *x, const HAO_INT *incx);
void ztrmv(const char *uplo, const char *transa, const char *diag, const HAO_INT *n,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *b, const HAO_INT *incx);
void ztrsv(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *x, const HAO_INT *incx);
void zgem2vc(const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, const HAO_Complex16 *x1, const HAO_INT *incx1,
           const HAO_Complex16 *x2, const HAO_INT *incx2, const HAO_Complex16 *beta,
           HAO_Complex16 *y1, const HAO_INT *incy1, HAO_Complex16 *y2, const HAO_INT *incy2);
void dzgemv(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const double *a, const HAO_INT *lda, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *beta, HAO_Complex16 *y, const HAO_INT *incy);

/* blas level3 */

void sgemm(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const float *alpha, const float *a, const HAO_INT *lda, const float *b, const HAO_INT *ldb,
           const float *beta, float *c, const HAO_INT *ldc);
void sgemm_batch(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const float *alpha_array, const float **a_array, const HAO_INT *lda_array, const float **b_array, const HAO_INT *ldb_array,
           const float *beta_array, float **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void sgemmt(const char *uplo, const char *transa, const char *transb, const HAO_INT *n, const HAO_INT *k,
            const float *alpha, const float *a, const HAO_INT *lda, const float *b, const HAO_INT *ldb,
            const float *beta, float *c, const HAO_INT *ldc);
void ssymm(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const float *alpha, const float *a, const HAO_INT *lda, const float *b, const HAO_INT *ldb,
           const float *beta, float *c, const HAO_INT *ldc);
void ssyr2k(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const float *alpha, const float *a, const HAO_INT *lda, const float *b, const HAO_INT *ldb,
            const float *beta, float *c, const HAO_INT *ldc);
void ssyrk(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const float *alpha, const float *a, const HAO_INT *lda, const float *beta,
           float *c, const HAO_INT *ldc);
void strmm(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const float *alpha, const float *a, const HAO_INT *lda,
           float *b, const HAO_INT *ldb);
void strsm(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const float *alpha, const float *a, const HAO_INT *lda,
           float *b, const HAO_INT *ldb);

void cgemm(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
           const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
           HAO_Complex8 *c, const HAO_INT *ldc);
void cgemm_batch(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const HAO_Complex8 *alpha_array, const HAO_Complex8 **a_array, const HAO_INT *lda_array, const HAO_Complex8 **b_array, const HAO_INT *ldb_array,
           const HAO_Complex8 *beta_array, HAO_Complex8 **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void scgemm(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex8 *alpha, const float *a, const HAO_INT *lda,
           const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
           HAO_Complex8 *c, const HAO_INT *ldc);
void cgemm3m(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
             const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
             const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
             HAO_Complex8 *c, const HAO_INT *ldc);
void cgemm3m_batch(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const HAO_Complex8 *alpha_array, const HAO_Complex8 **a_array, const HAO_INT *lda_array, const HAO_Complex8 **b_array, const HAO_INT *ldb_array,
           const HAO_Complex8 *beta_array, HAO_Complex8 **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void cgemmt(const char *uplo, const char *transa, const char *transb, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
            const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
            HAO_Complex8 *c, const HAO_INT *ldc);
void chemm(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
           const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
           HAO_Complex8 *c, const HAO_INT *ldc);
void cher2k(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
            const HAO_Complex8 *b, const HAO_INT *ldb, const float *beta,
            HAO_Complex8 *c, const HAO_INT *ldc);
void cherk(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const float *alpha, const HAO_Complex8 *a, const HAO_INT *lda, const float *beta,
           HAO_Complex8 *c, const HAO_INT *ldc);
void csymm(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
           const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
           HAO_Complex8 *c, const HAO_INT *ldc);
void csyr2k(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
            const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
            HAO_Complex8 *c, const HAO_INT *ldc);
void csyrk(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
           const HAO_Complex8 *beta, HAO_Complex8 *c, const HAO_INT *ldc);
void ctrmm(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, HAO_Complex8 *b, const HAO_INT *ldb);
void ctrsm(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, HAO_Complex8 *b, const HAO_INT *ldb);

void dgemm(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const double *alpha, const double *a, const HAO_INT *lda, const double *b, const HAO_INT *ldb,
           const double *beta, double *c, const HAO_INT *ldc);
void dgemm_batch(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const double *alpha_array, const double **a_array, const HAO_INT *lda_array, const double **b_array, const HAO_INT *ldb_array,
           const double *beta_array, double **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void dgemmt(const char *uplo, const char *transa, const char *transb, const HAO_INT *n, const HAO_INT *k,
            const double *alpha, const double *a, const HAO_INT *lda, const double *b, const HAO_INT *ldb,
            const double *beta, double *c, const HAO_INT *ldc);
void dsymm(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const double *alpha, const double *a, const HAO_INT *lda, const double *b, const HAO_INT *ldb,
           const double *beta, double *c, const HAO_INT *ldc);
void dsyr2k(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const double *alpha, const double *a, const HAO_INT *lda, const double *b, const HAO_INT *ldb,
            const double *beta, double *c, const HAO_INT *ldc);
void dsyrk(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const double *alpha, const double *a, const HAO_INT *lda, const double *beta,
           double *c, const HAO_INT *ldc);
void dtrmm(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const double *alpha, const double *a, const HAO_INT *lda,
           double *b, const HAO_INT *ldb);
void dtrsm(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const double *alpha, const double *a, const HAO_INT *lda,
           double *b, const HAO_INT *ldb);

void zgemm(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
           HAO_Complex16 *c, const HAO_INT *ldc);
void zgemm_batch(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const HAO_Complex16 *alpha_array, const HAO_Complex16 **a_array, const HAO_INT *lda_array, const HAO_Complex16 **b_array, const HAO_INT *ldb_array,
           const HAO_Complex16 *beta_array, HAO_Complex16 **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void dzgemm(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex16 *alpha, const double *a, const HAO_INT *lda,
           const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
           HAO_Complex16 *c, const HAO_INT *ldc);
void zgemm3m(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
             const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
             const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
             HAO_Complex16 *c, const HAO_INT *ldc);
void zgemm3m_batch(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const HAO_Complex16 *alpha_array, const HAO_Complex16 **a_array, const HAO_INT *lda_array, const HAO_Complex16 **b_array, const HAO_INT *ldb_array,
           const HAO_Complex16 *beta_array, HAO_Complex16 **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void zgemmt(const char *uplo, const char *transa, const char *transb, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
            const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
            HAO_Complex16 *c, const HAO_INT *ldc);
void zhemm(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
           HAO_Complex16 *c, const HAO_INT *ldc);
void zher2k(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
            const HAO_Complex16 *b, const HAO_INT *ldb, const double *beta,
            HAO_Complex16 *c, const HAO_INT *ldc);
void zherk(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const double *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const double *beta, HAO_Complex16 *c, const HAO_INT *ldc);
void zsymm(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
           HAO_Complex16 *c, const HAO_INT *ldc);
void zsyr2k(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
            const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
            HAO_Complex16 *c, const HAO_INT *ldc);
void zsyrk(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const HAO_Complex16 *beta, HAO_Complex16 *c, const HAO_INT *ldc);
void ztrmm(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *b, const HAO_INT *ldb);
void ztrsm(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,






//===============================
//FUNTION NAME WITH NO UNDERSCORE
//===============================

/* Upper case declaration */

void XERBLA_(const char *srname, const int *info, const int lsrname);
int LSAME_(const char *ca, const char *cb, const HAO_INT lca, const HAO_INT lcb);

/* BLAS Level1 */

float   SCABS1_(const HAO_Complex8 *c);
float   SASUM_(const HAO_INT *n, const float *x, const HAO_INT *incx);
void    SAXPY_(const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx, float *y, const HAO_INT *incy);
void    SAXPBY_(const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx, const float *beta, float *y, const HAO_INT *incy);
void    SAXPYI_(const HAO_INT *nz, const float *a, const float *x, const HAO_INT *indx,float *y);
float   SCASUM_(const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx);
float   SCNRM2_(const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx);
void    SCOPY_(const HAO_INT *n, const float *x, const HAO_INT *incx, float *y, const HAO_INT *incy);
float   SDOT_(const HAO_INT *n, const float *x, const HAO_INT *incx, const float *y, const HAO_INT *incy);
float   SDSDOT_(const HAO_INT *n, const float *sb, const float *x, const HAO_INT *incx, const float *y, const HAO_INT *incy);
float   SDOTI_(const HAO_INT *nz, const float *x, const HAO_INT *indx, const float *y);
void    SGTHR_(const HAO_INT *nz, const float *y, float *x, const HAO_INT *indx);
void    SGTHRZ_(const HAO_INT *nz, float *y, float *x, const HAO_INT *indx);
float   SNRM2_(const HAO_INT *n, const float *x, const HAO_INT *incx);
void    SROT_(const HAO_INT *n, float *x, const HAO_INT *incx, float *y, const HAO_INT *incy, const float *c, const float *s);
void    SROTG_(float *a,float *b,float *c,float *s);
void    SROTI_(const HAO_INT *nz, float *x, const HAO_INT *indx, float *y, const float *c, const float *s);
void    SROTM_(const HAO_INT *n, float *x, const HAO_INT *incx, float *y, const HAO_INT *incy, const float *param);
void    SROTMG_(float *d1, float *d2, float *x1, const float *y1, float *param);
void    SSCAL_(const HAO_INT *n, const float *a, float *x, const HAO_INT *incx);
void    SSCTR_(const HAO_INT *nz, const float *x, const HAO_INT *indx, float *y);
void    SSWAP_(const HAO_INT *n, float *x, const HAO_INT *incx, float *y, const HAO_INT *incy);
HAO_INT ISAMAX_(const HAO_INT *n, const float *x, const HAO_INT *incx);
HAO_INT ISAMIN_(const HAO_INT *n, const float *x, const HAO_INT *incx);

void    CAXPY_(const HAO_INT *n, const HAO_Complex8 *alpha, const HAO_Complex8 *x, const HAO_INT *incx, HAO_Complex8 *y, const HAO_INT *incy);
void    CAXPBY_(const HAO_INT *n, const HAO_Complex8 *alpha, const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *beta, HAO_Complex8 *y, const HAO_INT *incy);
void    CAXPYI_(const HAO_INT *nz, const HAO_Complex8 *a, const HAO_Complex8 *x, const HAO_INT *indx, HAO_Complex8 *y);
void    CCOPY_(const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx, HAO_Complex8 *y, const HAO_INT *incy);
void    CDOTC_(HAO_Complex8 *pres, const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx, const  HAO_Complex8 *y, const HAO_INT *incy);
void    CDOTCI_(HAO_Complex8 *pres, const HAO_INT *nz, const HAO_Complex8 *x, const HAO_INT *indx, const HAO_Complex8 *y);
void    CDOTU_(HAO_Complex8 *pres, const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx, const  HAO_Complex8 *y, const HAO_INT *incy);
void    CDOTUI_(HAO_Complex8 *pres, const HAO_INT *nz, const HAO_Complex8 *x, const HAO_INT *indx, const HAO_Complex8 *y);
void    CGTHR_(const HAO_INT *nz, const HAO_Complex8 *y, HAO_Complex8 *x, const HAO_INT *indx);
void    CGTHRZ_(const HAO_INT *nz, HAO_Complex8 *y, HAO_Complex8 *x, const HAO_INT *indx);
void    CROTG_(HAO_Complex8 *a, const HAO_Complex8 *b, float *c, HAO_Complex8 *s);
void    CSCAL_(const HAO_INT *n, const HAO_Complex8 *a, HAO_Complex8 *x, const HAO_INT *incx);
void    CSCTR_(const HAO_INT *nz, const HAO_Complex8 *x, const HAO_INT *indx, HAO_Complex8 *y);
void    CSROT_(const HAO_INT *n, HAO_Complex8 *x, const HAO_INT *incx, HAO_Complex8 *y, const HAO_INT *incy, const float *c, const float *s);
void    CSSCAL_(const HAO_INT *n, const float *a, HAO_Complex8 *x, const HAO_INT *incx);
void    CSWAP_(const HAO_INT *n, HAO_Complex8 *x, const HAO_INT *incx, HAO_Complex8 *y, const HAO_INT *incy);
HAO_INT ICAMAX_(const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx);
HAO_INT ICAMIN_(const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx);

double  DCABS1_(const HAO_Complex16 *z);
double  DASUM_(const HAO_INT *n, const double *x, const HAO_INT *incx);
void    DAXPY_(const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx, double *y, const HAO_INT *incy);
void    DAXPBY_(const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx, const double *beta, double *y, const HAO_INT *incy);
void    DAXPYI_(const HAO_INT *nz, const double *a, const double *x, const HAO_INT *indx, double *y);
void    DCOPY_(const HAO_INT *n, const double *x, const HAO_INT *incx, double *y, const HAO_INT *incy);
double  DDOT_(const  HAO_INT *n, const double *x, const HAO_INT *incx, const double *y, const HAO_INT *incy);
double  DSDOT_(const HAO_INT *n, const float *x, const HAO_INT *incx, const float *y, const HAO_INT *incy);
double  DDOTI_(const HAO_INT *nz, const double *x, const HAO_INT *indx, const double *y);
void    DGTHR_(const HAO_INT *nz, const double *y, double *x, const HAO_INT *indx);
void    DGTHRZ_(const HAO_INT *nz, double *y, double *x, const HAO_INT *indx);
double  DNRM2_(const HAO_INT *n, const double *x, const HAO_INT *incx);
void    DROT_(const HAO_INT *n, double *x, const HAO_INT *incx, double *y, const HAO_INT *incy, const double *c, const double *s);
void    DROTG_(double *a,double *b,double *c,double *s);
void    DROTI_(const HAO_INT *nz, double *x, const HAO_INT *indx, double *y, const double *c, const double *s);
void    DROTM_(const HAO_INT *n, double *x, const HAO_INT *incx, double *y, const HAO_INT *incy, const double *param);
void    DROTMG_(double *d1, double *d2, double *x1, const double *y1, double *param);
void    DSCAL_(const HAO_INT *n, const double *a, double *x, const HAO_INT *incx);
void    DSCTR_(const HAO_INT *nz, const double *x, const HAO_INT *indx, double *y);
void    DSWAP_(const HAO_INT *n, double *x, const HAO_INT *incx, double *y, const HAO_INT *incy);
double  DZASUM_(const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx);
double  DZNRM2_(const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx);
HAO_INT IDAMAX_(const HAO_INT *n, const double *x, const HAO_INT *incx);
HAO_INT IDAMIN_(const HAO_INT *n, const double *x, const HAO_INT *incx);

void    ZAXPY_(const HAO_INT *n, const HAO_Complex16 *alpha, const HAO_Complex16 *x, const HAO_INT *incx, HAO_Complex16 *y, const HAO_INT *incy);
void    ZAXPBY_(const HAO_INT *n, const HAO_Complex16 *alpha, const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *beta, HAO_Complex16 *y, const HAO_INT *incy);
void    ZAXPYI_(const HAO_INT *nz, const HAO_Complex16 *a, const HAO_Complex16 *x, const HAO_INT *indx, HAO_Complex16 *y);
void    ZCOPY_(const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx, HAO_Complex16 *y, const HAO_INT *incy);
void    ZDOTC_(HAO_Complex16 *pres, const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx, const  HAO_Complex16 *y, const HAO_INT *incy);
void    ZDOTCI_(HAO_Complex16 *pres,const HAO_INT *nz, const HAO_Complex16 *x, const HAO_INT *indx, const HAO_Complex16 *y);
void    ZDOTU_(HAO_Complex16 *pres, const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *y, const HAO_INT *incy);
void    ZDOTUI_(HAO_Complex16 *pres, const HAO_INT *nz, const HAO_Complex16 *x, const HAO_INT *indx, const HAO_Complex16 *y);
void    ZDROT_(const HAO_INT *n, HAO_Complex16 *x, const HAO_INT *incx, HAO_Complex16 *y, const HAO_INT *incy, const double *c, const double *s);
void    ZDSCAL_(const HAO_INT *n, const double *a, HAO_Complex16 *x, const HAO_INT *incx);
void    ZGTHR_(const HAO_INT *nz, const HAO_Complex16 *y, HAO_Complex16 *x, const HAO_INT *indx);
void    ZGTHRZ_(const HAO_INT *nz, HAO_Complex16 *y, HAO_Complex16 *x, const HAO_INT *indx);
void    ZROTG_(HAO_Complex16 *a, const HAO_Complex16 *b, double *c, HAO_Complex16 *s);
void    ZSCAL_(const HAO_INT *n, const HAO_Complex16 *a, HAO_Complex16 *x, const HAO_INT *incx);
void    ZSCTR_(const HAO_INT *nz, const HAO_Complex16 *x, const HAO_INT *indx, HAO_Complex16 *y);
void    ZSWAP_(const HAO_INT *n, HAO_Complex16 *x, const HAO_INT *incx, HAO_Complex16 *y, const HAO_INT *incy);
HAO_INT IZAMAX_(const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx);
HAO_INT IZAMIN_(const  HAO_INT *n,const  HAO_Complex16 *x, const HAO_INT *incx);

/* BLAS Level2 */

void SGBMV_(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_INT *kl, const HAO_INT *ku,
           const float *alpha, const float *a, const HAO_INT *lda, const float *x, const HAO_INT *incx,
           const float *beta, float *y, const HAO_INT *incy);
void SGEMV_(const char *trans, const HAO_INT *m, const HAO_INT *n, const float *alpha,
           const float *a, const HAO_INT *lda, const float *x, const HAO_INT *incx,
           const float *beta, float *y, const HAO_INT *incy);
void SGER_(const HAO_INT *m, const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx,
          const float *y, const HAO_INT *incy, float *a, const HAO_INT *lda);
void SSBMV_(const char *uplo, const HAO_INT *n, const HAO_INT *k,
           const float *alpha, const float *a, const HAO_INT *lda, const float *x, const HAO_INT *incx,
           const float *beta, float *y, const HAO_INT *incy);
void SSPMV_(const char *uplo, const HAO_INT *n, const float *alpha, const float *ap,
           const float *x, const HAO_INT *incx, const float *beta, float *y, const HAO_INT *incy);
void SSPR_(const char *uplo, const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx, float *ap);
void SSPR2_(const char *uplo, const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx,
           const float *y, const HAO_INT *incy, float *ap);
void SSYMV_(const char *uplo, const HAO_INT *n, const float *alpha, const float *a, const HAO_INT *lda,
           const float *x, const HAO_INT *incx, const float *beta, float *y, const HAO_INT *incy);
void SSYR_(const char *uplo, const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx,
          float *a, const HAO_INT *lda);
void SSYR2_(const char *uplo, const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx,
           const float *y, const HAO_INT *incy, float *a, const HAO_INT *lda);
void STBMV_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const float *a, const HAO_INT *lda, float *x, const HAO_INT *incx);
void STBSV_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const float *a, const HAO_INT *lda, float *x, const HAO_INT *incx);
void STPMV_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const float *ap, float *x, const HAO_INT *incx);
void STPSV_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const float *ap, float *x, const HAO_INT *incx);
void STRMV_(const char *uplo, const char *transa, const char *diag, const HAO_INT *n,
           const float *a, const HAO_INT *lda, float *b, const HAO_INT *incx);
void STRSV_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const float *a, const HAO_INT *lda, float *x, const HAO_INT *incx);
void SGEM2VU_(const HAO_INT *m, const HAO_INT *n, const float *alpha, const float *a, const HAO_INT *lda,
           const float *x1, const HAO_INT *incx1, const float *x2, const HAO_INT *incx2,
           const float *beta, float *y1, const HAO_INT *incy1, float *y2, const HAO_INT *incy2);

void CGBMV_(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_INT *kl, const HAO_INT *ku,
           const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *beta,
           HAO_Complex8 *y, const HAO_INT *incy);
void CGEMV_(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, const HAO_Complex8 *x, const HAO_INT *incx,
           const HAO_Complex8 *beta, HAO_Complex8 *y, const HAO_INT *incy);
void CGERC_(const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *y, const HAO_INT *incy,
           HAO_Complex8 *a, const HAO_INT *lda);
void CGERU_(const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *y, const HAO_INT *incy,
           HAO_Complex8 *a, const HAO_INT *lda);
void CHBMV_(const char *uplo, const HAO_INT *n, const HAO_INT *k, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, const HAO_Complex8 *x, const HAO_INT *incx,
           const HAO_Complex8 *beta, HAO_Complex8 *y, const HAO_INT *incy);
void CHEMV_(const char *uplo, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, const HAO_Complex8 *x, const HAO_INT *incx,
           const HAO_Complex8 *beta, HAO_Complex8 *y, const HAO_INT *incy);
void CHER_(const char *uplo, const HAO_INT *n, const float *alpha, const HAO_Complex8 *x, const HAO_INT *incx,
          HAO_Complex8 *a, const HAO_INT *lda);
void CHER2_(const char *uplo, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *y, const HAO_INT *incy,
           HAO_Complex8 *a, const HAO_INT *lda);
void CHPMV_(const char *uplo, const HAO_INT *n, const HAO_Complex8 *alpha, const HAO_Complex8 *ap,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *beta,
           HAO_Complex8 *y, const HAO_INT *incy);
void CHPR_(const char *uplo, const HAO_INT *n, const float *alpha, const HAO_Complex8 *x, const HAO_INT *incx,
          HAO_Complex8 *ap);
void CHPR2_(const char *uplo, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *y, const HAO_INT *incy,
           HAO_Complex8 *ap);
void CTBMV_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex8 *a, const HAO_INT *lda, HAO_Complex8 *x, const HAO_INT *incx);
void CTBSV_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex8 *a, const HAO_INT *lda, HAO_Complex8 *x, const HAO_INT *incx);
void CTPMV_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex8 *ap, HAO_Complex8 *x, const HAO_INT *incx);
void CTPSV_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex8 *ap, HAO_Complex8 *x, const HAO_INT *incx);
void CTRMV_(const char *uplo, const char *transa, const char *diag, const HAO_INT *n,
           const HAO_Complex8 *a, const HAO_INT *lda, HAO_Complex8 *b, const HAO_INT *incx);
void CTRSV_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex8 *a, const HAO_INT *lda, HAO_Complex8 *x, const HAO_INT *incx);
void CGEM2VC_(const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, const HAO_Complex8 *x1, const HAO_INT *incx1,
           const HAO_Complex8 *x2, const HAO_INT *incx2, const HAO_Complex8 *beta,
           HAO_Complex8 *y1, const HAO_INT *incy1, HAO_Complex8 *y2, const HAO_INT *incy2);
void SCGEMV_(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const float *a, const HAO_INT *lda, const HAO_Complex8 *x, const HAO_INT *incx,
           const HAO_Complex8 *beta, HAO_Complex8 *y, const HAO_INT *incy);

void DGBMV_(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_INT *kl, const HAO_INT *ku,
           const double *alpha, const double *a, const HAO_INT *lda, const double *x, const HAO_INT *incx,
           const double *beta, double *y, const HAO_INT *incy);
void DGEMV_(const char *trans, const HAO_INT *m, const HAO_INT *n, const double *alpha,
           const double *a, const HAO_INT *lda, const double *x, const HAO_INT *incx,
           const double *beta, double *y, const HAO_INT *incy);
void DGER_(const HAO_INT *m, const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx,
          const double *y, const HAO_INT *incy, double *a, const HAO_INT *lda);
void DSBMV_(const char *uplo, const HAO_INT *n, const HAO_INT *k, const double *alpha,
           const double *a, const HAO_INT *lda, const double *x, const HAO_INT *incx,
           const double *beta, double *y, const HAO_INT *incy);
void DSPMV_(const char *uplo, const HAO_INT *n, const double *alpha, const double *ap,
           const double *x, const HAO_INT *incx, const double *beta, double *y, const HAO_INT *incy);
void DSPR_(const char *uplo, const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx, double *ap);
void DSPR2_(const char *uplo, const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx,
           const double *y, const HAO_INT *incy, double *ap);
void DSYMV_(const char *uplo, const HAO_INT *n, const double *alpha, const double *a, const HAO_INT *lda,
           const double *x, const HAO_INT *incx, const double *beta, double *y, const HAO_INT *incy);
void DSYR_(const char *uplo, const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx,
          double *a, const HAO_INT *lda);
void DSYR2_(const char *uplo, const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx,
           const double *y, const HAO_INT *incy, double *a, const HAO_INT *lda);
void DTBMV_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const double *a, const HAO_INT *lda, double *x, const HAO_INT *incx);
void DTBSV_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const double *a, const HAO_INT *lda, double *x, const HAO_INT *incx);
void DTPMV_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const double *ap, double *x, const HAO_INT *incx);
void DTPSV_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const double *ap, double *x, const HAO_INT *incx);
void DTRMV_(const char *uplo, const char *transa, const char *diag, const HAO_INT *n,
           const double *a, const HAO_INT *lda, double *b, const HAO_INT *incx);
void DTRSV_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const double *a, const HAO_INT *lda, double *x, const HAO_INT *incx);
void DGEM2VU_(const HAO_INT *m, const HAO_INT *n, const double *alpha,
           const double *a, const HAO_INT *lda, const double *x1, const HAO_INT *incx1,
           const double *x2, const HAO_INT *incx2, const double *beta,
           double *y1, const HAO_INT *incy1, double *y2, const HAO_INT *incy2);

void ZGBMV_(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_INT *kl, const HAO_INT *ku,
           const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *beta,
           HAO_Complex16 *y, const HAO_INT *incy);
void ZGEMV_(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *beta, HAO_Complex16 *y, const HAO_INT *incy);
void ZGERC_(const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *y, const HAO_INT *incy,
           HAO_Complex16 *a, const HAO_INT *lda);
void ZGERU_(const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *y, const HAO_INT *incy,
           HAO_Complex16 *a, const HAO_INT *lda);
void ZHBMV_(const char *uplo, const HAO_INT *n, const HAO_INT *k, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *beta, HAO_Complex16 *y, const HAO_INT *incy);
void ZHEMV_(const char *uplo, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *beta, HAO_Complex16 *y, const HAO_INT *incy);
void ZHER_(const char *uplo, const HAO_INT *n, const double *alpha,
          const HAO_Complex16 *x, const HAO_INT *incx, HAO_Complex16 *a, const HAO_INT *lda);
void ZHER2_(const char *uplo, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *y, const HAO_INT *incy,
           HAO_Complex16 *a, const HAO_INT *lda);
void ZHPMV_(const char *uplo, const HAO_INT *n, const HAO_Complex16 *alpha, const HAO_Complex16 *ap,
           const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *beta,
           HAO_Complex16 *y, const HAO_INT *incy);
void ZHPR_(const char *uplo, const HAO_INT *n, const double *alpha, const HAO_Complex16 *x,
          const HAO_INT *incx, HAO_Complex16 *ap);
void ZHPR2_(const char *uplo, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *y, const HAO_INT *incy,
           HAO_Complex16 *ap);
void ZTBMV_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *x, const HAO_INT *incx);
void ZTBSV_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *x, const HAO_INT *incx);
void ZTPMV_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex16 *ap, HAO_Complex16 *x, const HAO_INT *incx);
void ZTPSV_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           HAO_Complex16 *ap, HAO_Complex16 *x, const HAO_INT *incx);
void ZTRMV_(const char *uplo, const char *transa, const char *diag, const HAO_INT *n,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *b, const HAO_INT *incx);
void ZTRSV_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *x, const HAO_INT *incx);
void ZGEM2VC_(const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, const HAO_Complex16 *x1, const HAO_INT *incx1,
           const HAO_Complex16 *x2, const HAO_INT *incx2, const HAO_Complex16 *beta,
           HAO_Complex16 *y1, const HAO_INT *incy1, HAO_Complex16 *y2, const HAO_INT *incy2);
void DZGEMV_(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const double *a, const HAO_INT *lda, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *beta, HAO_Complex16 *y, const HAO_INT *incy);

/* BLAS Level3 */

void SGEMM_(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const float *alpha, const float *a, const HAO_INT *lda, const float *b, const HAO_INT *ldb,
           const float *beta, float *c, const HAO_INT *ldc);
void SGEMM_BATCH_(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const float *alpha_array, const float **a_array, const HAO_INT *lda_array, const float **b_array, const HAO_INT *ldb_array,
           const float *beta_array, float **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void SGEMMT_(const char *uplo, const char *transa, const char *transb, const HAO_INT *n, const HAO_INT *k,
            const float *alpha, const float *a, const HAO_INT *lda, const float *b, const HAO_INT *ldb,
            const float *beta, float *c, const HAO_INT *ldc);
void SSYMM_(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const float *alpha, const float *a, const HAO_INT *lda, const float *b, const HAO_INT *ldb,
           const float *beta, float *c, const HAO_INT *ldc);
void SSYR2K_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const float *alpha, const float *a, const HAO_INT *lda, const float *b, const HAO_INT *ldb,
            const float *beta, float *c, const HAO_INT *ldc);
void SSYRK_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const float *alpha, const float *a, const HAO_INT *lda,
           const float *beta, float *c, const HAO_INT *ldc);
void STRMM_(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const float *alpha, const float *a, const HAO_INT *lda,
           float *b, const HAO_INT *ldb);
void STRSM_(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const float *alpha, const float *a, const HAO_INT *lda,
           float *b, const HAO_INT *ldb);

void CGEMM_(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
           const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
           HAO_Complex8 *c, const HAO_INT *ldc);

void CGEMM_BATCH_(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const HAO_Complex8 *alpha_array, const HAO_Complex8 **a_array, const HAO_INT *lda_array, const HAO_Complex8 **b_array, const HAO_INT *ldb_array,
           const HAO_Complex8 *beta_array, HAO_Complex8 **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void SCGEMM_(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex8 *alpha, const float *a, const HAO_INT *lda,
           const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
           HAO_Complex8 *c, const HAO_INT *ldc);
void CGEMM3M_(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
             const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
             const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
             HAO_Complex8 *c, const HAO_INT *ldc);
void CGEMM3M_BATCH_(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const HAO_Complex8 *alpha_array, const HAO_Complex8 **a_array, const HAO_INT *lda_array, const HAO_Complex8 **b_array, const HAO_INT *ldb_array,
           const HAO_Complex8 *beta_array, HAO_Complex8 **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void CGEMMT_(const char *uplo, const char *transa, const char *transb, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
            const HAO_Complex8 *b, const HAO_INT *ldb,
            const HAO_Complex8 *beta, HAO_Complex8 *c, const HAO_INT *ldc);

void CHEMM_(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
           const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
           HAO_Complex8 *c, const HAO_INT *ldc);
void CHER2K_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
            const HAO_Complex8 *b, const HAO_INT *ldb, const float *beta,
            HAO_Complex8 *c, const HAO_INT *ldc);
void CHERK_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const float *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
           const float *beta, HAO_Complex8 *c, const HAO_INT *ldc);
void CSYMM_(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, const HAO_Complex8 *b, const HAO_INT *ldb,
           const HAO_Complex8 *beta, HAO_Complex8 *c, const HAO_INT *ldc);
void CSYR2K_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
            const HAO_Complex8 *b, const HAO_INT *ldb,
            const HAO_Complex8 *beta, HAO_Complex8 *c, const HAO_INT *ldc);
void CSYRK_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
           const HAO_Complex8 *beta, HAO_Complex8 *c, const HAO_INT *ldc);
void CTRMM_(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda,
           HAO_Complex8 *b, const HAO_INT *ldb);
void CTRSM_(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda,
           HAO_Complex8 *b, const HAO_INT *ldb);

void DGEMM_(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const double *alpha, const double *a, const HAO_INT *lda, const double *b, const HAO_INT *ldb,
           const double *beta, double *c, const HAO_INT *ldc);

void DGEMM_BATCH_(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const double *alpha_array, const double **a_array, const HAO_INT *lda_array, const double **b_array, const HAO_INT *ldb_array,
           const double *beta_array, double **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void DGEMMT_(const char *uplo, const char *transa, const char *transb, const HAO_INT *n, const HAO_INT *k,
            const double *alpha, const double *a, const HAO_INT *lda, const double *b, const HAO_INT *ldb,
            const double *beta, double *c, const HAO_INT *ldc);

void DSYMM_(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const double *alpha, const double *a, const HAO_INT *lda, const double *b, const HAO_INT *ldb,
           const double *beta, double *c, const HAO_INT *ldc);
void DSYR2K_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const double *alpha, const double *a, const HAO_INT *lda, const double *b, const HAO_INT *ldb,
            double *beta, double *c, const HAO_INT *ldc);
void DSYRK_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const double *alpha, const double *a, const HAO_INT *lda, const double *beta,
           double *c, const HAO_INT *ldc);
void DTRMM_(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const double *alpha, const double *a, const HAO_INT *lda,
           double *b, const HAO_INT *ldb);
void DTRSM_(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const double *alpha, const double *a, const HAO_INT *lda,
           double *b, const HAO_INT *ldb);

void ZGEMM_(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
           HAO_Complex16 *c, const HAO_INT *ldc);
void ZGEMM_BATCH_(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const HAO_Complex16 *alpha_array, const HAO_Complex16 **a_array, const HAO_INT *lda_array, const HAO_Complex16 **b_array, const HAO_INT *ldb_array,
           const HAO_Complex16 *beta_array, HAO_Complex16 **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void DZGEMM_(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex16 *alpha, const double *a, const HAO_INT *lda,
           const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
           HAO_Complex16 *c, const HAO_INT *ldc);
void ZGEMM3M_(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
             const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
             const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
             HAO_Complex16 *c, const HAO_INT *ldc);
void ZGEMM3M_BATCH_(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const HAO_Complex16 *alpha_array, const HAO_Complex16 **a_array, const HAO_INT *lda_array, const HAO_Complex16 **b_array, const HAO_INT *ldb_array,
           const HAO_Complex16 *beta_array, HAO_Complex16 **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void ZGEMMT_(const char *uplo, const char *transa, const char *transb, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
            const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
            HAO_Complex16 *c, const HAO_INT *ldc);
void ZHEMM_(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
           HAO_Complex16 *c, const HAO_INT *ldc);
void ZHER2K_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
            const HAO_Complex16 *b, const HAO_INT *ldb, const double *beta,
            HAO_Complex16 *c, const HAO_INT *ldc);
void ZHERK_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const double *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const double *beta, HAO_Complex16 *c, const HAO_INT *ldc);
void ZSYMM_(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
           HAO_Complex16 *c, const HAO_INT *ldc);
void ZSYR2K_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
            const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
            HAO_Complex16 *c, const HAO_INT *ldc);
void ZSYRK_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const HAO_Complex16 *beta, HAO_Complex16 *c, const HAO_INT *ldc);
void ZTRMM_(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *b, const HAO_INT *ldb);
void ZTRSM_(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *b, const HAO_INT *ldb);

/* Lower case declaration */

void xerbla_(const char *srname, const int *info, const int lsrname);
int lsame_(const char *ca, const char *cb, const HAO_INT lca, const HAO_INT lcb);

/* BLAS Level1 */
float   scabs1_(const HAO_Complex8 *c);
float   sasum_(const HAO_INT *n, const float *x, const HAO_INT *incx);
void    saxpy_(const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx, float *y, const HAO_INT *incy);
void    saxpby_(const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx, const float *beta, float *y, const HAO_INT *incy);
void    saxpyi_(const HAO_INT *nz, const float *a, const float *x, const HAO_INT *indx, float *y);
float   scasum_(const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx);
float   scnrm2_(const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx);
void    scopy_(const HAO_INT *n, const float *x, const HAO_INT *incx, float *y, const HAO_INT *incy);
float   sdot_(const HAO_INT *n, const float *x, const HAO_INT *incx, const float *y, const HAO_INT *incy);
float   sdoti_(const HAO_INT *nz, const float *x, const HAO_INT *indx, const float *y);
float   sdsdot_(const HAO_INT *n, const float *sb, const float *x, const HAO_INT *incx, const float *y, const HAO_INT *incy);
void    sgthr_(const HAO_INT *nz, const float *y, float *x, const HAO_INT *indx);
void    sgthrz_(const HAO_INT *nz, float *y, float *x, const HAO_INT *indx);
float   snrm2_(const HAO_INT *n, const float *x, const HAO_INT *incx);
void    srot_(const HAO_INT *n, float *x, const HAO_INT *incx, float *y, const HAO_INT *incy, const float *c, const float *s);
void    srotg_(float *a,float *b,float *c,float *s);
void    sroti_(const HAO_INT *nz, float *x, const HAO_INT *indx, float *y, const float *c, const float *s);
void    srotm_(const HAO_INT *n, float *x, const HAO_INT *incx, float *y, const HAO_INT *incy, const float *param);
void    srotmg_(float *d1, float *d2, float *x1, const float *y1, float *param);
void    sscal_(const HAO_INT *n, const float *a, float *x, const HAO_INT *incx);
void    ssctr_(const HAO_INT *nz, const float *x, const HAO_INT *indx, float *y);
void    sswap_(const HAO_INT *n, float *x, const HAO_INT *incx, float *y, const HAO_INT *incy);
HAO_INT isamax_(const HAO_INT *n, const float *x, const HAO_INT *incx);
HAO_INT isamin_(const HAO_INT *n, const float *x, const HAO_INT *incx);

void    caxpy_(const HAO_INT *n, const HAO_Complex8 *alpha, const HAO_Complex8 *x, const HAO_INT *incx, HAO_Complex8 *y, const HAO_INT *incy);
void    caxpby_(const HAO_INT *n, const HAO_Complex8 *alpha, const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *beta, HAO_Complex8 *y, const HAO_INT *incy);
void    caxpyi_(const HAO_INT *nz, const HAO_Complex8 *a, const HAO_Complex8 *x, const HAO_INT *indx, HAO_Complex8 *y);
void    ccopy_(const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx, HAO_Complex8 *y, const HAO_INT *incy);
void    cdotc_(HAO_Complex8 *pres, const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *y, const HAO_INT *incy);
void    cdotci_(HAO_Complex8 *pres, const HAO_INT *nz, const HAO_Complex8 *x, const HAO_INT *indx, const HAO_Complex8 *y);
void    cdotu_(HAO_Complex8 *pres, const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *y, const HAO_INT *incy);
void    cdotui_(HAO_Complex8 *pres, const HAO_INT *nz, const HAO_Complex8 *x, const HAO_INT *indx, const HAO_Complex8 *y);
void    cgthr_(const HAO_INT *nz, const HAO_Complex8 *y, HAO_Complex8 *x, const HAO_INT *indx);
void    cgthrz_(const HAO_INT *nz, HAO_Complex8 *y, HAO_Complex8 *x, const HAO_INT *indx);
void    crotg_(HAO_Complex8 *a, const HAO_Complex8 *b, float *c, HAO_Complex8 *s);
void    cscal_(const HAO_INT *n, const HAO_Complex8 *a, HAO_Complex8 *x, const HAO_INT *incx);
void    csctr_(const HAO_INT *nz, const HAO_Complex8 *x, const HAO_INT *indx, HAO_Complex8 *y);
void    csrot_(const HAO_INT *n, HAO_Complex8 *x, const HAO_INT *incx, HAO_Complex8 *y, const HAO_INT *incy, const float *c, const float *s);
void    csscal_(const HAO_INT *n, const float *a, HAO_Complex8 *x, const HAO_INT *incx);
void    cswap_(const HAO_INT *n, HAO_Complex8 *x, const HAO_INT *incx, HAO_Complex8 *y, const HAO_INT *incy);
HAO_INT icamax_(const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx);
HAO_INT icamin_(const HAO_INT *n, const HAO_Complex8 *x, const HAO_INT *incx);

double  dcabs1_(const HAO_Complex16 *z);
double  dasum_(const HAO_INT *n, const double *x, const HAO_INT *incx);
void    daxpy_(const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx, double *y, const HAO_INT *incy);
void    daxpby_(const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx, const double *beta, double *y, const HAO_INT *incy);
void    daxpyi_(const HAO_INT *nz, const double *a, const double *x, const HAO_INT *indx, double *y);
void    dcopy_(const HAO_INT *n, const double *x, const HAO_INT *incx, double *y, const HAO_INT *incy);
double  ddot_(const HAO_INT *n, const double *x, const HAO_INT *incx, const double *y, const HAO_INT *incy);
double  dsdot_(const HAO_INT *n, const float *x, const HAO_INT *incx, const float *y, const HAO_INT *incy);
double  ddoti_(const HAO_INT *nz, const double *x, const HAO_INT *indx, const double *y);
void    dgthr_(const HAO_INT *nz, const double *y, double *x, const HAO_INT *indx);
void    dgthrz_(const HAO_INT *nz, double *y, double *x, const HAO_INT *indx);
double  dnrm2_(const HAO_INT *n, const double *x, const HAO_INT *incx);
void    drot_(const HAO_INT *n, double *x, const HAO_INT *incx, double *y, const HAO_INT *incy, const double *c, const double *s);
void    drotg_(double *a, double *b, double *c, double *s);
void    droti_(const HAO_INT *nz, double *x, const HAO_INT *indx, double *y, const double *c, const double *s);
void    drotm_(const HAO_INT *n, double *x, const HAO_INT *incx, double *y, const HAO_INT *incy, const double *param);
void    drotmg_(double *d1, double *d2, double *x1, const double *y1, double *param);
void    dscal_(const HAO_INT *n, const double *a, double *x, const HAO_INT *incx);
void    dsctr_(const HAO_INT *nz, const double *x, const HAO_INT *indx, double *y);
void    dswap_(const HAO_INT *n, double *x, const HAO_INT *incx, double *y, const HAO_INT *incy);
double  dzasum_(const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx);
double  dznrm2_(const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx);
HAO_INT idamax_(const HAO_INT *n, const double *x, const HAO_INT *incx);
HAO_INT idamin_(const HAO_INT *n, const double *x, const HAO_INT *incx);

void    zaxpy_(const HAO_INT *n, const HAO_Complex16 *alpha, const HAO_Complex16 *x, const HAO_INT *incx, HAO_Complex16 *y, const HAO_INT *incy);
void    zaxpby_(const HAO_INT *n, const HAO_Complex16 *alpha, const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *beta, HAO_Complex16 *y, const HAO_INT *incy);
void    zaxpyi_(const HAO_INT *nz, const HAO_Complex16 *a, const HAO_Complex16 *x, const HAO_INT *indx, HAO_Complex16 *y);
void    zcopy_(const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx, HAO_Complex16 *y, const HAO_INT *incy);
void    zdotc_(HAO_Complex16 *pres, const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *y, const HAO_INT *incy);
void    zdotci_(HAO_Complex16 *pres, const HAO_INT *nz, const HAO_Complex16 *x, const HAO_INT *indx, const HAO_Complex16 *y);
void    zdotu_(HAO_Complex16 *pres, const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *y, const HAO_INT *incy);
void    zdotui_(HAO_Complex16 *pres, const HAO_INT *nz, const HAO_Complex16 *x, const HAO_INT *indx, const HAO_Complex16 *y);
void    zdrot_(const HAO_INT *n, HAO_Complex16 *x, const HAO_INT *incx, HAO_Complex16 *y, const HAO_INT *incy, const double *c, const double *s);
void    zdscal_(const HAO_INT *n, const double *a, HAO_Complex16 *x, const HAO_INT *incx);
void    zgthr_(const HAO_INT *nz, const HAO_Complex16 *y, HAO_Complex16 *x, const HAO_INT *indx);
void    zgthrz_(const HAO_INT *nz, HAO_Complex16 *y, HAO_Complex16 *x, const HAO_INT *indx);
void    zrotg_(HAO_Complex16 *a, const HAO_Complex16 *b, double *c, HAO_Complex16 *s);
void    zscal_(const HAO_INT *n, const HAO_Complex16 *a, HAO_Complex16 *x, const HAO_INT *incx);
void    zsctr_(const HAO_INT *nz, const HAO_Complex16 *x, const HAO_INT *indx, HAO_Complex16 *y);
void    zswap_(const HAO_INT *n, HAO_Complex16 *x, const HAO_INT *incx, HAO_Complex16 *y, const HAO_INT *incy);
HAO_INT izamax_(const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx);
HAO_INT izamin_(const HAO_INT *n, const HAO_Complex16 *x, const HAO_INT *incx);

/* blas level2 */

void sgbmv_(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_INT *kl, const HAO_INT *ku,
           const float *alpha, const float *a, const HAO_INT *lda, const float *x, const HAO_INT *incx,
           const float *beta, float *y, const HAO_INT *incy);
void sgemv_(const char *trans, const HAO_INT *m, const HAO_INT *n, const float *alpha,
           const float *a, const HAO_INT *lda, const float *x, const HAO_INT *incx,
           const float *beta, float *y, const HAO_INT *incy);
void sger_(const HAO_INT *m, const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx,
          const float *y, const HAO_INT *incy, float *a, const HAO_INT *lda);
void ssbmv_(const char *uplo, const HAO_INT *n, const HAO_INT *k, const float *alpha,
           const float *a, const HAO_INT *lda, const float *x, const HAO_INT *incx,
           const float *beta, float *y, const HAO_INT *incy);
void sspmv_(const char *uplo, const HAO_INT *n, const float *alpha, const float *ap,
           const float *x, const HAO_INT *incx, const float *beta, float *y, const HAO_INT *incy);
void sspr_(const char *uplo, const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx,
          float *ap);
void sspr2_(const char *uplo, const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx,
           const float *y, const HAO_INT *incy, float *ap);
void ssymv_(const char *uplo, const HAO_INT *n, const float *alpha, const float *a, const HAO_INT *lda,
           const float *x, const HAO_INT *incx, const float *beta, float *y, const HAO_INT *incy);
void ssyr_(const char *uplo, const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx,
          float *a, const HAO_INT *lda);
void ssyr2_(const char *uplo, const HAO_INT *n, const float *alpha, const float *x, const HAO_INT *incx,
           const float *y, const HAO_INT *incy, float *a, const HAO_INT *lda);
void stbmv_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const float *a, const HAO_INT *lda, float *x, const HAO_INT *incx);
void stbsv_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const float *a, const HAO_INT *lda, float *x, const HAO_INT *incx);
void stpmv_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const float *ap,
           float *x, const HAO_INT *incx);
void stpsv_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const float *ap,
           float *x, const HAO_INT *incx);
void strmv_(const char *uplo, const char *transa, const char *diag, const HAO_INT *n, const float *a,
           const HAO_INT *lda, float *b, const HAO_INT *incx);
void strsv_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const float *a, const HAO_INT *lda, float *x, const HAO_INT *incx);
void sgem2vu_(const HAO_INT *m, const HAO_INT *n, const float *alpha, const float *a, const HAO_INT *lda,
           const float *x1, const HAO_INT *incx1, const float *x2, const HAO_INT *incx2,
           const float *beta, float *y1, const HAO_INT *incy1, float *y2, const HAO_INT *incy2);

void cgbmv_(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_INT *kl, const HAO_INT *ku,
           const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *beta,
           HAO_Complex8 *y, const HAO_INT *incy);
void cgemv_(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, const HAO_Complex8 *x, const HAO_INT *incx,
           const HAO_Complex8 *beta, HAO_Complex8 *y, const HAO_INT *incy);
void cgerc_(const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *y, const HAO_INT *incy,
           HAO_Complex8 *a, const HAO_INT *lda);
void cgeru_(const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *y, const HAO_INT *incy,
           HAO_Complex8 *a, const HAO_INT *lda);
void chbmv_(const char *uplo, const HAO_INT *n, const HAO_INT *k, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, const HAO_Complex8 *x, const HAO_INT *incx,
           const HAO_Complex8 *beta, HAO_Complex8 *y, const HAO_INT *incy);
void chemv_(const char *uplo, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, const HAO_Complex8 *x, const HAO_INT *incx,
           const HAO_Complex8 *beta, HAO_Complex8 *y, const HAO_INT *incy);
void cher_(const char *uplo, const HAO_INT *n, const float *alpha, const HAO_Complex8 *x, const HAO_INT *incx,
          HAO_Complex8 *a, const HAO_INT *lda);
void cher2_(const char *uplo, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *y, const HAO_INT *incy,
           HAO_Complex8 *a, const HAO_INT *lda);
void chpmv_(const char *uplo, const HAO_INT *n, const HAO_Complex8 *alpha, const HAO_Complex8 *ap,
           const HAO_Complex8 *x, const HAO_INT *incx, const HAO_Complex8 *beta,
           HAO_Complex8 *y, const HAO_INT *incy);
void chpr_(const char *uplo, const HAO_INT *n, const float *alpha, const HAO_Complex8 *x, const HAO_INT *incx,
          HAO_Complex8 *ap);
void chpr2_(const char *uplo, const HAO_INT *n, const HAO_Complex8 *alpha, const HAO_Complex8 *x, const HAO_INT *incx,
           const HAO_Complex8 *y, const HAO_INT *incy, HAO_Complex8 *ap);
void ctbmv_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex8 *a, const HAO_INT *lda, HAO_Complex8 *x, const HAO_INT *incx);
void ctbsv_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex8 *a, const HAO_INT *lda, HAO_Complex8 *x, const HAO_INT *incx);
void ctpmv_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex8 *ap, HAO_Complex8 *x, const HAO_INT *incx);
void ctpsv_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex8 *ap, HAO_Complex8 *x, const HAO_INT *incx);
void ctrmv_(const char *uplo, const char *transa, const char *diag, const HAO_INT *n,
           const HAO_Complex8 *a, const HAO_INT *lda, HAO_Complex8 *b, const HAO_INT *incx);
void ctrsv_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex8 *a, const HAO_INT *lda, HAO_Complex8 *x, const HAO_INT *incx);
void cgem2vc_(const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, const HAO_Complex8 *x1, const HAO_INT *incx1,
           const HAO_Complex8 *x2, const HAO_INT *incx2, const HAO_Complex8 *beta,
           HAO_Complex8 *y1, const HAO_INT *incy1, HAO_Complex8 *y2, const HAO_INT *incy2);
void scgemv_(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const float *a, const HAO_INT *lda, const HAO_Complex8 *x, const HAO_INT *incx,
           const HAO_Complex8 *beta, HAO_Complex8 *y, const HAO_INT *incy);

void dgbmv_(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_INT *kl, const HAO_INT *ku,
           const double *alpha, const double *a, const HAO_INT *lda, const double *x, const HAO_INT *incx,
           const double *beta, double *y, const HAO_INT *incy);
void dgemv_(const char *trans, const HAO_INT *m, const HAO_INT *n, const double *alpha,
           const double *a, const HAO_INT *lda, const double *x, const HAO_INT *incx,
           const double *beta, double *y, const HAO_INT *incy);
void dger_(const HAO_INT *m, const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx,
          const double *y, const HAO_INT *incy, double *a, const HAO_INT *lda);
void dsbmv_(const char *uplo, const HAO_INT *n, const HAO_INT *k, const double *alpha,
           const double *a, const HAO_INT *lda, const double *x, const HAO_INT *incx,
           const double *beta, double *y, const HAO_INT *incy);
void dspmv_(const char *uplo, const HAO_INT *n, const double *alpha, const double *ap,
           const double *x, const HAO_INT *incx, const double *beta,
           double *y, const HAO_INT *incy);
void dspr_(const char *uplo, const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx,
          double *ap);
void dspr2_(const char *uplo, const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx,
           const double *y, const HAO_INT *incy, double *ap);
void dsymv_(const char *uplo, const HAO_INT *n, const double *alpha, const double *a, const HAO_INT *lda,
           const double *x, const HAO_INT *incx, const double *beta, double *y, const HAO_INT *incy);
void dsyr_(const char *uplo, const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx,
          double *a, const HAO_INT *lda);
void dsyr2_(const char *uplo, const HAO_INT *n, const double *alpha, const double *x, const HAO_INT *incx,
           const double *y, const HAO_INT *incy, double *a, const HAO_INT *lda);
void dtbmv_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const double *a, const HAO_INT *lda, double *x, const HAO_INT *incx);
void dtbsv_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const double *a, const HAO_INT *lda, double *x, const HAO_INT *incx);
void dtpmv_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const double *ap, double *x, const HAO_INT *incx);
void dtpsv_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const double *ap, double *x, const HAO_INT *incx);
void dtrmv_(const char *uplo, const char *transa, const char *diag, const HAO_INT *n,
           const double *a, const HAO_INT *lda, double *b, const HAO_INT *incx);
void dtrsv_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const double *a, const HAO_INT *lda, double *x, const HAO_INT *incx);
void dgem2vu_(const HAO_INT *m, const HAO_INT *n, const double *alpha,
           const double *a, const HAO_INT *lda, const double *x1, const HAO_INT *incx1,
           const double *x2, const HAO_INT *incx2, const double *beta,
           double *y1, const HAO_INT *incy1, double *y2, const HAO_INT *incy2);

void zgbmv_(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_INT *kl, const HAO_INT *ku,
           const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *beta,
           HAO_Complex16 *y, const HAO_INT *incy);
void zgemv_(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *beta, HAO_Complex16 *y, const HAO_INT *incy);
void zgerc_(const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *y, const HAO_INT *incy, HAO_Complex16 *a, const HAO_INT *lda);
void zgeru_(const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *y, const HAO_INT *incy, HAO_Complex16 *a, const HAO_INT *lda);
void zhbmv_(const char *uplo, const HAO_INT *n, const HAO_INT *k, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *beta, HAO_Complex16 *y, const HAO_INT *incy);
void zhemv_(const char *uplo, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *beta, HAO_Complex16 *y, const HAO_INT *incy);
void zher_(const char *uplo, const HAO_INT *n, const double *alpha, const HAO_Complex16 *x, const HAO_INT *incx,
          HAO_Complex16 *a, const HAO_INT *lda);
void zher2_(const char *uplo, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *y, const HAO_INT *incy,
           HAO_Complex16 *a, const HAO_INT *lda);
void zhpmv_(const char *uplo, const HAO_INT *n, const HAO_Complex16 *alpha, const HAO_Complex16 *ap,
           const HAO_Complex16 *x, const HAO_INT *incx, const HAO_Complex16 *beta,
           HAO_Complex16 *y, const HAO_INT *incy);
void zhpr_(const char *uplo, const HAO_INT *n, const double *alpha, const HAO_Complex16 *x, const HAO_INT *incx,
          HAO_Complex16 *ap);
void zhpr2_(const char *uplo, const HAO_INT *n, const HAO_Complex16 *alpha, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *y, const HAO_INT *incy, HAO_Complex16 *ap);
void ztbmv_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *x, const HAO_INT *incx);
void ztbsv_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *x, const HAO_INT *incx);
void ztpmv_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex16 *ap, HAO_Complex16 *x, const HAO_INT *incx);
void ztpsv_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex16 *ap, HAO_Complex16 *x, const HAO_INT *incx);
void ztrmv_(const char *uplo, const char *transa, const char *diag, const HAO_INT *n,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *b, const HAO_INT *incx);
void ztrsv_(const char *uplo, const char *trans, const char *diag, const HAO_INT *n,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *x, const HAO_INT *incx);
void zgem2vc_(const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, const HAO_Complex16 *x1, const HAO_INT *incx1,
           const HAO_Complex16 *x2, const HAO_INT *incx2, const HAO_Complex16 *beta,
           HAO_Complex16 *y1, const HAO_INT *incy1, HAO_Complex16 *y2, const HAO_INT *incy2);
void dzgemv_(const char *trans, const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const double *a, const HAO_INT *lda, const HAO_Complex16 *x, const HAO_INT *incx,
           const HAO_Complex16 *beta, HAO_Complex16 *y, const HAO_INT *incy);

/* blas level3 */

void sgemm_(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const float *alpha, const float *a, const HAO_INT *lda, const float *b, const HAO_INT *ldb,
           const float *beta, float *c, const HAO_INT *ldc);
void sgemm_batch_(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const float *alpha_array, const float **a_array, const HAO_INT *lda_array, const float **b_array, const HAO_INT *ldb_array,
           const float *beta_array, float **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void sgemmt_(const char *uplo, const char *transa, const char *transb, const HAO_INT *n, const HAO_INT *k,
            const float *alpha, const float *a, const HAO_INT *lda, const float *b, const HAO_INT *ldb,
            const float *beta, float *c, const HAO_INT *ldc);
void ssymm_(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const float *alpha, const float *a, const HAO_INT *lda, const float *b, const HAO_INT *ldb,
           const float *beta, float *c, const HAO_INT *ldc);
void ssyr2k_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const float *alpha, const float *a, const HAO_INT *lda, const float *b, const HAO_INT *ldb,
            const float *beta, float *c, const HAO_INT *ldc);
void ssyrk_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const float *alpha, const float *a, const HAO_INT *lda, const float *beta,
           float *c, const HAO_INT *ldc);
void strmm_(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const float *alpha, const float *a, const HAO_INT *lda,
           float *b, const HAO_INT *ldb);
void strsm_(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const float *alpha, const float *a, const HAO_INT *lda,
           float *b, const HAO_INT *ldb);

void cgemm_(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
           const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
           HAO_Complex8 *c, const HAO_INT *ldc);
void cgemm_batch_(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const HAO_Complex8 *alpha_array, const HAO_Complex8 **a_array, const HAO_INT *lda_array, const HAO_Complex8 **b_array, const HAO_INT *ldb_array,
           const HAO_Complex8 *beta_array, HAO_Complex8 **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void scgemm_(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex8 *alpha, const float *a, const HAO_INT *lda,
           const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
           HAO_Complex8 *c, const HAO_INT *ldc);
void cgemm3m_(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
             const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
             const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
             HAO_Complex8 *c, const HAO_INT *ldc);
void cgemm3m_batch_(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const HAO_Complex8 *alpha_array, const HAO_Complex8 **a_array, const HAO_INT *lda_array, const HAO_Complex8 **b_array, const HAO_INT *ldb_array,
           const HAO_Complex8 *beta_array, HAO_Complex8 **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void cgemmt_(const char *uplo, const char *transa, const char *transb, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
            const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
            HAO_Complex8 *c, const HAO_INT *ldc);
void chemm_(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
           const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
           HAO_Complex8 *c, const HAO_INT *ldc);
void cher2k_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
            const HAO_Complex8 *b, const HAO_INT *ldb, const float *beta,
            HAO_Complex8 *c, const HAO_INT *ldc);
void cherk_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const float *alpha, const HAO_Complex8 *a, const HAO_INT *lda, const float *beta,
           HAO_Complex8 *c, const HAO_INT *ldc);
void csymm_(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
           const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
           HAO_Complex8 *c, const HAO_INT *ldc);
void csyr2k_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
            const HAO_Complex8 *b, const HAO_INT *ldb, const HAO_Complex8 *beta,
            HAO_Complex8 *c, const HAO_INT *ldc);
void csyrk_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex8 *alpha, const HAO_Complex8 *a, const HAO_INT *lda,
           const HAO_Complex8 *beta, HAO_Complex8 *c, const HAO_INT *ldc);
void ctrmm_(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, HAO_Complex8 *b, const HAO_INT *ldb);
void ctrsm_(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const HAO_Complex8 *alpha,
           const HAO_Complex8 *a, const HAO_INT *lda, HAO_Complex8 *b, const HAO_INT *ldb);

void dgemm_(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const double *alpha, const double *a, const HAO_INT *lda, const double *b, const HAO_INT *ldb,
           const double *beta, double *c, const HAO_INT *ldc);
void dgemm_batch_(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const double *alpha_array, const double **a_array, const HAO_INT *lda_array, const double **b_array, const HAO_INT *ldb_array,
           const double *beta_array, double **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void dgemmt_(const char *uplo, const char *transa, const char *transb, const HAO_INT *n, const HAO_INT *k,
            const double *alpha, const double *a, const HAO_INT *lda, const double *b, const HAO_INT *ldb,
            const double *beta, double *c, const HAO_INT *ldc);
void dsymm_(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const double *alpha, const double *a, const HAO_INT *lda, const double *b, const HAO_INT *ldb,
           const double *beta, double *c, const HAO_INT *ldc);
void dsyr2k_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const double *alpha, const double *a, const HAO_INT *lda, const double *b, const HAO_INT *ldb,
            const double *beta, double *c, const HAO_INT *ldc);
void dsyrk_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const double *alpha, const double *a, const HAO_INT *lda, const double *beta,
           double *c, const HAO_INT *ldc);
void dtrmm_(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const double *alpha, const double *a, const HAO_INT *lda,
           double *b, const HAO_INT *ldb);
void dtrsm_(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const double *alpha, const double *a, const HAO_INT *lda,
           double *b, const HAO_INT *ldb);

void zgemm_(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
           HAO_Complex16 *c, const HAO_INT *ldc);
void zgemm_batch_(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const HAO_Complex16 *alpha_array, const HAO_Complex16 **a_array, const HAO_INT *lda_array, const HAO_Complex16 **b_array, const HAO_INT *ldb_array,
           const HAO_Complex16 *beta_array, HAO_Complex16 **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void dzgemm_(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex16 *alpha, const double *a, const HAO_INT *lda,
           const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
           HAO_Complex16 *c, const HAO_INT *ldc);
void zgemm3m_(const char *transa, const char *transb, const HAO_INT *m, const HAO_INT *n, const HAO_INT *k,
             const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
             const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
             HAO_Complex16 *c, const HAO_INT *ldc);
void zgemm3m_batch_(const char *transa_array, const char *transb_array, const HAO_INT *m_array, const HAO_INT *n_array, const HAO_INT *k_array,
           const HAO_Complex16 *alpha_array, const HAO_Complex16 **a_array, const HAO_INT *lda_array, const HAO_Complex16 **b_array, const HAO_INT *ldb_array,
           const HAO_Complex16 *beta_array, HAO_Complex16 **c_array, const HAO_INT *ldc_array, const HAO_INT *group_count, const HAO_INT *group_size);
void zgemmt_(const char *uplo, const char *transa, const char *transb, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
            const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
            HAO_Complex16 *c, const HAO_INT *ldc);
void zhemm_(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
           HAO_Complex16 *c, const HAO_INT *ldc);
void zher2k_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
            const HAO_Complex16 *b, const HAO_INT *ldb, const double *beta,
            HAO_Complex16 *c, const HAO_INT *ldc);
void zherk_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const double *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const double *beta, HAO_Complex16 *c, const HAO_INT *ldc);
void zsymm_(const char *side, const char *uplo, const HAO_INT *m, const HAO_INT *n,
           const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
           HAO_Complex16 *c, const HAO_INT *ldc);
void zsyr2k_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
            const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
            const HAO_Complex16 *b, const HAO_INT *ldb, const HAO_Complex16 *beta,
            HAO_Complex16 *c, const HAO_INT *ldc);
void zsyrk_(const char *uplo, const char *trans, const HAO_INT *n, const HAO_INT *k,
           const HAO_Complex16 *alpha, const HAO_Complex16 *a, const HAO_INT *lda,
           const HAO_Complex16 *beta, HAO_Complex16 *c, const HAO_INT *ldc);
void ztrmm_(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *b, const HAO_INT *ldb);
void ztrsm_(const char *side, const char *uplo, const char *transa, const char *diag,
           const HAO_INT *m, const HAO_INT *n, const HAO_Complex16 *alpha,
           const HAO_Complex16 *a, const HAO_INT *lda, HAO_Complex16 *b, const HAO_INT *ldb);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CUSTOMIZED_BLAS_H_ */
