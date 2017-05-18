//
// Created by boruoshihao on 5/18/17.
//

#include "../include/hop2IS.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(Hop2ISTest, voidConstruction)
{
    size_t L(0);
    Hop2IS hop2IS;
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, hop2IS.logw );
    EXPECT_FALSE( hop2IS.matrix.data() );
    EXPECT_EQ( L, hop2IS.getL() );
}

TEST(Hop2ISTest, size_tConstruction)
{
    size_t L(10);
    Hop2IS hop2IS(L);
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, hop2IS.logw );
    EXPECT_TRUE( hop2IS.matrix.data() );
    EXPECT_EQ( L, hop2IS.getL() );
}

TEST(Hop2ISTest, copyConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrix(L,L);
    randomFill(matrix);
    complex<double> logw(2.0, 3.0);

    Hop2IS hop2ISBase; hop2ISBase.logw=logw; hop2ISBase.matrix = matrix;
    Hop2IS hop2IS(hop2ISBase);

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop2IS.logw );
    EXPECT_FALSE( diff( matrix, hop2IS.matrix, 1e-12 ) );
    EXPECT_EQ( L, hop2IS.getL() );
    EXPECT_FALSE( diff( matrix, hop2ISBase.matrix, 1e-12 ) );
}

TEST(Hop2ISTest, moveConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrix(L,L);
    randomFill(matrix);
    complex<double> logw(2.0, 3.0);

    Hop2IS hop2ISBase; hop2ISBase.logw=logw; hop2ISBase.matrix = matrix;
    Hop2IS hop2IS( move( hop2ISBase ) );

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop2IS.logw );
    EXPECT_FALSE( diff( matrix, hop2IS.matrix, 1e-12 ) );
    EXPECT_EQ( L, hop2IS.getL() );
    EXPECT_FALSE( hop2ISBase.matrix.data() );
}

TEST(Hop2ISTest, copyAssignment)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrix(L,L);
    randomFill(matrix);
    complex<double> logw(2.0, 3.0);

    Hop2IS hop2ISBase; hop2ISBase.logw=logw; hop2ISBase.matrix = matrix;
    Hop2IS hop2IS; hop2IS = hop2ISBase;

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop2IS.logw );
    EXPECT_FALSE( diff( matrix, hop2IS.matrix, 1e-12 ) );
    EXPECT_EQ( L, hop2IS.getL() );
    EXPECT_FALSE( diff( matrix, hop2ISBase.matrix, 1e-12 ) );
}

TEST(Hop2ISTest, moveAssignment)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrix(L,L);
    randomFill(matrix);
    complex<double> logw(2.0, 3.0);

    Hop2IS hop2ISBase; hop2ISBase.logw=logw; hop2ISBase.matrix = matrix;
    Hop2IS hop2IS; hop2IS = move( hop2ISBase );

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop2IS.logw );
    EXPECT_FALSE( diff( matrix, hop2IS.matrix, 1e-12 ) );
    EXPECT_EQ( L, hop2IS.getL() );
    EXPECT_FALSE( hop2ISBase.matrix.data() );
}
