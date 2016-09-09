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

 void gmm_cpu(const Tensor_core<float,2>& A, const Tensor_core<float,2>& B, Tensor_core<float,2>& C,
          char TRANSA='N', char TRANSB='N', float alpha=1, float beta=0);

 void gmm_cpu(const Tensor_core<double,2>& A, const Tensor_core<double,2>& B, Tensor_core<double,2>& C,
          char TRANSA='N', char TRANSB='N', double alpha=1, double beta=0);

 void gmm_cpu(const Tensor_core<std::complex<float>,2>& A, const Tensor_core<std::complex<float>,2>& B, Tensor_core<std::complex<float>,2>& C,
          char TRANSA='N', char TRANSB='N', std::complex<float> alpha=1, std::complex<float> beta=0);

 void gmm_cpu(const Tensor_core<std::complex<double>,2>& A, const Tensor_core<std::complex<double>,2>& B, Tensor_core<std::complex<double>,2>& C,
          char TRANSA='N', char TRANSB='N', std::complex<double> alpha=1, std::complex<double> beta=0);


 /*****************************************/
 /*Diagonalize symmetric/ Hermitian Matrix*/
 /*****************************************/

 void eigen_cpu(Tensor_core<double,2>& A, Tensor_core<double,1>& W, char JOBZ='V', char UPLO='U');
 void eigen_cpu(Tensor_core<std::complex<double>,2>& A, Tensor_core<double,1>& W, char JOBZ='V', char UPLO='U');


 /*****************************/
 /*Construct LUDecomp with CPU*/
 /*****************************/

 LUDecomp< std::complex<double> > LUconstruct_cpu(const Tensor_core<std::complex<double>,2>& x);
 LUDecomp< std::complex<double> > LUconstruct_cpu(Tensor_hao<std::complex<double>,2>&& x);


 /*******************/
 /*Inverse of matrix*/
 /*******************/

 Tensor_hao<std::complex<double>,2> inverse_cpu(const LUDecomp<std::complex<double>>& x);
 Tensor_hao<std::complex<double>,2> inverse_cpu(LUDecomp<std::complex<double>>&& x);


 /*********************************************************/
 /*Solve linear equation of matrix A*M=B: return M=A^{-1}B*/
 /*********************************************************/

 Tensor_hao<std::complex<double>,2> solve_lineq_cpu(const LUDecomp<std::complex<double>>& x, const Tensor_core<std::complex<double>,2>& B, char TRANS='N');
 Tensor_hao<std::complex<double>,2> solve_lineq_cpu(const LUDecomp<std::complex<double>>& x, Tensor_hao<std::complex<double>,2>&& B, char TRANS='N');


 /***********************************************************/
 /*QR decompostion of matrix ph, return the determinant of R*/
 /***********************************************************/

 double QRMatrix_cpu(Tensor_core<std::complex<double>,2>& ph);
 double QRMatrix_cpu(Tensor_core<std::complex<double>,2>& ph, Tensor_core<double,1>& det_list);


 /**********************************************************************************************/
 /*SVD a matrix U = U D V, input U, output U, D, and V. Note: output U and V are unitary matrix*/
 /**********************************************************************************************/

 void SVDMatrix_cpu(Tensor_core<std::complex<double>,2>& U, Tensor_core<double,1>& D, Tensor_core<std::complex<double>,2>& V);

} //end namespace tensor_hao

#endif
