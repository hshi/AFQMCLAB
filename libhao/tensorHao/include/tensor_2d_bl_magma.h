#ifndef TENSOR_2D_BL_MAGMA_H
#define TENSOR_2D_BL_MAGMA_H

#ifdef USE_MAGMA

#include <vector>
#include "tensor_core.h"
#include "tensor_hao_ref.h"
#include "tensorHao.h"
#include "tensor_element_wise.h"
#include "tensor_2d_common_fun.h"

namespace tensorHao
{

 /*************************************/
 /*Matrix Multiply C=alpha*A.B+beta*C */
 /*************************************/

 void gmm_magma(const TensorCore<float,2>& A, const TensorCore<float,2>& B, TensorCore<float,2>& C,
          char TRANSA='N', char TRANSB='N', float alpha=1, float beta=0);

 void gmm_magma(const TensorCore<double,2>& A, const TensorCore<double,2>& B, TensorCore<double,2>& C,
          char TRANSA='N', char TRANSB='N', double alpha=1, double beta=0);

 void gmm_magma(const TensorCore<std::complex<float>,2>& A, const TensorCore<std::complex<float>,2>& B, TensorCore<std::complex<float>,2>& C,
          char TRANSA='N', char TRANSB='N', std::complex<float> alpha=1, std::complex<float> beta=0);

 void gmm_magma(const TensorCore<std::complex<double>,2>& A, const TensorCore<std::complex<double>,2>& B, TensorCore<std::complex<double>,2>& C,
          char TRANSA='N', char TRANSB='N', std::complex<double> alpha=1, std::complex<double> beta=0);


 /*****************************************/
 /*Diagonalize symmetric/ Hermitian Matrix*/
 /*****************************************/

 void eigen_magma(TensorCore<double,2>& A, TensorCore<double,1>& W, char JOBZ='V', char UPLO='U');
 void eigen_magma(TensorCore<std::complex<double>,2>& A, TensorCore<double,1>& W, char JOBZ='V', char UPLO='U');


 /****************************************************************************/
 /*Construct LUDecomp, use GPU interface, only one LUconstruct_magma is okay.*/
 /****************************************************************************/

 LUDecomp< std::complex<double> > LUconstruct_magma(const TensorCore<std::complex<double>,2>& x);


 /**********************************************************************/
 /*Inverse of matrix, use gpu interface, only one inverse_magma is okay.*/
 /**********************************************************************/

 TensorHao<std::complex<double>,2> inverse_magma(const LUDecomp<std::complex<double>>& x);


 /*********************************************************/
 /*Solve linear equation of matrix A*M=B: return M=A^{-1}B*/
 /*********************************************************/

 TensorHao<std::complex<double>,2> solve_lineq_magma(const LUDecomp<std::complex<double>>& x, const TensorCore<std::complex<double>,2>& B, char TRANS='N');


 /***********************************************************/
 /*QR decompostion of matrix ph, return the determinant of R*/
 /***********************************************************/

 double QRMatrix_magma(TensorCore<std::complex<double>,2>& ph);
 double QRMatrix_magma(TensorCore<std::complex<double>,2>& ph, TensorCore<double,1>& det_list);


 /**********************************************************************************************/
 /*SVD a matrix U = U D V, input U, output U, D, and V. Note: output U and V are unitary matrix*/
 /**********************************************************************************************/

 void SVDMatrix_magma(TensorCore<std::complex<double>,2>& U, TensorCore<double,1>& D, TensorCore<std::complex<double>,2>& V);

} //end namespace tensorHao

#endif

#endif
