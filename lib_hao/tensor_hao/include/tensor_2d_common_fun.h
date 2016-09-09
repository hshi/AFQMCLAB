#ifndef TENSOR_2D_COMMON_FUN_H
#define TENSOR_2D_COMMON_FUN_H

#include <vector>
#include "tensor_core.h"
#include "tensor_hao_ref.h"
#include "tensor_hao.h"
#include "tensor_element_wise.h"

namespace tensor_hao
{

 /**************/
 /* return A^T */
 /**************/
 template <class T>
 Tensor_hao<T,2> trans(const Tensor_core<T,2>& A)
 {
     int L0 = A.rank(0); int L1 = A.rank(1);
     Tensor_hao<T,2> B(L1, L0);
     for(int i=0; i<L0; i++)
     {
         for(int j=0; j<L1; j++) B(j,i)=A(i,j);
     }
     return B;
 }

 /**************/
 /* return A^H */
 /**************/
 template <class T>
 Tensor_hao<T,2> conjtrans(const Tensor_core<T,2>& A)
 {
     int L0 = A.rank(0); int L1 = A.rank(1);
     Tensor_hao<T,2> B(L1, L0);
     for(int i=0; i<L0; i++)
     {
         for(int j=0; j<L1; j++) B(j,i)=std::conj( A(i,j) );
     }
     return B;
 }

 /*****************************/
 /*Check Hermitian of a matrix*/
 /*****************************/
 int check_Hermitian(const Tensor_core<std::complex<double>,2>& A);

 /*******************************************/
 /*LU decomposition of complex double matrix*/
 /*******************************************/
 template <class T> class LUDecomp
 {
     public:
     Tensor_hao<T,2> A;
     Tensor_hao<int,1> ipiv;
     int info;

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
 void lognorm_phase_determinant(const LUDecomp<std::complex<double>>& x, std::complex<double>& lognorm, std::complex<double>& phase);
 std::complex<double> log_determinant(const LUDecomp<std::complex<double>>& x);

 /*******************************/
 /*Diagonal array multipy matrix*/
 /*******************************/
 Tensor_hao<std::complex<double>,2> D_Multi_Matrix(const Tensor_core<std::complex<double>,1>& D,const Tensor_core<std::complex<double>,2>& ph);

 /**********************/
 /*Pfaffian of a matrix*/
 /**********************/
 int check_skew_symmetric(const Tensor_core<std::complex<double>,2>& A);
 std::complex<double> Pfaffian(Tensor_core<std::complex<double>,2>& A);

} //end namespace tensor_hao

#endif
