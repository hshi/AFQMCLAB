#include "../include/tensor_1d_bl_cpu.h"
#include "../include/blas_lapack_wrap.h"

using namespace std;

namespace tensor_hao
{
    void copyBlas_cpu(const TensorCore<complex<double>, 1>& x, TensorCore<complex<double>,1>& y,
                      int incx, int incy)
    {
        int L = x.size();
        if( L != y.size() )
        {
            cerr<<"Size not consistent in copyBlas_cpu"<<endl; exit(1);
        }
        F77NAME(zcopy)(&L, x.data(), &incx, y.data(), &incy);
    }

    complex<double> normBlas_cpu(const TensorCore<complex<double>, 1> &x, int incx)
    {
        int L = x.size();
        complex<double> normBlas = F77NAME(dznrm2) ( &L , x.data() , &incx );
        return normBlas;
    }

    void scalBlas_cpu(complex<double> a, TensorCore<complex<double>, 1> &x, int incx)
    {
        int L = x.size();
        F77NAME(zscal) ( &L , &a , x.data() , &incx );
    }

    complex<double> dotcBlas_cpu(const TensorCore<complex<double>, 1> &x, const TensorCore<complex<double>, 1> &y,
                                 int incx, int incy)
    {
        int L = x.size();
        if( L != y.size() )
        {
            cerr<<"Size not consistent in dotcBlas_cpu"<<endl; exit(1);
        }
        complex<double> result;
        F77NAME(zdotc) (&result, &L, x.data(), &incx, y.data(), &incy);
        return result;
    }

    void axpyBlas_cpu(complex<double> a, const TensorCore<complex<double>, 1> &x,
                      TensorCore<complex<double>, 1> &y, int incx, int incy)
    {
        int L = x.size();
        if( L != y.size() )
        {
            cerr<<"Size not consistent in axpyBlas_cpu"<<endl; exit(1);
        }
        F77NAME(zaxpy) ( &L , &a , x.data() , &incx , y.data() , &incy );
    }

    void gemvBlas_cpu(const TensorCore<complex<double>, 2> & A,
                      const TensorCore<complex<double>, 1> & x, TensorCore<complex<double>, 1> &y,
                      char TRANSA, complex<double> alpha, complex<double> beta)
    {
        int M = A.rank(0); int N = A.rank(1);
        int incx=1; int incy=1;

        if(TRANSA=='N' || TRANSA=='n' )
        {
            if(x.rank(0) != N || y.rank(0) != M ) { cerr<<"Size not consistent in gemvBlas_cpu"<<endl; exit(1); }
        }
        else
        {
            if(x.rank(0) != M || y.rank(0) != N ) { cerr<<"Size not consistent in gemvBlas_cpu"<<endl; exit(1); }
        }

        F77NAME(zgemv) ( &TRANSA , &M , &N , &alpha , A.data() , &M , x.data() , &incx , &beta , y.data() , &incy );
    }

} //end namespace tensor_hao