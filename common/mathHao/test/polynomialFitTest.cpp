//
// Created by boruoshihao on 4/29/17.
//
#include "../include/polynomialFit.h"
#include "../../testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST (polynomialFitTest, zeroOrder)
{
    TensorHao<double, 1> x(5); x={0, 1, 2, 3, 4};
    TensorHao<double, 1> y(5); y={0.2, 0.1, 0.3, 0.15, 0.25};
    TensorHao<double, 1> coeExact(1); coeExact = {0.2};

    PolynomialFit polynomialFit(x,y,0);
    const TensorHao<double, 1> &coe = polynomialFit.getCoefficient();

    EXPECT_FALSE ( diff(coe, coeExact,1e-8) );
}

TEST (polynomialFitTest, firstOrder)
{
    TensorHao<double, 1> x(5); x={0, 1, 2, 3, 4};
    TensorHao<double, 1> y(5); y={0.2, 1.2, 2.2, 3.2, 4.2};
    TensorHao<double, 1> coeExact(2); coeExact = {0.2, 1.0};

    PolynomialFit polynomialFit(x,y,1);
    const TensorHao<double, 1> &coe = polynomialFit.getCoefficient();

    EXPECT_FALSE ( diff(coe, coeExact,1e-8) );
    EXPECT_FALSE ( diff(polynomialFit.returnFittedY(), y, 1e-8) );
}

TEST (polynomialFitTest, secondOrder)
{
    TensorHao<double, 1> x(5); x={0, 1, 2, 3, 4};
    TensorHao<double, 1> y(5); y={1.0, 1.8, 1.3, 2.5, 6.4};
    //Exact result is from the sample code online
    TensorHao<double, 1> coeExact(3); coeExact = {1.4285714285714248, -1.1071428571428525, 0.5642857142857133};

    PolynomialFit polynomialFit(x,y,2);
    const TensorHao<double, 1> &coe = polynomialFit.getCoefficient();

    EXPECT_FALSE ( diff(coe, coeExact,1e-8) );
}

TEST (polynomialFitTest, thirdOrder)
{
    TensorHao<double, 1> x(5); x={1.0, 1.2, 1.4, 1.6, 1.8};
    TensorHao<double, 1> y(5); y={10.9, 16.1872, 23.1256, 31.9504, 42.8968};
    TensorHao<double, 1> coeExact(4); coeExact = {1, 2, 3, 4.9};

    PolynomialFit polynomialFit(x,y,3);
    const TensorHao<double, 1> &coe = polynomialFit.getCoefficient();

    EXPECT_FALSE ( diff(coe, coeExact,1e-8) );
    EXPECT_FALSE ( diff(polynomialFit.returnFittedY(), y, 1e-8) );
}
