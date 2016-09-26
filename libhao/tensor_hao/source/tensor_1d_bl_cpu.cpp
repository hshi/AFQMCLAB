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
        zcopy(&L, x.data(), &incx, y.data(), &incy);
    }

    complex<double> normBlas_cpu(const TensorCore<complex<double>, 1> &x, int incx)
    {
        int L = x.size();
        complex<double> normBlas = dznrm2 ( &L , x.data() , &incx );
        return normBlas;
    }

    void scalBlas_cpu(complex<double> a, TensorCore<complex<double>, 1> &x, int incx)
    {
        int L = x.size();
        zscal ( &L , &a , x.data() , &incx );
    }
} //end namespace tensor_hao