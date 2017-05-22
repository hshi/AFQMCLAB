//
// Created by boruoshihao on 5/18/17.
//

#include "../include/hop2is.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(Hop2isTest, voidConstruction)
{
    size_t L(0);
    Hop2is hop2is;
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, hop2is.logw );
    EXPECT_FALSE( hop2is.matrix.data() );
    EXPECT_EQ( L, hop2is.getL() );
}

TEST(Hop2isTest, size_tConstruction)
{
    size_t L(10);
    Hop2is hop2is(L);
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, hop2is.logw );
    EXPECT_TRUE( hop2is.matrix.data() );
    EXPECT_EQ( L, hop2is.getL() );
}

TEST(Hop2isTest, copyConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrix(L,L);
    randomFill(matrix);
    complex<double> logw(2.0, 3.0);

    Hop2is hop2isBase; hop2isBase.logw=logw; hop2isBase.matrix = matrix;
    Hop2is hop2is(hop2isBase);

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop2is.logw );
    EXPECT_FALSE( diff( matrix, hop2is.matrix, 1e-12 ) );
    EXPECT_EQ( L, hop2is.getL() );
    EXPECT_FALSE( diff( matrix, hop2isBase.matrix, 1e-12 ) );
}

TEST(Hop2isTest, moveConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrix(L,L);
    randomFill(matrix);
    complex<double> logw(2.0, 3.0);

    Hop2is hop2isBase; hop2isBase.logw=logw; hop2isBase.matrix = matrix;
    Hop2is hop2is( move( hop2isBase ) );

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop2is.logw );
    EXPECT_FALSE( diff( matrix, hop2is.matrix, 1e-12 ) );
    EXPECT_EQ( L, hop2is.getL() );
    EXPECT_FALSE( hop2isBase.matrix.data() );
}

TEST(Hop2isTest, copyAssignment)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrix(L,L);
    randomFill(matrix);
    complex<double> logw(2.0, 3.0);

    Hop2is hop2isBase; hop2isBase.logw=logw; hop2isBase.matrix = matrix;
    Hop2is hop2is; hop2is = hop2isBase;

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop2is.logw );
    EXPECT_FALSE( diff( matrix, hop2is.matrix, 1e-12 ) );
    EXPECT_EQ( L, hop2is.getL() );
    EXPECT_FALSE( diff( matrix, hop2isBase.matrix, 1e-12 ) );
}

TEST(Hop2isTest, moveAssignment)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrix(L,L);
    randomFill(matrix);
    complex<double> logw(2.0, 3.0);

    Hop2is hop2isBase; hop2isBase.logw=logw; hop2isBase.matrix = matrix;
    Hop2is hop2is; hop2is = move( hop2isBase );

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop2is.logw );
    EXPECT_FALSE( diff( matrix, hop2is.matrix, 1e-12 ) );
    EXPECT_EQ( L, hop2is.getL() );
    EXPECT_FALSE( hop2isBase.matrix.data() );
}
