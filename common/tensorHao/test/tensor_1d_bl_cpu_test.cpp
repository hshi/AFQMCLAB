#include <cmath>
#include "../include/tensor_1d_bl_cpu.h"
#include "../include/tensor_fill.h"
#include "../../testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(Tensor_1d_bl_cpu, copy)
{
    TensorHao<complex<double>,1> x(6), y(6);
    x = { {0.0,0.8},{3.0,4.0},{2.123,3.11},{2.0,3.3},{4.0,5.0},{3.123,4.11} };
    copy_cpu(x, y);
    EXPECT_FALSE( diff(x,y, 1e-12) );
}

TEST(Tensor_1d_bl_cpu, nrm2)
{
    TensorHao<complex<double>,1> x(6);
    x = { {0.0,0.8},{3.0,4.0},{2.123,3.11},{2.0,3.3},{4.0,5.0},{3.123,4.11} };

    double nrm2Expect(0);
    for(size_t i = 0; i < x.size() ; ++i)
    {
        nrm2Expect += std::norm( x(i) );
    }
    nrm2Expect = sqrt( nrm2Expect);

    double nrm2Actual = nrm2_cpu(x);

    EXPECT_DOUBLE_EQ( nrm2Expect, nrm2Actual);
}

TEST(Tensor_1d_bl_cpu, scale)
{
    TensorHao<complex<double>,1> x(6), y(6);
    x = { {0.0,0.8},{3.0,4.0},{2.123,3.11},{2.0,3.3},{4.0,5.0},{3.123,4.11} };
    complex<double> scale(2.0, 3.0);

    for(size_t i = 0; i < x.size() ; ++i)
    {
        y(i) = scale * x(i);
    }
    scal_cpu(scale, x);

    EXPECT_FALSE( diff(x, y, 1e-12) );
}

TEST(Tensor_1d_bl_cpu, dotc)
{
    TensorHao<complex<double>,1> x(6), y(6);
    x = { {0.0,0.8},{3.0,4.0},{2.123,3.11},{2.0,3.3},{4.0,5.0},{3.123,4.11} };
    y = { {0.2,0.8},{3.3,4.0},{6.123,3.11},{9.0,3.3},{4.0,5.1},{3.123,4.21} };

    complex<double> dotExact(0,0);
    for(size_t i = 0; i < x.size(); ++i)
    {
        dotExact += conj( x(i) ) * y(i);
    }

    complex<double> dotTest = dotc_cpu(x, y);

    EXPECT_COMPLEXDOUBLE_EQ(dotExact, dotTest);
}

TEST(Tensor_1d_bl_cpu, axpy)
{
    TensorHao<complex<double>,1> x(6), y(6), yExact(6);
    x = { {0.0,0.8},{3.0,4.0},{2.123,3.11},{2.0,3.3},{4.0,5.0},{3.123,4.11} };
    y = { {0.2,0.8},{3.3,4.0},{6.123,3.11},{9.0,3.3},{4.0,5.1},{3.123,4.21} };
    complex<double> a(2.0, 3.0);

    for(size_t i = 0; i < x.size(); ++i)
    {
        yExact(i) = a * x(i) + y(i);
    }

    axpy_cpu(a, x, y);
    EXPECT_FALSE( diff(yExact, y, 1e-12));
}

TEST(Tensor_1d_bl_cpu, gemvDouble)
{
    TensorHao<double,2> A(6,5);
    TensorHao<double,1> x(6), y(5), yExact(5);
    double alpha(2.0), beta(3.0);

    randomFill(A); randomFill(x); randomFill(y);

    for(size_t i = 0; i < A.rank(1); ++i)
    {
        yExact(i) = beta * y(i);
        for(size_t j = 0; j < A.rank(0); ++j)
        {
            yExact(i) += alpha * A(j,i) * x(j) ;
        }
    }

    gemv_cpu(A, x, y, 'T', alpha, beta);
    EXPECT_FALSE( diff(yExact, y, 1e-12));
}

TEST(Tensor_1d_bl_cpu, gemvComplexDouble)
{
    TensorHao<complex<double>,2> A(6,5);
    TensorHao<complex<double>,1> x(6), y(5), yExact(5);
    complex<double> alpha(2.0, 3.0), beta(1.0, 2.0);

    randomFill(A); randomFill(x); randomFill(y);

    for(size_t i = 0; i < A.rank(1); ++i)
    {
        yExact(i) = beta * y(i);
        for(size_t j = 0; j < A.rank(0); ++j)
        {
            yExact(i) += alpha * A(j,i) * x(j);
        }
    }

    gemv_cpu(A, x, y, 'T', alpha, beta);
    EXPECT_FALSE( diff(yExact, y, 1e-12));
}
