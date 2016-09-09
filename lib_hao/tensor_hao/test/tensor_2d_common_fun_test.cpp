#include <cmath>
#include "../include/tensor_2d_common_fun.h"
#include "../include/tensor_2d_bl_cpu.h"
#include "../include/tensor_2d_bl_magma.h"
#include "../../../utilities/test_hao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(Tensor_2d_common_fun, trans)
{
    Tensor_hao<double, 2> A(2,3), B(3,2), B_exact(3,2);
    A={1.,2.,3.,4.,5.,6.};
    B_exact={1.,3.,5.,2.,4.,6.};
    B=trans(A);
    EXPECT_FALSE ( diff(B, B_exact, 1e-12) );
}

TEST(Tensor_2d_common_fun, conjtrans)
{
    Tensor_hao<complex<double>, 2> A(2,3), B(3,2), B_exact(3,2);
    A={ {1.,1.}, {2.,2.}, {3.,3.}, {4.,4.}, {5.,5.}, {6.,6.} };
    B_exact={ {1.,-1.}, {3.,-3.}, {5.,-5.}, {2.,-2.}, {4.,-4.}, {6.,-6.} };
    B=conjtrans(A);
    EXPECT_FALSE ( diff(B, B_exact, 1e-12) );
}

TEST(Tensor_2d_common_fun, Hermitian)
{
    Tensor_hao<complex<double>,2> a(3,3);
    a = { {1.0,0.0} ,   {3.0,4.0},    {2.123,3.11},
          {3.0,-4.0},   {2.0,0.0},    {5.123,3.11},
          {2.123,-3.11},{5.123,-3.11},{3,0.0}     };
    EXPECT_FALSE ( check_Hermitian(a) );
}

TEST(Tensor_2d_common_fun, LUDecomp)
{
    Tensor_hao<complex<double>,2> X(3,3);
    X = { {1.0,0.0} ,   {3.0,4.0},    {2.123,3.11},
          {3.0,-2.0},   {2.0,0.0},    {5.123,3.11},
          {2.123,-5.11},{5.123,-6.11},{3,0.0} };

    LUDecomp<complex<double>> LU=LUconstruct_cpu(X);

    Tensor_hao<complex<double>,2> A_exact=LU.A;

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
    Tensor_hao<complex<double>,2> X(3,3);

    X={ {1.0,0.0} ,   {3.0,4.0},    {2.123,3.11},
        {3.0,-2.0},   {2.0,0.0},    {5.123,3.11},
        {2.123,-5.11},{5.123,-6.11},{3,0.0}  };

    complex<double> det_exact={123.11968700000003,3.3324580000000000};

    complex<double> det=determinant( LUconstruct_cpu(X) );
    EXPECT_COMPLEXDOUBLE_EQ ( det_exact, det );

#ifdef USE_MAGMA
     det=determinant( LUconstruct_magma(X) );
     EXPECT_COMPLEXDOUBLE_EQ ( det_exact, det );
#endif
}

TEST(Tensor_2d_common_fun, lognorm_phase_determinant)
{
    Tensor_hao<complex<double>,2> X(3,3);
    X={ {1.0,0.0} ,   {3.0,4.0},    {2.123,3.11},
        {3.0,-2.0},   {2.0,0.0},    {5.123,3.11},
        {2.123,-5.11},{5.123,-6.11},{3,0.0}  };
    complex<double> lognorm_exact = 4.813523119460474;
    complex<double> phase_exact = {0.9996338948645466, 0.027056907397860167};
    complex<double> lognorm, phase;

    lognorm_phase_determinant( LUconstruct_cpu(X), lognorm, phase );
    EXPECT_COMPLEXDOUBLE_EQ ( lognorm_exact, lognorm);
    EXPECT_COMPLEXDOUBLE_EQ ( phase_exact,phase);

#ifdef USE_MAGMA
    lognorm_phase_determinant( LUconstruct_magma(X), lognorm, phase );
    EXPECT_COMPLEXDOUBLE_EQ ( lognorm_exact, lognorm);
    EXPECT_COMPLEXDOUBLE_EQ ( phase_exact,phase);
#endif
}

TEST(Tensor_2d_common_fun, log_determinant)
{
    Tensor_hao<complex<double>,2> X(3,3);

    X={ {1.0,0.0} ,   {3.0,4.0},    {2.123,3.11},
        {3.0,-2.0},   {2.0,0.0},    {5.123,3.11},
        {2.123,-5.11},{5.123,-6.11},{3,0.0}  };

    X*=1.e103;
    complex<double> logdet_exact={716.3123168546207,0.027060209772387683};

    complex<double> logdet=log_determinant( LUconstruct_cpu(X) );
    EXPECT_COMPLEXDOUBLE_EQ ( logdet_exact, logdet );

#ifdef USE_MAGMA
    logdet=log_determinant( LUconstruct_magma(X) );
    EXPECT_COMPLEXDOUBLE_EQ ( logdet_exact, logdet );
#endif
}

TEST(Tensor_2d_common_fun, D_Multi_Matrix)
{
    Tensor_hao<complex<double>,2> A(3,2);
    Tensor_hao<complex<double>,1> D(3);

    A = { {2.0,0.0} ,   {3.0,5.0},    {3.123,3.11},
          {3.0,-6.0},   {2.0,1.0},    {6.123,3.11} };

    D = { {1.2,0.0}, {2.0,0.0}, {3.0,0.0} };

    Tensor_hao<complex<double>,2> B=D_Multi_Matrix(D,A);

    Tensor_hao<complex<double>,2> B_exact(3,2);
    B_exact = { {2.4,0.0} ,   {6.0,10.0},    {9.369,9.33},
                {3.6,-7.2},   {4.0,2.0 },    {18.369,9.33} };

    EXPECT_FALSE ( diff(B,B_exact,1e-12) );
}

TEST(Tensor_2d_common_fun, check_skew_symmetric)
{
    Tensor_hao<complex<double>,2> a(3,3);
    a = { {0.0,0.0} ,    {3.0,4.0},     {2.123,3.11},
          {-3.0,-4.0},   {0.0,0.0},     {5.123,3.11},
          {-2.123,-3.11},{-5.123,-3.11},{0,0.0}     };
    EXPECT_FALSE ( check_skew_symmetric(a) );
}

TEST(Tensor_2d_common_fun, pfaffian)
{
    Tensor_hao<complex<double>,2> A(4,4);
    A = { {0.0,0.0},  {1.0,2.0},  {1.5,0.0}, {2.3,0.0},
          {-1.0,-2.0},{0.0,0.0},  {-3.0,0.0},{1.5,0.0},
          {-1.5,0.0}, {3.0,0.0},  {0.0,0.0}, {-2.5,-5.3},
          {-2.3,0.0}, {-1.5,0.0}, {2.5,5.3}, {0.0,0.0} };
    complex<double> pf=Pfaffian(A);
    complex<double> exact{-1.05,-10.3};

    EXPECT_COMPLEXDOUBLE_EQ ( exact, pf);
}