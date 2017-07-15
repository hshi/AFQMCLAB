#include "../include/tensor_1d_bl_cpu.h"
#include "../../lapackblasHao/blas_lapack_wrap.h"

using namespace std;

namespace tensor_hao
{
    double nrm2_cpu(const TensorCore<complex<double>, 1> &x, size_t incx)
    {
        HAO_INT L = x.size(); HAO_INT inc_x = incx;
        return dznrm2 ( &L , x.data() , &inc_x );
    }

    void scal_cpu(complex<double> a, TensorCore<complex<double>, 1> &x, size_t incx)
    {
        HAO_INT L = x.size(); HAO_INT inc_x = incx;
        zscal ( &L , &a , x.data() , &inc_x );
    }

    complex<double> dotc_cpu(const TensorCore<complex<double>, 1> &x, const TensorCore<complex<double>, 1> &y,
                             size_t incx, size_t incy)
    {
        HAO_INT L = x.size(); HAO_INT inc_x = incx; HAO_INT inc_y = incy;
        if( x.size() != y.size() )
        {
            cerr<<"Size not consistent in dotc_cpu"<<endl; exit(1);
        }
        complex<double> result;
#ifndef FORTRAN_COMPLEX_FUNCTIONS_RETURN_VOID
        result = zdotc(
#else
        zdotc( &result,
#endif
        &L, x.data(), &inc_x, y.data(), &inc_y);

        return result;
    }

    void axpy_cpu(complex<double> a, const TensorCore<complex<double>, 1> &x,
                  TensorCore<complex<double>, 1> &y, size_t incx, size_t incy)
    {
        HAO_INT L = x.size(); HAO_INT inc_x = incx; HAO_INT inc_y = incy;
        if( x.size() != y.size() )
        {
            cerr<<"Size not consistent in axpy_cpu"<<endl; exit(1);
        }
        zaxpy ( &L , &a , x.data() , &inc_x , y.data() , &inc_y );
    }

    void gemv_cpu(const TensorCore<double, 2> &A, const TensorCore<double, 1> &x, TensorCore<double, 1> &y, char TRANSA,
                  double alpha, double beta)
    {
        HAO_INT M = A.rank(0); HAO_INT N = A.rank(1);
        HAO_INT inc_x=1; HAO_INT inc_y=1;

        if(TRANSA=='N' || TRANSA=='n' )
        {
            if(x.rank(0) != A.rank(1) || y.rank(0) != A.rank(0) )
            {
                cerr<<"Size not consistent in gemv_cpu"<<endl;
                exit(1);
            }
        }
        else
        {
            if(x.rank(0) != A.rank(0) || y.rank(0) != A.rank(1) )
            {
                cerr<<"Size not consistent in gemv_cpu"<<endl;
                exit(1);
            }
        }

        if( y.size()==0 ) return;
        if( A.size()==0 ) { y*=beta; return; }
        dgemv ( &TRANSA , &M , &N , &alpha , A.data() , &M , x.data() , &inc_x , &beta , y.data() , &inc_y );
    }

    void gemv_cpu(const TensorCore<complex<double>, 2> &A,
                  const TensorCore<complex<double>, 1> &x, TensorCore<complex<double>, 1> &y,
                  char TRANSA, complex<double> alpha, complex<double> beta)
    {
        HAO_INT M = A.rank(0); HAO_INT N = A.rank(1);
        HAO_INT inc_x=1; HAO_INT inc_y=1;

        if(TRANSA=='N' || TRANSA=='n' )
        {
            if(x.rank(0) != A.rank(1) || y.rank(0) != A.rank(0) )
            {
                cerr<<"Size not consistent in gemv_cpu"<<endl;
                exit(1);
            }
        }
        else
        {
            if(x.rank(0) != A.rank(0) || y.rank(0) != A.rank(1) )
            {
                cerr<<"Size not consistent in gemv_cpu"<<endl;
                exit(1);
            }
        }

        if( y.size()==0 ) return;
        if( A.size()==0 ) { y*=beta; return; }
        zgemv ( &TRANSA , &M , &N , &alpha , A.data() , &M , x.data() , &inc_x , &beta , y.data() , &inc_y );
    }

} //end namespace tensor_hao
