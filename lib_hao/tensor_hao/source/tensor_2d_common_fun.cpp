#include "../include/tensor_2d_common_fun.h"
#include "../include/pfaffian_utilities.h"

using namespace std;

namespace tensor_hao
{
 /*****************************/
 /*Check Hermitian of a matrix*/
 /*****************************/
 int checkHermitian(const TensorCore<complex<double>, 2> &A)
 {
     int L0= A.getRank(0); int L1= A.getRank(1);
     if( L0!=L1 ) {cout<<"Input for Hermitian is not square matrix!"<<endl; exit(1);}
     double error=0; double norm=0;
     for(int j=0; j<L1; j++)
     {
         for(int i=j; i<L0; i++)
         {
             error+=abs(A(i,j)-conj(A(j,i)));
             norm+=abs(A(i,j));
         }
     }
     norm/=(A.size()*1.0);
     if(error/norm>1e-12) 
     {
         cout<<"Warning!!!!!Matrix is not Hermition! "<<error<<" "<<norm<<endl;
         return 1;
     }
     else
     {
         return 0;
     }

 }

 /***********************/
 /*Determinant of matrix*/
 /***********************/
 complex<double> determinant(const LUDecomp<complex<double>>& x)
 {
     if(x.info>0) return 0;

     complex<double> det(1,0);
     int L= x.ipiv.getRank(0);
     for(int i=0;i<L;i++)
     {
         if(x.ipiv(i)!=(i+1)) det*=(-x.A(i,i));
         else det*=x.A(i,i);
     }
     return det;
 }

 /****************************************/
 /*Get log(|det|) and det/|det| of matrix*/
 /****************************************/
 void lognormPhaseDeterminant(const LUDecomp<complex<double>> &x, complex<double> &lognorm, complex<double> &phase)
 {
     if(x.info>0)
     {
         cout<<"WARNING!!!! lognormPhaseDeterminant function has zero determinant!"<<endl;
         lognorm=complex<double>(-1e300,0.0);
         phase=complex<double>(1.0,0.0);
         return;
     }

     lognorm=0.0; phase=1.0;
     int L= x.ipiv.getRank(0);
     for(int i=0;i<L;i++)
     {
         lognorm+=log(abs(x.A(i,i)));
         if(x.ipiv(i)!=(i+1)) phase*=(-x.A(i,i)/abs(x.A(i,i)));
         else phase*=(x.A(i,i)/abs(x.A(i,i)));
     }
     return;
 }

 /***************************/
 /*Log determinant of matrix*/
 /***************************/
 complex<double> logDeterminant(const LUDecomp<complex<double>> &x)
 {
     complex<double> log_det,phase;
     lognormPhaseDeterminant(x, log_det, phase);
     log_det+=log(phase);
     return log_det;
 }


 /*******************************/
 /*Diagonal array multipy matrix*/
 /*******************************/
 TensorHao<complex<double>,2> dMultiMatrix(const TensorCore<complex<double>, 1> &D, const TensorCore<complex<double>, 2> &ph)
 {
     if(D.getRank(0) != ph.getRank(0) ) {cout<<"dMultiMatrix input error: D.rank(0)!=ph.getRank(0)!"<<endl; exit(1);}

     int L0 = ph.getRank(0); int L1 = ph.getRank(1);
     TensorHao<complex<double>,2> ph_new(L0, L1);

     //The order about loop i,j is important
     for(int j=0; j<L1; j++)
     {
         for(int i=0; i<L0; i++) ph_new(i,j)=D(i)*ph(i,j);
     }

     return ph_new;
 }

 /************************************/
 /*Check skew symmetric of the matrix*/
 /************************************/
 int checkSkewSymmetric(const TensorCore<complex<double>, 2> &A)
 {
     int L0= A.getRank(0); int L1= A.getRank(1);
     if( L0!=L1 ) {cout<<"Input for checkSkewSymmetric is not square matrix!"<<endl; exit(1);}

     double error=0; double norm=0;
     for(int j=0; j<L1; j++)
     {
         for(int i=j; i<L0; i++)
         {
             error+=abs( A(i,j)+A(j,i) );
             norm+=abs(A(i,j));
         }
     }

     norm/=(A.size()*1.0);

     if(error/norm>1e-12) 
     {
         cout<<"Warning!!!!!Matrix is not skew symmetric! "<<error<<" "<<norm<<endl;
         return 1;
     }
     else
     {
         return 0;
     }
 }

 /**********************/
 /*pfaffian of a matrix*/
 /**********************/
 complex<double> pfaffian(TensorCore<complex<double>, 2> &A)
 {
    int L0 = A.getRank(0); int L1 = A.getRank(1);
    if( L0!=L1 ) {cout<<"pfaffian input error: A.rank(0)!=A.getRank(1)!"<<endl; exit(1);}
    return pfaffian_aitken(A.data(), L0, L1);
 }


} //end namespace tensor_hao
