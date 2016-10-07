#ifndef PFAFFIAN_UTILITIES_H
#define PFAFFIAN_UTILITIES_H

#include <iostream>
#include <complex>

//NOTE: When we loop for T* A, we need to make sure it is continous memory
//Current code might be slower!

namespace tensor_hao
{
 //Goal:  Exchange rows i1 i2 and columns i1 i2 of a skew symmetric matrix A
 //Input: T* A 
 //         A is a skew symmetric input matrix with dimension NxN, actual space
 //         is LDAxN; We only assumed upper triangular part.
 //       size_t LDA, N 
 //         Dimension of matrix A
 //       size_t i1, i2
 //         the row and columns to be exchanged.
 //
 //Output: T* A
 //         Only the upper triangular part is exchanged.
 template<class T> 
 void exchange_row_columns_skew_matrix(T* A, size_t LDA, size_t N, size_t i1, size_t i2)
 {
     if(i1==i2) return; // No need to exchange
 
     T tmp; size_t i;
 
     if(i1>i2) {i=i1; i1=i2; i2=i;}  // make sure i1<i2
 
     // exchange A(i1, i2)
     A[i1+i2*LDA] = -A[i1+i2*LDA];
     // exchange i1 and i2 columns, only 0~i1-1 elements
     for(i=0; i<i1;  i++)    { tmp = A[i+i1*LDA]; A[i+i1*LDA] = A[i+i2*LDA]; A[i+i2*LDA] = tmp; }
     // exchange i1 and i2 rows; only i2+1~N-1 elements
     for(i=i2+1; i<N; i++)   { tmp = A[i1+i*LDA]; A[i1+i*LDA] = A[i2+i*LDA]; A[i2+i*LDA] = tmp; }
     // exchange i1 row to i2 columns, with a minus sign, only i1+1~i2-1 elements 
     for(i=i1+1; i<i2; i++)  { tmp = A[i1+i*LDA]; A[i1+i*LDA] =-A[i+i2*LDA]; A[i+i2*LDA] =-tmp; }
 }
 
 
 //Goal:   Compute the pfaffian of a skew-symmetric matrix A using
 //        the ideas of Aitken's block diagonalization formula. 
 //        Full pivoting is implemented to make the whole procedure stable.
 //        reference: Computer Physics Communications 182 (2011) 2213–2218
 //Input:  T* A 
 //          A is a skew symmetric input matrix with dimension NxN, actual space
 //          is LDAxN; We only need upper triangular part.
 //        size_t LDA, N 
 //          Dimension of matrix A
 //        T epsln
 //          A small number for convergence, e.g. 1+epsln=1
 //Output: T pfaffian_aitken
 //          The value of pfaffian 
 //        T* A
 //          Currently no meaning
 //          We can change the code to contain the transformation matrix in lower triangular part of A
 //          And also return the pivoting matrix.
 template<class T>
 T pfaffian_aitken(T* A, size_t LDA, size_t N, T epsln=0)
 {
    if( (N%2) == 1) return 0; //odd matrix has zero pfaffian
    size_t NB=N/2; if (NB==1) return A[LDA]; // 2x2 matrix has A(0,1) pfaffian
 
       
    T pf=1; size_t NR,NC,I1,I2; T phas,ss,Atmp;
    T zero=0; auto big=std::abs(zero); 
    for(size_t IB=0; IB<NB-1; IB++)
    {
       NR=IB*2; NC=NR+1; // (0,1) element of 2x2 matrix
 
       //Find the big value
       big=0; I1=NR; I2=NC;
       for(size_t i=NR; i<N-1; i++)
       {
          for(size_t j=i+1; j<N; j++)
          {
             if( std::abs( A[i+j*LDA] ) > big ) { big = std::abs( A[i+j*LDA] ); I1 = i; I2 = j; }
          }
       }
 
       phas = 1; if(I1==NR) phas = -phas; if(I2==NC) phas = -phas;
 
       //Exchange NR,I1 and NC, I2
       exchange_row_columns_skew_matrix(A, LDA, N, NR, I1);
       exchange_row_columns_skew_matrix(A, LDA, N, NC, I2);
 
       ss = A[NR+NC*LDA];
       if( std::abs(ss) <= std::abs(epsln) ) return 0;
      
       //Updating the Schur complement matrix 
       for(size_t i=2*IB+2; i<N-1; i++)
       {
          for(size_t j=i+1; j<N; j++)
          {   
             A[i+j*LDA] = A[i+j*LDA] + ( A[NC+i*LDA]*A[NR+j*LDA]-A[NR+i*LDA]*A[NC+j*LDA] ) / ss;
          }
       }
 
       //Swapping       
       if( IB > 0)
       {
          for(size_t j=0; j<2*IB+2; j++)
          { 
              Atmp = A[NR+j*LDA]; A[NR+j*LDA] = A[I1+j*LDA]; A[I1+j*LDA] = Atmp;
              Atmp = A[NC+j*LDA]; A[NC+j*LDA] = A[I2+j*LDA]; A[I2+j*LDA] = Atmp;
          }
       }
 
       pf = pf * ss * phas;
    }
 
    pf = pf * A[N-2+(N-1)*LDA];
 
    return pf;
 }

} //end namespace tensor_hao
#endif
