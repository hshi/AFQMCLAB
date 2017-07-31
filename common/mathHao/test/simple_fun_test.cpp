#include <random>
#include "../include/simple_fun.h"
#include "../../testHao/gtest_custom.h"

using namespace std;

TEST (simple_fun, solveCoshxEqExpy)
{
    vector<double> v={-5.0,-3.3,-1.2,0.0,1.1,2.0,3.0,4.0};
    complex<double> gamma;
    for (auto i: v)
    {
        gamma= solveCoshxEqExpy(i);

        EXPECT_NEAR ( cosh(gamma).real(), exp(i), 1E-10 );
        EXPECT_NEAR ( cosh(gamma).imag(), 0.0 , 1E-10 );
    }
}


TEST (simple_fun, solveCosxEqExpy)
{
    vector<double> v={-5.0,-3.3,-1.2,0.0,1.1,2.0,3.0,4.0};
    complex<double> gamma;
    for (auto i: v)
    {
        gamma= solveCosxEqExpy(i);
        EXPECT_NEAR ( cos(gamma).real(), exp(i), 1E-10 );
        EXPECT_NEAR ( cos(gamma).imag(), 0.0 , 1E-10 );
    }
}

TEST (simple_fun, exp2by2Matrix)
{
    double a, b, a_exact, b_exact;
    complex<double> c, c_exact;

    a =  1.2; b = -2.0; c = complex<double>( 3.0, -2.0 );
    exp2by2Matrix(a, b, c);
    a_exact = 24.33957375963294;
    b_exact = 10.299809224500716;
    c_exact = complex<double>(13.162279251686476, -8.774852834457649);

    EXPECT_NEAR ( a_exact, a, 1e-12 );
    EXPECT_NEAR ( b_exact, b, 1e-12 );
    EXPECT_COMPLEX_NEAR ( c_exact, c, 1e-12 );

    a = 0.0; b = 0.0; c = complex<double> (3.0, 2.0);
    exp2by2Matrix(a, b, c);
    a_exact = 18.414569374170224;
    b_exact = 18.414569374170224;
    c_exact = complex<double>( 15.299239013566734, 10.199492675711154 );
    EXPECT_DOUBLE_EQ ( a_exact, a );
    EXPECT_DOUBLE_EQ ( b_exact, b );
    EXPECT_COMPLEX_NEAR ( c_exact, c );

    a = 1.0; b = 2.0; c = 0.0;
    exp2by2Matrix(a, b, c);
    a_exact = exp(1.0); b_exact = exp(2.0); c_exact = 0.0;
    EXPECT_DOUBLE_EQ ( a_exact, a );
    EXPECT_DOUBLE_EQ ( b_exact, b );
    EXPECT_COMPLEX_NEAR ( c_exact, c );
}


TEST (simple_fun, eigen2by2Matrix)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-2.0,2.0);

    double a, b; complex<double> c;
    double eig[2]; complex<double> vec[4];

    for(int i=0; i<20; i++)
    {
        a = distribution(generator);
        b = distribution(generator);
        c = complex<double>( distribution(generator), distribution(generator) );

        eigen2by2Matrix(a, b, c, eig, vec);

        EXPECT_COMPLEX_NEAR ( a*vec[0]+conj(c)*vec[1], eig[0]*vec[0], 1e-12 );
        EXPECT_COMPLEX_NEAR ( c*vec[0]+b*vec[1], eig[0]*vec[1], 1e-12 );
        EXPECT_COMPLEX_NEAR ( a*vec[2]+conj(c)*vec[3], eig[1]*vec[2], 1e-12 );
        EXPECT_COMPLEX_NEAR ( c*vec[2]+b*vec[3], eig[1]*vec[3], 1e-12 );
    }

    for(int i=0; i<20; i++)
    {
        a = distribution(generator);
        b = a;
        c = complex<double>( distribution(generator), distribution(generator) );

        eigen2by2Matrix(a, b, c, eig, vec);

        EXPECT_COMPLEX_NEAR ( a*vec[0]+conj(c)*vec[1], eig[0]*vec[0] );
        EXPECT_COMPLEX_NEAR ( c*vec[0]+b*vec[1], eig[0]*vec[1] );
        EXPECT_COMPLEX_NEAR ( a*vec[2]+conj(c)*vec[3], eig[1]*vec[2] );
        EXPECT_COMPLEX_NEAR ( c*vec[2]+b*vec[3], eig[1]*vec[3] );
    }

    for(int i=0; i<20; i++)
    {
        a = distribution(generator);
        b = distribution(generator);
        c = 0.0;

        eigen2by2Matrix(a, b, c, eig, vec);

        EXPECT_COMPLEX_NEAR ( a*vec[0]+conj(c)*vec[1], eig[0]*vec[0] );
        EXPECT_COMPLEX_NEAR ( c*vec[0]+b*vec[1], eig[0]*vec[1] );
        EXPECT_COMPLEX_NEAR ( a*vec[2]+conj(c)*vec[3], eig[1]*vec[2] );
        EXPECT_COMPLEX_NEAR ( c*vec[2]+b*vec[3], eig[1]*vec[3] );
    }
}

TEST(simple_fun, binomialCoeff)
{
    EXPECT_EQ( static_cast<size_t>(1),  binomialCoeff(5, 0) );
    EXPECT_EQ( static_cast<size_t>(5),  binomialCoeff(5, 1) );
    EXPECT_EQ( static_cast<size_t>(10), binomialCoeff(5, 2) );
    EXPECT_EQ( static_cast<size_t>(10), binomialCoeff(5, 3) );
    EXPECT_EQ( static_cast<size_t>(5),  binomialCoeff(5, 4) );
    EXPECT_EQ( static_cast<size_t>(1),  binomialCoeff(5, 5) );
    EXPECT_EQ( static_cast<size_t>(601080390), binomialCoeff(32, 16) );
}
