//
// Created by boruoshihao on 5/18/17.
//

#include "../include/logHop2IS.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(LogHop2ISTest, voidConstruction)
{
    size_t L(0);
    LogHop2IS logHop2IS;
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, logHop2IS.logw );
    EXPECT_FALSE( logHop2IS.matrix.data() );
    EXPECT_EQ( L, logHop2IS.getL() );
}

TEST(LogHop2ISTest, size_tConstruction)
{
    size_t L(10);
    LogHop2IS logHop2IS(L);
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, logHop2IS.logw );
    EXPECT_TRUE( logHop2IS.matrix.data() );
    EXPECT_EQ( L, logHop2IS.getL() );
}

TEST(LogHop2ISTest, copyConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrix(L,L);
    randomFill(matrix);
    complex<double> logw(2.0, 3.0);

    LogHop2IS logHop2ISBase; logHop2ISBase.logw=logw; logHop2ISBase.matrix = matrix;
    LogHop2IS logHop2IS(logHop2ISBase);

    EXPECT_COMPLEXDOUBLE_EQ( logw, logHop2IS.logw );
    EXPECT_FALSE( diff( matrix, logHop2IS.matrix, 1e-12 ) );
    EXPECT_EQ( L, logHop2IS.getL() );
    EXPECT_FALSE( diff( matrix, logHop2ISBase.matrix, 1e-12 ) );
}

TEST(LogHop2ISTest, moveConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrix(L,L);
    randomFill(matrix);
    complex<double> logw(2.0, 3.0);

    LogHop2IS logHop2ISBase; logHop2ISBase.logw=logw; logHop2ISBase.matrix = matrix;
    LogHop2IS logHop2IS( move( logHop2ISBase ) );

    EXPECT_COMPLEXDOUBLE_EQ( logw, logHop2IS.logw );
    EXPECT_FALSE( diff( matrix, logHop2IS.matrix, 1e-12 ) );
    EXPECT_EQ( L, logHop2IS.getL() );
    EXPECT_FALSE( logHop2ISBase.matrix.data() );
}

TEST(LogHop2ISTest, copyAssignment)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrix(L,L);
    randomFill(matrix);
    complex<double> logw(2.0, 3.0);

    LogHop2IS logHop2ISBase; logHop2ISBase.logw=logw; logHop2ISBase.matrix = matrix;
    LogHop2IS logHop2IS; logHop2IS = logHop2ISBase;

    EXPECT_COMPLEXDOUBLE_EQ( logw, logHop2IS.logw );
    EXPECT_FALSE( diff( matrix, logHop2IS.matrix, 1e-12 ) );
    EXPECT_EQ( L, logHop2IS.getL() );
    EXPECT_FALSE( diff( matrix, logHop2ISBase.matrix, 1e-12 ) );
}

TEST(LogHop2ISTest, moveAssignment)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrix(L,L);
    randomFill(matrix);
    complex<double> logw(2.0, 3.0);

    LogHop2IS logHop2ISBase; logHop2ISBase.logw=logw; logHop2ISBase.matrix = matrix;
    LogHop2IS logHop2IS; logHop2IS = move( logHop2ISBase );

    EXPECT_COMPLEXDOUBLE_EQ( logw, logHop2IS.logw );
    EXPECT_FALSE( diff( matrix, logHop2IS.matrix, 1e-12 ) );
    EXPECT_EQ( L, logHop2IS.getL() );
    EXPECT_FALSE( logHop2ISBase.matrix.data() );
}