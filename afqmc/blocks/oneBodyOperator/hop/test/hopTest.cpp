//
// Created by boruoshihao on 12/28/16.
//
#include "../include/hop.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(HopTest, voidConstruction)
{
    size_t L(0);
    Hop hop;
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, hop.logw );
    EXPECT_FALSE( hop.matrix.data() );
    EXPECT_EQ( L, hop.getL() );
}

TEST(HopTest, size_tConstruction)
{
    size_t L(10);
    Hop hop(L);
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, hop.logw );
    EXPECT_TRUE( hop.matrix.data() );
    EXPECT_EQ( L, hop.getL() );
}

TEST(HopTest, copyConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrix(L,L);
    randomFill(matrix);
    complex<double> logw(2.0, 3.0);

    Hop hopBase; hopBase.logw=logw; hopBase.matrix = matrix;
    Hop hop(hopBase);

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop.logw );
    EXPECT_FALSE( diff( matrix, hop.matrix, 1e-12 ) );
    EXPECT_EQ( L, hop.getL() );
    EXPECT_FALSE( diff( matrix, hopBase.matrix, 1e-12 ) );
}

TEST(HopTest, moveConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrix(L,L);
    randomFill(matrix);
    complex<double> logw(2.0, 3.0);

    Hop hopBase; hopBase.logw=logw; hopBase.matrix = matrix;
    Hop hop( move( hopBase ) );

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop.logw );
    EXPECT_FALSE( diff( matrix, hop.matrix, 1e-12 ) );
    EXPECT_EQ( L, hop.getL() );
    EXPECT_FALSE( hopBase.matrix.data() );
}

TEST(HopTest, copyAssignment)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrix(L,L);
    randomFill(matrix);
    complex<double> logw(2.0, 3.0);

    Hop hopBase; hopBase.logw=logw; hopBase.matrix = matrix;
    Hop hop; hop = hopBase;

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop.logw );
    EXPECT_FALSE( diff( matrix, hop.matrix, 1e-12 ) );
    EXPECT_EQ( L, hop.getL() );
    EXPECT_FALSE( diff( matrix, hopBase.matrix, 1e-12 ) );
}

TEST(HopTest, moveAssignment)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrix(L,L);
    randomFill(matrix);
    complex<double> logw(2.0, 3.0);

    Hop hopBase; hopBase.logw=logw; hopBase.matrix = matrix;
    Hop hop; hop = move( hopBase );

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop.logw );
    EXPECT_FALSE( diff( matrix, hop.matrix, 1e-12 ) );
    EXPECT_EQ( L, hop.getL() );
    EXPECT_FALSE( hopBase.matrix.data() );
}