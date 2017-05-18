//
// Created by boruoshihao on 5/17/17.
//
#include "../include/hop2S.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(Hop2STest, voidConstruction)
{
    size_t L(0);
    Hop2S hop2S;
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, hop2S.logw );
    EXPECT_FALSE( hop2S.matrixUp.data() );
    EXPECT_FALSE( hop2S.matrixDn.data() );
    EXPECT_EQ( L, hop2S.getL() );
}

TEST(Hop2STest, size_tConstruction)
{
    size_t L(10);
    Hop2S hop2S(L);
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, hop2S.logw );
    EXPECT_TRUE( hop2S.matrixUp.data() );
    EXPECT_TRUE( hop2S.matrixDn.data() );
    EXPECT_EQ( L, hop2S.getL() );
}

TEST(Hop2STest, copyConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrixUp(L,L), matrixDn(L,L);
    randomFill(matrixUp); randomFill(matrixDn);
    complex<double> logw(2.0, 3.0);

    Hop2S hop2SBase; hop2SBase.logw=logw; hop2SBase.matrixUp = matrixUp; hop2SBase.matrixDn = matrixDn;
    Hop2S hop2S(hop2SBase);

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop2S.logw );
    EXPECT_FALSE( diff( matrixUp, hop2S.matrixUp, 1e-12 ) );
    EXPECT_FALSE( diff( matrixDn, hop2S.matrixDn, 1e-12 ) );
    EXPECT_EQ( L, hop2S.getL() );
    EXPECT_FALSE( diff( matrixUp, hop2SBase.matrixUp, 1e-12 ) );
    EXPECT_FALSE( diff( matrixDn, hop2SBase.matrixDn, 1e-12 ) );
}

TEST(Hop2STest, moveConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrixUp(L,L), matrixDn(L,L);
    randomFill(matrixUp); randomFill(matrixDn);
    complex<double> logw(2.0, 3.0);

    Hop2S hop2SBase; hop2SBase.logw=logw; hop2SBase.matrixUp = matrixUp; hop2SBase.matrixDn = matrixDn;
    Hop2S hop2S( move(hop2SBase) );

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop2S.logw );
    EXPECT_FALSE( diff( matrixUp, hop2S.matrixUp, 1e-12 ) );
    EXPECT_FALSE( diff( matrixDn, hop2S.matrixDn, 1e-12 ) );
    EXPECT_EQ( L, hop2S.getL() );
    EXPECT_FALSE( hop2SBase.matrixUp.data() );
    EXPECT_FALSE( hop2SBase.matrixDn.data() );
}

TEST(Hop2STest, copyAssigment)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrixUp(L,L), matrixDn(L,L);
    randomFill(matrixUp); randomFill(matrixDn);
    complex<double> logw(2.0, 3.0);

    Hop2S hop2SBase; hop2SBase.logw=logw; hop2SBase.matrixUp = matrixUp; hop2SBase.matrixDn = matrixDn;
    Hop2S hop2S; hop2S=hop2SBase;

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop2S.logw );
    EXPECT_FALSE( diff( matrixUp, hop2S.matrixUp, 1e-12 ) );
    EXPECT_FALSE( diff( matrixDn, hop2S.matrixDn, 1e-12 ) );
    EXPECT_EQ( L, hop2S.getL() );
    EXPECT_FALSE( diff( matrixUp, hop2SBase.matrixUp, 1e-12 ) );
    EXPECT_FALSE( diff( matrixDn, hop2SBase.matrixDn, 1e-12 ) );
}

TEST(Hop2STest, moveAssigment)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrixUp(L,L), matrixDn(L,L);
    randomFill(matrixUp); randomFill(matrixDn);
    complex<double> logw(2.0, 3.0);

    Hop2S hop2SBase; hop2SBase.logw=logw; hop2SBase.matrixUp = matrixUp; hop2SBase.matrixDn = matrixDn;
    Hop2S hop2S; hop2S=move(hop2SBase);

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop2S.logw );
    EXPECT_FALSE( diff( matrixUp, hop2S.matrixUp, 1e-12 ) );
    EXPECT_FALSE( diff( matrixDn, hop2S.matrixDn, 1e-12 ) );
    EXPECT_EQ( L, hop2S.getL() );
    EXPECT_FALSE( hop2SBase.matrixUp.data() );
    EXPECT_FALSE( hop2SBase.matrixDn.data() );
}
