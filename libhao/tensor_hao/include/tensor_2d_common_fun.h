#ifndef TENSOR_2D_COMMON_FUN_H
#define TENSOR_2D_COMMON_FUN_H

#include <vector>
#include "tensor_core.h"
#include "tensor_hao_ref.h"
#include "tensor_hao.h"
#include "tensor_element_wise.h"
#include "../../lapackblas_hao/Hao_types.h"

namespace tensor_hao
{

 /**************/
 /* return A^T */
 /**************/
 template <class T>
 TensorHao<T,2> trans(const TensorCore<T,2>& A)
 {
     size_t L0 = A.rank(0); size_t L1 = A.rank(1);
     TensorHao<T,2> B(L1, L0);
     for(size_t i=0; i<L0; i++)
     {
         for(size_t j=0; j<L1; j++) B(j,i)=A(i,j);
     }
     return B;
 }

 /**************/
 /* return A^H */
 /**************/
 template <class T>
 TensorHao<T,2> conjtrans(const TensorCore<T,2>& A)
 {
     size_t L0 = A.rank(0); size_t L1 = A.rank(1);
     TensorHao<T,2> B(L1, L0);
     for(size_t i=0; i<L0; i++)
     {
         for(size_t j=0; j<L1; j++) B(j,i)=std::conj( A(i,j) );
     }
     return B;
 }

 /*****************************/
 /*Check Hermitian of a matrix*/
 /*****************************/
 void checkHermitian(const TensorCore<std::complex<double>, 2> &A);

 /*******************************************/
 /*LU decomposition of complex double matrix*/
 /*******************************************/
 template <class T> class LUDecomp
 {
     public:
     TensorHao<T,2> A;
     TensorHao<HAO_INT,1> ipiv;
     HAO_INT info;

     LUDecomp() {}
     LUDecomp(const LUDecomp<T>& x) {A=x.A;ipiv=x.ipiv;info=x.info;}
     LUDecomp(LUDecomp<T>&& x) {A=std::move(x.A);ipiv=std::move(x.ipiv);info=x.info;}
     ~LUDecomp() {}
     LUDecomp<T>& operator = (const LUDecomp<T>& x) {A=x.A;ipiv=x.ipiv;info=x.info;return *this;}
     LUDecomp<T>& operator = (LUDecomp<T>&& x) {A=std::move(x.A);ipiv=std::move(x.ipiv);info=x.info;return *this;}
 };

 /************************/
 /*Determinant of matrix*/
 /************************/
 std::complex<double> determinant(const LUDecomp<std::complex<double>>& x);
 void lognormPhaseDeterminant(const LUDecomp<std::complex<double>> &x, std::complex<double> &lognorm, std::complex<double> &phase);
 std::complex<double> logDeterminant(const LUDecomp<std::complex<double>> &x);

 /*******************************/
 /*Diagonal array multipy matrix*/
 /*******************************/
 TensorHao<std::complex<double>,2> dMultiMatrix(const TensorCore<std::complex<double>, 1> &D, const TensorCore<std::complex<double>, 2> &ph);

 /**********************/
 /*pfaffian of a matrix*/
 /**********************/
 void checkSkewSymmetric(const TensorCore<std::complex<double>, 2> &A);
 std::complex<double> pfaffian(TensorCore<std::complex<double>, 2> &A);

} //end namespace tensor_hao

#endif
