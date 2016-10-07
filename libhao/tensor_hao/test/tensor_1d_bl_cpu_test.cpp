#include <cmath>
#include "../include/tensor_1d_bl_cpu.h"
#include "../include/tensor_fill.h"
#include "../../test_hao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(Tensor_1d_bl_cpu, copyBlas)
{
    TensorHao<complex<double>,1> x(6), y(6);
    x = { {0.0,0.8},{3.0,4.0},{2.123,3.11},{2.0,3.3},{4.0,5.0},{3.123,4.11} };
    copyBlas_cpu(x, y);
    EXPECT_FALSE( diff(x,y, 1e-12) );
}

TEST(Tensor_1d_bl_cpu, normBlas)
{
    TensorHao<complex<double>,1> x(6);
    x = { {0.0,0.8},{3.0,4.0},{2.123,3.11},{2.0,3.3},{4.0,5.0},{3.123,4.11} };

    complex<double> norm_exact(0,0);
    for(size_t i = 0; i < x.size() ; ++i)
    {
        norm_exact += std::norm( x(i) );
    }
    norm_exact = sqrt( norm_exact);

    complex<double> norm_blas = normBlas_cpu(x);

    EXPECT_COMPLEXDOUBLE_EQ( norm_exact, norm_blas);
}

TEST(Tensor_1d_bl_cpu, scaleBlas)
{
    TensorHao<complex<double>,1> x(6), y(6);
    x = { {0.0,0.8},{3.0,4.0},{2.123,3.11},{2.0,3.3},{4.0,5.0},{3.123,4.11} };
    complex<double> scale(2.0, 3.0);

    for(size_t i = 0; i < x.size() ; ++i)
    {
        y(i) = scale * x(i);
    }
    scalBlas_cpu(scale, x);

    EXPECT_FALSE( diff(x, y, 1e-12) );
}

TEST(Tensor_1d_bl_cpu, dotcBlas)
{
    TensorHao<complex<double>,1> x(6), y(6);
    x = { {0.0,0.8},{3.0,4.0},{2.123,3.11},{2.0,3.3},{4.0,5.0},{3.123,4.11} };
    y = { {0.2,0.8},{3.3,4.0},{6.123,3.11},{9.0,3.3},{4.0,5.1},{3.123,4.21} };

    complex<double> dotExact(0,0);
    for(size_t i = 0; i < x.size(); ++i)
    {
        dotExact += conj( x(i) ) * y(i);
    }

    complex<double> dotTest = dotcBlas_cpu(x, y);

    EXPECT_COMPLEXDOUBLE_EQ(dotExact, dotTest);
}

TEST(Tensor_1d_bl_cpu, axpyBlas_cpu)
{
    TensorHao<complex<double>,1> x(6), y(6), yExact(6);
    x = { {0.0,0.8},{3.0,4.0},{2.123,3.11},{2.0,3.3},{4.0,5.0},{3.123,4.11} };
    y = { {0.2,0.8},{3.3,4.0},{6.123,3.11},{9.0,3.3},{4.0,5.1},{3.123,4.21} };
    complex<double> a(2.0, 3.0);

    for(size_t i = 0; i < x.size(); ++i)
    {
        yExact(i) = a * x(i) + y(i);
    }

    axpyBlas_cpu(a, x, y);
    EXPECT_FALSE( diff(yExact, y, 1e-12));
}

TEST(Tensor_1d_bl_cpu, gemvBlas_cpu)
{
    TensorHao<complex<double>,2> A(6,5);
    TensorHao<complex<double>,1> x(6), y(5), yExact(5);
    complex<double> alpha(2.0, 3.0), beta(1.0, 2.0);

    randomFill(A); randomFill(x);

    for(size_t i = 0; i < A.rank(1); ++i)
    {
        yExact(i) = 0.0;
        for(size_t j = 0; j < A.rank(0); ++j)
        {
            yExact(i) += alpha * A(j,i) * x(j) + beta * y(i);
        }
    }

    gemvBlas_cpu(A, x, y, 'T' ,alpha, beta);
    EXPECT_FALSE( diff(yExact, y, 1e-12));
}
