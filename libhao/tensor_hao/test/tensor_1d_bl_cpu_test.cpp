#include <cmath>
#include "../include/tensor_1d_bl_cpu.h"
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
    for(int i = 0; i < x.size() ; ++i)
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

    for(int i = 0; i < x.size() ; ++i)
    {
        y(i) = scale * x(i);
    }
    scalBlas_cpu(scale, x);

    EXPECT_FALSE( diff(x, y, 1e-12) );
}