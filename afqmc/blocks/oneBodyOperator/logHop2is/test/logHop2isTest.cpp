//
// Created by boruoshihao on 5/18/17.
//

#include "../include/logHop2is.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(LogHop2isTest, voidConstruction)
{
    size_t L(0);
    LogHop2is logHop2is;
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, logHop2is.logw );
    EXPECT_FALSE( logHop2is.matrix.data() );
    EXPECT_EQ( L, logHop2is.getL() );
}

TEST(LogHop2isTest, size_tConstruction)
{
    size_t L(10);
    LogHop2is logHop2is(L);
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, logHop2is.logw );
    EXPECT_TRUE( logHop2is.matrix.data() );
    EXPECT_EQ( L, logHop2is.getL() );
}

TEST(LogHop2isTest, copyConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrix(L,L);
    randomFill(matrix);
    complex<double> logw(2.0, 3.0);

    LogHop2is logHop2isBase; logHop2isBase.logw=logw; logHop2isBase.matrix = matrix;
    LogHop2is logHop2is(logHop2isBase);

    EXPECT_COMPLEXDOUBLE_EQ( logw, logHop2is.logw );
    EXPECT_FALSE( diff( matrix, logHop2is.matrix, 1e-12 ) );
    EXPECT_EQ( L, logHop2is.getL() );
    EXPECT_FALSE( diff( matrix, logHop2isBase.matrix, 1e-12 ) );
}

TEST(LogHop2isTest, moveConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrix(L,L);
    randomFill(matrix);
    complex<double> logw(2.0, 3.0);

    LogHop2is logHop2isBase; logHop2isBase.logw=logw; logHop2isBase.matrix = matrix;
    LogHop2is logHop2is( move( logHop2isBase ) );

    EXPECT_COMPLEXDOUBLE_EQ( logw, logHop2is.logw );
    EXPECT_FALSE( diff( matrix, logHop2is.matrix, 1e-12 ) );
    EXPECT_EQ( L, logHop2is.getL() );
    EXPECT_FALSE( logHop2isBase.matrix.data() );
}

TEST(LogHop2isTest, copyAssignment)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrix(L,L);
    randomFill(matrix);
    complex<double> logw(2.0, 3.0);

    LogHop2is logHop2isBase; logHop2isBase.logw=logw; logHop2isBase.matrix = matrix;
    LogHop2is logHop2is; logHop2is = logHop2isBase;

    EXPECT_COMPLEXDOUBLE_EQ( logw, logHop2is.logw );
    EXPECT_FALSE( diff( matrix, logHop2is.matrix, 1e-12 ) );
    EXPECT_EQ( L, logHop2is.getL() );
    EXPECT_FALSE( diff( matrix, logHop2isBase.matrix, 1e-12 ) );
}

TEST(LogHop2isTest, moveAssignment)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrix(L,L);
    randomFill(matrix);
    complex<double> logw(2.0, 3.0);

    LogHop2is logHop2isBase; logHop2isBase.logw=logw; logHop2isBase.matrix = matrix;
    LogHop2is logHop2is; logHop2is = move( logHop2isBase );

    EXPECT_COMPLEXDOUBLE_EQ( logw, logHop2is.logw );
    EXPECT_FALSE( diff( matrix, logHop2is.matrix, 1e-12 ) );
    EXPECT_EQ( L, logHop2is.getL() );
    EXPECT_FALSE( logHop2isBase.matrix.data() );
}
