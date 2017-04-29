#ifndef TENSOR_2D_BL_CPU_H
#define TENSOR_2D_BL_CPU_H

#include <vector>
#include "tensor_core.h"
#include "tensor_hao_ref.h"
#include "tensor_hao.h"
#include "tensor_element_wise.h"
#include "tensor_2d_common_fun.h"

namespace tensor_hao
{

 /*************************************/
 /*Matrix Multiply C=alpha*A.B+beta*C */
 /*************************************/

 void gmm_cpu(const TensorCore<float,2>& A, const TensorCore<float,2>& B, TensorCore<float,2>& C,
          char TRANSA='N', char TRANSB='N', float alpha=1, float beta=0);

 void gmm_cpu(const TensorCore<double,2>& A, const TensorCore<double,2>& B, TensorCore<double,2>& C,
          char TRANSA='N', char TRANSB='N', double alpha=1, double beta=0);

 void gmm_cpu(const TensorCore<std::complex<float>,2>& A, const TensorCore<std::complex<float>,2>& B, TensorCore<std::complex<float>,2>& C,
          char TRANSA='N', char TRANSB='N', std::complex<float> alpha=1, std::complex<float> beta=0);

 void gmm_cpu(const TensorCore<std::complex<double>,2>& A, const TensorCore<std::complex<double>,2>& B, TensorCore<std::complex<double>,2>& C,
          char TRANSA='N', char TRANSB='N', std::complex<double> alpha=1, std::complex<double> beta=0);


 /*****************************************/
 /*Diagonalize symmetric/ Hermitian Matrix*/
 /*****************************************/

 void eigen_cpu(TensorCore<double,2>& A, TensorCore<double,1>& W, char JOBZ='V', char UPLO='U');
 void eigen_cpu(TensorCore<std::complex<double>,2>& A, TensorCore<double,1>& W, char JOBZ='V', char UPLO='U');


 /*****************************/
 /*Construct LUDecomp with CPU*/
 /*****************************/

 LUDecomp<double> LUconstruct_cpu(const TensorCore<double,2>& x);
 LUDecomp<double> LUconstruct_cpu(TensorHao<double,2>&& x);
 LUDecomp< std::complex<double> > LUconstruct_cpu(const TensorCore<std::complex<double>,2>& x);
 LUDecomp< std::complex<double> > LUconstruct_cpu(TensorHao<std::complex<double>,2>&& x);



 /*******************/
 /*Inverse of matrix*/
 /*******************/

 TensorHao<std::complex<double>,2> inverse_cpu(const LUDecomp<std::complex<double>>& x);
 TensorHao<std::complex<double>,2> inverse_cpu(LUDecomp<std::complex<double>>&& x);


 /*********************************************************/
 /*Solve linear equation of matrix x*M=B: return M=x^{-1}B*/
 /*********************************************************/

 TensorHao<double,2> solve_lineq_cpu(const LUDecomp<double>& x, const TensorCore<double,2>& B, char TRANS='N');
 TensorHao<double,2> solve_lineq_cpu(const LUDecomp<double>& x, TensorHao<double,2>&& B, char TRANS='N');
 TensorHao<std::complex<double>,2> solve_lineq_cpu(const LUDecomp<std::complex<double>>& x, const TensorCore<std::complex<double>,2>& B, char TRANS='N');
 TensorHao<std::complex<double>,2> solve_lineq_cpu(const LUDecomp<std::complex<double>>& x, TensorHao<std::complex<double>,2>&& B, char TRANS='N');


 /***********************************************************/
 /*QR decompostion of matrix ph, return the determinant of R*/
 /***********************************************************/

 double QRMatrix_cpu(TensorCore<std::complex<double>,2>& ph);
 double QRMatrix_cpu(TensorCore<std::complex<double>,2>& ph, TensorCore<double,1>& det_list);


 /**********************************************************************************************/
 /*SVD a matrix U = U D V, input U, output U, D, and V. Note: output U and V are unitary matrix*/
 /**********************************************************************************************/

 void SVDMatrix_cpu(TensorCore<std::complex<double>,2>& U, TensorCore<double,1>& D, TensorCore<std::complex<double>,2>& V);

} //end namespace tensor_hao

#endif
