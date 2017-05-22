//
// Created by boruoshihao on 5/17/17.
//
#include "../include/hop2s.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(Hop2sTest, voidConstruction)
{
    size_t L(0);
    Hop2s hop2s;
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, hop2s.logw );
    EXPECT_FALSE( hop2s.matrixUp.data() );
    EXPECT_FALSE( hop2s.matrixDn.data() );
    EXPECT_EQ( L, hop2s.getL() );
}

TEST(Hop2sTest, size_tConstruction)
{
    size_t L(10);
    Hop2s hop2s(L);
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, hop2s.logw );
    EXPECT_TRUE( hop2s.matrixUp.data() );
    EXPECT_TRUE( hop2s.matrixDn.data() );
    EXPECT_EQ( L, hop2s.getL() );
}

TEST(Hop2sTest, copyConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrixUp(L,L), matrixDn(L,L);
    randomFill(matrixUp); randomFill(matrixDn);
    complex<double> logw(2.0, 3.0);

    Hop2s hop2sBase; hop2sBase.logw=logw; hop2sBase.matrixUp = matrixUp; hop2sBase.matrixDn = matrixDn;
    Hop2s hop2s(hop2sBase);

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop2s.logw );
    EXPECT_FALSE( diff( matrixUp, hop2s.matrixUp, 1e-12 ) );
    EXPECT_FALSE( diff( matrixDn, hop2s.matrixDn, 1e-12 ) );
    EXPECT_EQ( L, hop2s.getL() );
    EXPECT_FALSE( diff( matrixUp, hop2sBase.matrixUp, 1e-12 ) );
    EXPECT_FALSE( diff( matrixDn, hop2sBase.matrixDn, 1e-12 ) );
}

TEST(Hop2sTest, moveConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrixUp(L,L), matrixDn(L,L);
    randomFill(matrixUp); randomFill(matrixDn);
    complex<double> logw(2.0, 3.0);

    Hop2s hop2sBase; hop2sBase.logw=logw; hop2sBase.matrixUp = matrixUp; hop2sBase.matrixDn = matrixDn;
    Hop2s hop2s( move(hop2sBase) );

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop2s.logw );
    EXPECT_FALSE( diff( matrixUp, hop2s.matrixUp, 1e-12 ) );
    EXPECT_FALSE( diff( matrixDn, hop2s.matrixDn, 1e-12 ) );
    EXPECT_EQ( L, hop2s.getL() );
    EXPECT_FALSE( hop2sBase.matrixUp.data() );
    EXPECT_FALSE( hop2sBase.matrixDn.data() );
}

TEST(Hop2sTest, copyAssigment)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrixUp(L,L), matrixDn(L,L);
    randomFill(matrixUp); randomFill(matrixDn);
    complex<double> logw(2.0, 3.0);

    Hop2s hop2sBase; hop2sBase.logw=logw; hop2sBase.matrixUp = matrixUp; hop2sBase.matrixDn = matrixDn;
    Hop2s hop2s; hop2s=hop2sBase;

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop2s.logw );
    EXPECT_FALSE( diff( matrixUp, hop2s.matrixUp, 1e-12 ) );
    EXPECT_FALSE( diff( matrixDn, hop2s.matrixDn, 1e-12 ) );
    EXPECT_EQ( L, hop2s.getL() );
    EXPECT_FALSE( diff( matrixUp, hop2sBase.matrixUp, 1e-12 ) );
    EXPECT_FALSE( diff( matrixDn, hop2sBase.matrixDn, 1e-12 ) );
}

TEST(Hop2sTest, moveAssigment)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrixUp(L,L), matrixDn(L,L);
    randomFill(matrixUp); randomFill(matrixDn);
    complex<double> logw(2.0, 3.0);

    Hop2s hop2sBase; hop2sBase.logw=logw; hop2sBase.matrixUp = matrixUp; hop2sBase.matrixDn = matrixDn;
    Hop2s hop2s; hop2s=move(hop2sBase);

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop2s.logw );
    EXPECT_FALSE( diff( matrixUp, hop2s.matrixUp, 1e-12 ) );
    EXPECT_FALSE( diff( matrixDn, hop2s.matrixDn, 1e-12 ) );
    EXPECT_EQ( L, hop2s.getL() );
    EXPECT_FALSE( hop2sBase.matrixUp.data() );
    EXPECT_FALSE( hop2sBase.matrixDn.data() );
}
