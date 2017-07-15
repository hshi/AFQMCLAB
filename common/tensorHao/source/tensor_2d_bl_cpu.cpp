#include "../include/tensor_2d_bl_cpu.h"
#include "../../lapackblasHao/blas_lapack_wrap.h"

using namespace std;

namespace tensor_hao
{

 /*************************************/
 /*Matrix Multiply C=alpha*A.B+beta*C */
 /*************************************/

 void gmm_cpu(const TensorCore<float,2>& A, const TensorCore<float,2>& B, TensorCore<float,2>& C,
          char TRANSA, char TRANSB, float alpha, float beta)
 {
     HAO_INT  M, N, K, LDA, LDB, LDC;
     M=(TRANSA=='N' || TRANSA=='n' ) ? A.rank(0): A.rank(1);
     K=(TRANSA=='N' || TRANSA=='n' ) ? A.rank(1): A.rank(0);
     N=(TRANSB=='N' || TRANSB=='n' ) ? B.rank(1): B.rank(0);
     LDA= A.rank(0);
     LDB= B.rank(0);
     LDC= C.rank(0);

     if( C.size()==0 ) return;
     if( A.size()==0 ) { C*=beta; return;}
     sgemm(&TRANSA, &TRANSB, &M, &N, &K, &alpha, A.data(), &LDA, B.data(), &LDB, &beta, C.data(), &LDC);
 }

 void gmm_cpu(const TensorCore<double,2>& A, const TensorCore<double,2>& B, TensorCore<double,2>& C,
          char TRANSA, char TRANSB, double alpha, double beta)
 {
     HAO_INT  M, N, K, LDA, LDB, LDC;
     M=(TRANSA=='N' || TRANSA=='n' ) ? A.rank(0): A.rank(1);
     K=(TRANSA=='N' || TRANSA=='n' ) ? A.rank(1): A.rank(0);
     N=(TRANSB=='N' || TRANSB=='n' ) ? B.rank(1): B.rank(0);
     LDA= A.rank(0);
     LDB= B.rank(0);
     LDC= C.rank(0);

     if( C.size()==0 ) return;
     if( A.size()==0 ) { C*=beta; return;}
     dgemm(&TRANSA, &TRANSB, &M, &N, &K, &alpha, A.data(), &LDA, B.data(), &LDB, &beta, C.data(), &LDC);
 }

 void gmm_cpu(const TensorCore<complex<float>,2>& A, const TensorCore<complex<float>,2>& B, TensorCore<complex<float>,2>& C,
          char TRANSA, char TRANSB, complex<float> alpha, complex<float> beta)
 {
     HAO_INT  M, N, K, LDA, LDB, LDC;
     M=(TRANSA=='N' || TRANSA=='n' ) ? A.rank(0): A.rank(1);
     K=(TRANSA=='N' || TRANSA=='n' ) ? A.rank(1): A.rank(0);
     N=(TRANSB=='N' || TRANSB=='n' ) ? B.rank(1): B.rank(0);
     LDA= A.rank(0);
     LDB= B.rank(0);
     LDC= C.rank(0);

     if( C.size()==0 ) return;
     if( A.size()==0 ) { C*=beta; return;}
     cgemm(&TRANSA, &TRANSB, &M, &N, &K, &alpha, A.data(), &LDA, B.data(), &LDB, &beta, C.data(), &LDC);
 }

 void gmm_cpu(const TensorCore<complex<double>,2>& A, const TensorCore<complex<double>,2>& B, TensorCore<complex<double>,2>& C,
          char TRANSA, char TRANSB, complex<double> alpha, complex<double> beta)
 {
     HAO_INT  M, N, K, LDA, LDB, LDC;
     M=(TRANSA=='N' || TRANSA=='n' ) ? A.rank(0): A.rank(1);
     K=(TRANSA=='N' || TRANSA=='n' ) ? A.rank(1): A.rank(0);
     N=(TRANSB=='N' || TRANSB=='n' ) ? B.rank(1): B.rank(0);
     LDA= A.rank(0);
     LDB= B.rank(0);
     LDC= C.rank(0);

     if( C.size()==0 ) return;
     if( A.size()==0 ) { C*=beta; return;}
     zgemm(&TRANSA, &TRANSB, &M, &N, &K, &alpha, A.data(), &LDA, B.data(), &LDB, &beta, C.data(), &LDC);
 }


 /******************************/
 /*Diagonalize symmetric Matrix*/
 /******************************/
 void eigen_cpu(TensorCore<double,2>& A, TensorCore<double,1>& W, char JOBZ, char UPLO)
 {
     if(A.rank(0) != A.rank(1) ) {cout<<"Input for eigen is not square matrix!"<<endl; exit(1);}
     if(A.rank(0) != W.rank(0) ) {cout<<"Input size of W is not consistent with A!"<<endl; exit(1);}
     HAO_INT N= A.rank(0); HAO_INT info;

     double work_test[1]; HAO_INT iwork_test[1]; HAO_INT lwork=-1; HAO_INT liwork=-1;
     dsyevd(&JOBZ, &UPLO, &N, A.data(), &N, W.data(), work_test, &lwork, iwork_test, &liwork ,&info);

     lwork=lround(work_test[0]); liwork=iwork_test[0];
     vector<double> work(lwork); vector<HAO_INT> iwork(liwork);
     dsyevd(&JOBZ, &UPLO, &N, A.data(), &N, W.data(), work.data(), &lwork, iwork.data(), &liwork ,&info);

     if(info!=0) {cout<<"Dsyevd failed: info= "<< info<<endl; exit(1);}
 }


 /******************************/
 /*Diagonalize Hermition Matrix*/
 /******************************/
 void eigen_cpu(TensorCore<complex<double>,2>& A, TensorCore<double,1>& W, char JOBZ, char UPLO)
 {
     if(A.rank(0) != A.rank(1) ) {cout<<"Input for eigen is not square matrix!"<<endl; exit(1);}
     if(A.rank(0) != W.rank(0) ) {cout<<"Input size of W is not consistent with A!"<<endl; exit(1);}
     HAO_INT N= A.rank(0); HAO_INT info;

     complex<double> work_test[1]; double rwork_test[1]; HAO_INT iwork_test[1];
     HAO_INT lwork=-1; HAO_INT lrwork=-1; HAO_INT liwork=-1;
     zheevd(&JOBZ, &UPLO, &N, A.data(), &N, W.data(), work_test, &lwork, rwork_test, &lrwork, iwork_test, &liwork ,&info);

     lwork=lround(work_test[0].real()); lrwork=lround(rwork_test[0]); liwork=iwork_test[0];
     vector<complex<double>> work(lwork); vector<double> rwork(lrwork); vector<HAO_INT> iwork(liwork);
     zheevd(&JOBZ, &UPLO, &N, A.data(), &N, W.data(), work.data(), &lwork, rwork.data(), &lrwork, iwork.data(), &liwork ,&info);

     if(info!=0) {cout<<"Zheevd failed: info= "<< info<<endl; exit(1);}
 }

 /******************************************/
 /*LU Decomposition a complex square Matrix*/
 /******************************************/
 LUDecomp<double> LUconstruct_cpu(const TensorCore<double, 2> &x)
 {
     if(x.rank(0) != x.rank(1) ) {cout<<"Input for LU is not square matrix!"<<endl; exit(1);}
     HAO_INT N= x.rank(0);
     LUDecomp<double> y; y.A=x; y.ipiv=TensorHao<HAO_INT,1>(N);

     if( x.size()==0 ) return y;
     dgetrf(&N, &N, y.A.data(), &N, y.ipiv.data(), &(y.info) );
     if(y.info<0) {cout<<"The "<<y.info<<"-th parameter is illegal in LUconstruct_cpu!"<<endl; exit(1);}
     return y;
 }

 LUDecomp<double> LUconstruct_cpu(TensorHao<double, 2> &&x)
 {
     if(x.rank(0) != x.rank(1) ) {cout<<"Input for LU is not square matrix!"<<endl; exit(1);}
     HAO_INT N= x.rank(0);
     LUDecomp<double> y; y.A= move(x); y.ipiv=TensorHao<HAO_INT,1>(N);

     if( x.size()==0 ) return y;
     dgetrf(&N, &N, y.A.data(), &N, y.ipiv.data(), &(y.info) );
     if(y.info<0) {cout<<"The "<<y.info<<"-th parameter is illegal in LUconstruct_cpu!"<<endl; exit(1);}
     return y;
 }

 LUDecomp<complex<double>> LUconstruct_cpu(const TensorCore<complex<double>,2>& x)
 {
     if(x.rank(0) != x.rank(1) ) {cout<<"Input for LU is not square matrix!"<<endl; exit(1);}
     HAO_INT N= x.rank(0);
     LUDecomp<complex<double>> y; y.A=x; y.ipiv=TensorHao<HAO_INT,1>(N);

     if( x.size()==0 ) return y;
     zgetrf(&N, &N, y.A.data(), &N, y.ipiv.data(), &(y.info) );
     if(y.info<0) {cout<<"The "<<y.info<<"-th parameter is illegal in LUconstruct_cpu!"<<endl; exit(1);}
     return y;
 }

 LUDecomp<complex<double>> LUconstruct_cpu(TensorHao<complex<double>,2>&& x)
 {
     if(x.rank(0) != x.rank(1) ) {cout<<"Input for LU is not square matrix!"<<endl; exit(1);}
     HAO_INT N= x.rank(0);
     LUDecomp<complex<double>> y; y.A= move(x); y.ipiv=TensorHao<HAO_INT,1>(N);

     if( x.size()==0 ) return y;
     zgetrf(&N, &N, y.A.data(), &N, y.ipiv.data(), &(y.info) );
     if(y.info<0) {cout<<"The "<<y.info<<"-th parameter is illegal in LUconstruct_cpu!"<<endl; exit(1);}
     return y;
 }


 /********************************************************************************************************************/
 /*Inverse of matrix: If determinant of the matrix is outof machine precision, inverse should be fine, since it solve*
  *The linear equation, every small value is well defined                                                            */
 /********************************************************************************************************************/
 void inverse_cpu_utilities(TensorCore<complex<double>, 2> &A, const TensorCore<HAO_INT, 1> &ipiv)
 {
     HAO_INT N= A.rank(0); HAO_INT info;

     HAO_INT lwork=-1; complex<double> work_test[1];
     zgetri(&N, A.data(), &N, ipiv.data(), work_test, &lwork, &info);

     lwork=lround(work_test[0].real());
     vector<complex<double>> work(lwork);
     zgetri(&N, A.data(), &N, ipiv.data(), work.data(), &lwork, &info);
     if(info<0) {cout<<"The "<<info<<"-th parameter is illegal in inverse_cpu_utilities!"<<endl; exit(1);}
 }

 TensorHao<complex<double>,2> inverse_cpu(const LUDecomp<complex<double>>& x)
 {
     TensorHao<complex<double>,2> A=x.A;
     inverse_cpu_utilities(A, x.ipiv);
     return A;
 }

 TensorHao<complex<double>,2> inverse_cpu(LUDecomp<complex<double>>&& x)
 {
     TensorHao<complex<double>,2> A=move(x.A);
     inverse_cpu_utilities(A, x.ipiv);
     return A;
 }

 /*********************************************************/
 /*Solve linear equation of matrix A*M=B: return M=A^{-1}B*/
 /*********************************************************/
 void solve_lineq_cpu_utilities(const LUDecomp<double>& x, TensorHao<double,2>& M, char TRANS)
 {
     if(x.A.rank(0) != M.rank(0) )  {cout<<"Input size for solving linear equation is not consistent!"<<endl; exit(1);}
     HAO_INT N= M.rank(0); HAO_INT NRHS= M.rank(1); HAO_INT info;

     if( M.size()==0 ) return;
     dgetrs(&TRANS, &N, &NRHS, x.A.data(), &N, x.ipiv.data(), M.data(), &N, &info);
     if(info!=0)
     {
         cout<<"Solve linear equation is not suceesful: "<<info<<"-th parameter is illegal!"<<endl;
         exit(1);
     }
 }

 void solve_lineq_cpu_utilities(const LUDecomp<complex<double>>& x, TensorHao<complex<double>,2>& M, char TRANS)
 {
     if(x.A.rank(0) != M.rank(0) )  {cout<<"Input size for solving linear equation is not consistent!"<<endl; exit(1);}
     HAO_INT N= M.rank(0); HAO_INT NRHS= M.rank(1); HAO_INT info;

     if( M.size()==0 ) return;
     zgetrs(&TRANS, &N, &NRHS, x.A.data(), &N, x.ipiv.data(), M.data(), &N, &info);
     if(info!=0)
     {
         cout<<"Solve linear equation is not suceesful: "<<info<<"-th parameter is illegal!"<<endl;
         exit(1);
     }
 }

 TensorHao<double, 2> solve_lineq_cpu(const LUDecomp<double> &x, const TensorCore<double, 2> &B, char TRANS)
 {
     TensorHao<double,2> M(B);
     solve_lineq_cpu_utilities(x, M, TRANS);
     return M;
 }

 TensorHao<double, 2> solve_lineq_cpu(const LUDecomp<double> &x, TensorHao<double, 2> &&B, char TRANS)
 {
     TensorHao<double,2> M( move(B) );
     solve_lineq_cpu_utilities(x, M, TRANS);
     return M;
 }

 TensorHao<complex<double>,2> solve_lineq_cpu(const LUDecomp<complex<double>>& x, const TensorCore<complex<double>,2>& B, char TRANS)
 {
     TensorHao<complex<double>,2> M(B);
     solve_lineq_cpu_utilities(x, M, TRANS);
     return M;
 }

 TensorHao<complex<double>,2> solve_lineq_cpu(const LUDecomp<complex<double>>& x, TensorHao<complex<double>,2>&&B, char TRANS)
 {
     TensorHao<complex<double>,2> M( move(B) );
     solve_lineq_cpu_utilities(x, M, TRANS);
     return M;
 }

 /******************************/
 /*QR decompostion of matrix ph*/
 /******************************/
 double QRMatrix_cpu(TensorCore<complex<double>,2>& ph)
 {
     HAO_INT L= ph.rank(0); HAO_INT N= ph.rank(1); HAO_INT info;
     HAO_INT lwork=-1; complex<double> work_test[1];
     vector<complex<double>> tau(N);

     zgeqrf (&L, &N, ph.data(), &L, tau.data(), work_test, &lwork, &info);

     lwork=lround(work_test[0].real());
     vector<complex<double>> work(lwork);
     zgeqrf (&L, &N, ph.data(), &L, tau.data(), work.data(), &lwork, &info);
     if(info!=0) {cout<<"QR run is not suceesful: "<<info<<"-th parameter is illegal!"<<endl; exit(1);}

     complex<double> det={1.0,0.0}; for (HAO_INT i=0; i<N; i++)  det*=ph(i,i);

     zungqr (&L, &N, &N, ph.data(), &L, tau.data(), work.data(), &lwork, &info);
     if(info!=0) {cout<<"Zungqr run is not suceesful: "<<info<<"-th parameter is illegal!"<<endl; exit(1);}

     if(det.real()<0) {det=-det; for(HAO_INT i=0; i<L; i++) ph(i,0)=-ph(i,0);}

     return det.real();
 }

 double QRMatrix_cpu(TensorCore<complex<double>,2>& ph, TensorCore<double,1>& det_list)
 {
     if(det_list.rank(0) != ph.rank(1) ) {cout<<"det_list size is not consistent with ph! "<<endl; exit(1); }

     HAO_INT L= ph.rank(0); HAO_INT N= ph.rank(1); HAO_INT info;
     HAO_INT lwork=-1; complex<double> work_test[1];
     vector<complex<double>> tau(N);

     zgeqrf (&L, &N, ph.data(), &L, tau.data(), work_test, &lwork, &info);

     lwork=lround(work_test[0].real());
     vector<complex<double>> work(lwork);
     zgeqrf (&L, &N, ph.data(), &L, tau.data(), work.data(), &lwork, &info);
     if(info!=0) {cout<<"QR run is not suceesful: "<<info<<"-th parameter is illegal!"<<endl; exit(1);}

     complex<double> det={1.0,0.0}; 
     for (HAO_INT i=0; i<N; i++)  {det_list(i)=ph(i,i).real(); det*=ph(i,i);}

     zungqr (&L, &N, &N, ph.data(), &L, tau.data(), work.data(), &lwork, &info);
     if(info!=0) {cout<<"Zungqr run is not suceesful: "<<info<<"-th parameter is illegal!"<<endl; exit(1);}

     if(det.real()<0)
     {
        det=-det;
        det_list(0)=-det_list(0);
        for(HAO_INT i=0; i<L; i++) ph(i,0)=-ph(i,0);
     }

     return det.real();
 }

 /*********************************************/
 /*SVD a matrix U = U D V, return U, D, and V*/
 /*********************************************/
 //Use zgesdd instead of zgesvd, since zgesdd is faster for large matrix: http://www.netlib.org/lapack/lug/node32.html
 //Test in Hurricane, zgesdd is faster.
 void SVDMatrix_cpu(TensorCore<complex<double>,2>& U, TensorCore<double,1>& D, TensorCore<complex<double>,2>& V)
 {
     if(U.rank(0)!= U.rank(1) || U.rank(1)!= D.rank(0) || D.rank(0)!= V.rank(0) || V.rank(0)!= V.rank(1) )
     {
         cout<<"size is not consistent in SVDMatrix_cpu! Only support square matrix."<<endl;
         exit(1);
     }

     HAO_INT m= U.rank(0); HAO_INT n= V.rank(0);
     char jobz='O'; HAO_INT lda=m;
     complex<double>* u=nullptr; HAO_INT ldu=1; HAO_INT ldv=n;
     complex<double> work_test[1]; HAO_INT lwork=-1;
     vector<double> rwork(5*m*m+7*m); vector<HAO_INT> iwork(8*m);
     HAO_INT info;

     zgesdd(&jobz, &m, &n, U.data(), &lda, D.data(), u, &ldu, V.data(), &ldv, work_test, &lwork, rwork.data(), iwork.data(), &info);

     lwork=lround(work_test[0].real());
     vector<complex<double>> work(lwork);

     zgesdd(&jobz, &m, &n, U.data(), &lda, D.data(), u, &ldu, V.data(), &ldv, work.data(), &lwork, rwork.data(), iwork.data(), &info);

     if(info!=0)
     {
         cout<<"SVDMatrix_cpu is not suceesful, info= "<<info<<endl;
         exit(1);
     }
 }

/*
 void SVDMatrix_cpu(TensorCore<complex<double>,2>& U, TensorCore<double,1>& D, TensorCore<complex<double>,2>& V)
 {
     if( U.rank(0)!=U.rank(1) || U.rank(1)!=D.rank(0) || D.rank(0)!=V.rank(0) || V.rank(0)!=V.rank(1) )
     {
         cout<<"size is not consistent in SVDMatrix_cpu! Only support square matrix."<<endl;
         exit(1);
     }

     HAO_INT m=U.rank(0); HAO_INT n=V.rank(0);
     char jobu='O'; char jobvt='A'; HAO_INT lda=m;
     complex<double>* u=nullptr; HAO_INT ldu=1; HAO_INT ldv=n;
     complex<double> work_test[1]; HAO_INT lwork=-1;
     vector<double> rwork(5*m);
     HAO_INT info;

     zgesvd(&jobu, &jobvt, &m, &n, U.data(), &lda, D.data(), u, &ldu, V.data(), &ldv, work_test, &lwork, rwork.data(), &info);

     lwork=lround(work_test[0].real());
     vector<complex<double>> work(lwork);

     zgesvd(&jobu, &jobvt, &m, &n, U.data(), &lda, D.data(), u, &ldu, V.data(), &ldv, work.data(), &lwork, rwork.data(), &info);

     if(info!=0)
     {
         cout<<"SVDMatrix_cpu is not suceesful, info= "<<info<<endl;
         exit(1);
     }
 }
*/

} //end namespace tensorHao
