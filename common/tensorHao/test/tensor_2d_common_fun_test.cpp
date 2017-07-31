#include <cmath>
#include <stdexcept>
#include "../include/tensor_2d_common_fun.h"
#include "../include/tensor_2d_bl_cpu.h"
#include "../include/tensor_2d_bl_magma.h"
#include "../../testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(Tensor_2d_common_fun, trans)
{
    TensorHao<double, 2> A(2,3), B(3,2), B_exact(3,2);
    A={1.,2.,3.,4.,5.,6.};
    B_exact={1.,3.,5.,2.,4.,6.};
    B=trans(A);
    EXPECT_FALSE ( diff(B, B_exact, 1e-12) );
}

TEST(Tensor_2d_common_fun, conjtrans)
{
    TensorHao<complex<double>, 2> A(2,3), B(3,2), B_exact(3,2);
    A={ {1.,1.}, {2.,2.}, {3.,3.}, {4.,4.}, {5.,5.}, {6.,6.} };
    B_exact={ {1.,-1.}, {3.,-3.}, {5.,-5.}, {2.,-2.}, {4.,-4.}, {6.,-6.} };
    B=conjtrans(A);
    EXPECT_FALSE ( diff(B, B_exact, 1e-12) );
}

TEST(Tensor_2d_common_fun, symmetry)
{
    TensorHao<double,2> a(3,3);
    a = { 1.0, 3.0, 2.123,
          3.0, 2.0, 5.123,
          2.123, 5.223, 3 };
    try
    {
        checkSymmetry(a);
    }
    catch(runtime_error& err)
    {
        EXPECT_EQ( "ERROR!!! Matrix is not symmetric!", string(err.what()) );
    }
}

TEST(Tensor_2d_common_fun, Hermitian)
{
    TensorHao<complex<double>,2> a(3,3);
    a = { {1.0,0.0} ,   {3.0,4.0},    {2.123,3.11},
          {6.0,-4.0},   {2.0,0.0},    {5.123,3.11},
          {2.123,-3.11},{5.123,-3.11},{3,0.0}     };
    try
    {
        checkHermitian(a);
    }
    catch(runtime_error& err)
    {
        EXPECT_EQ( "ERROR!!! Matrix is not Hermition!", string(err.what()) );
    }
}

TEST(Tensor_2d_common_fun, LUDecomp)
{
    TensorHao<complex<double>,2> X(3,3);
    X = { {1.0,0.0} ,   {3.0,4.0},    {2.123,3.11},
          {3.0,-2.0},   {2.0,0.0},    {5.123,3.11},
          {2.123,-5.11},{5.123,-6.11},{3,0.0} };

    LUDecomp<complex<double>> LU=LUconstruct_cpu(X);

    TensorHao<complex<double>,2> A_exact=LU.A;

    LUDecomp<complex<double>> LUC(LU);
    EXPECT_FALSE ( diff(LUC.A,A_exact,1e-13) );

    LUDecomp<complex<double>> LUR(std::move(LU));
    EXPECT_FALSE ( diff(LUR.A,A_exact,1e-13) );

    LUDecomp<complex<double>> LUEC;LUEC=LUC;
    EXPECT_FALSE ( diff(LUEC.A,A_exact,1e-13) );

    LUDecomp<complex<double>> LUER;LUER=std::move(LUR);
    EXPECT_FALSE ( diff(LUER.A,A_exact,1e-13) );
}

TEST(Tensor_2d_common_fun, determinant)
{
    TensorHao<complex<double>,2> X(3,3);

    X={ {1.0,0.0} ,   {3.0,4.0},    {2.123,3.11},
        {3.0,-2.0},   {2.0,0.0},    {5.123,3.11},
        {2.123,-5.11},{5.123,-6.11},{3,0.0}  };

    complex<double> det_exact={123.11968700000003,3.3324580000000000};

    complex<double> det=determinant( LUconstruct_cpu(X) );
    EXPECT_COMPLEX_NEAR ( det_exact, det );

#ifdef USE_MAGMA
     det=determinant( LUconstruct_magma(X) );
     EXPECT_COMPLEX_NEAR ( det_exact, det );
#endif
}

TEST(Tensor_2d_common_fun, lognormPhaseDeterminant)
{
    TensorHao<complex<double>,2> X(3,3);
    X={ {1.0,0.0} ,   {3.0,4.0},    {2.123,3.11},
        {3.0,-2.0},   {2.0,0.0},    {5.123,3.11},
        {2.123,-5.11},{5.123,-6.11},{3,0.0}  };
    complex<double> lognorm_exact = 4.813523119460474;
    complex<double> phase_exact = {0.9996338948645466, 0.027056907397860167};
    complex<double> lognorm, phase;

    lognormPhaseDeterminant(LUconstruct_cpu(X), lognorm, phase);
    EXPECT_COMPLEX_NEAR ( lognorm_exact, lognorm);
    EXPECT_COMPLEX_NEAR ( phase_exact,phase);

#ifdef USE_MAGMA
    lognormPhaseDeterminant( LUconstruct_magma(X), lognorm, phase );
    EXPECT_COMPLEX_NEAR ( lognorm_exact, lognorm);
    EXPECT_COMPLEX_NEAR ( phase_exact,phase);
#endif
}

TEST(Tensor_2d_common_fun, logDeterminant)
{
    TensorHao<complex<double>,2> X(3,3);

    X={ {1.0,0.0} ,   {3.0,4.0},    {2.123,3.11},
        {3.0,-2.0},   {2.0,0.0},    {5.123,3.11},
        {2.123,-5.11},{5.123,-6.11},{3,0.0}  };

    X*=1.e103;
    complex<double> logdet_exact={716.3123168546207,0.027060209772387683};

    complex<double> logdet= logDeterminant(LUconstruct_cpu(X));
    EXPECT_COMPLEX_NEAR ( logdet_exact, logdet );

#ifdef USE_MAGMA
    logdet=logDeterminant( LUconstruct_magma(X) );
    EXPECT_COMPLEX_NEAR ( logdet_exact, logdet );
#endif
}

TEST(Tensor_2d_common_fun, dMultiMatrix)
{
    TensorHao<complex<double>,2> A(3,2);
    TensorHao<complex<double>,1> D(3);

    A = { {2.0,0.0} ,   {3.0,5.0},    {3.123,3.11},
          {3.0,-6.0},   {2.0,1.0},    {6.123,3.11} };

    D = { {1.2,0.0}, {2.0,0.0}, {3.0,0.0} };

    TensorHao<complex<double>,2> B= dMultiMatrix(D, A);

    TensorHao<complex<double>,2> B_exact(3,2);
    B_exact = { {2.4,0.0} ,   {6.0,10.0},    {9.369,9.33},
                {3.6,-7.2},   {4.0,2.0 },    {18.369,9.33} };

    EXPECT_FALSE ( diff(B,B_exact,1e-12) );
}

TEST(Tensor_2d_common_fun, checkSkewSymmetric)
{
    TensorHao<complex<double>,2> a(3,3);
    a = { {0.0,0.0} ,    {3.0,4.0},     {2.123,3.11},
          {-3.0,-4.0},   {0.0,0.0},     {5.123,3.11},
          {-2.123,-3.11},{-5.123, 3.11},{0,0.0}     };

    try
    {
        checkSkewSymmetric(a);
    }
    catch(runtime_error& err)
    {
        EXPECT_EQ( "ERROR!!! Matrix is not skew symmetric!", string(err.what()) );
    }
}

TEST(Tensor_2d_common_fun, pfaffian)
{
    TensorHao<complex<double>,2> A(4,4);
    A = { {0.0,0.0},  {1.0,2.0},  {1.5,0.0}, {2.3,0.0},
          {-1.0,-2.0},{0.0,0.0},  {-3.0,0.0},{1.5,0.0},
          {-1.5,0.0}, {3.0,0.0},  {0.0,0.0}, {-2.5,-5.3},
          {-2.3,0.0}, {-1.5,0.0}, {2.5,5.3}, {0.0,0.0} };
    complex<double> pf= pfaffian(A);
    complex<double> exact{-1.05,-10.3};

    EXPECT_COMPLEX_NEAR ( exact, pf, 1e-12);
}
