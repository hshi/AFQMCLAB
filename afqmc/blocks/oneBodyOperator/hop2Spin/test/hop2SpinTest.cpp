//
// Created by boruoshihao on 5/17/17.
//
#include "../include/hop2Spin.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(Hop2SpinTest, voidConstruction)
{
    size_t L(0);
    Hop2Spin hop2Spin;
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, hop2Spin.logw );
    EXPECT_FALSE( hop2Spin.matrixUp.data() );
    EXPECT_FALSE( hop2Spin.matrixDn.data() );
    EXPECT_EQ( L, hop2Spin.getL() );
}

TEST(Hop2SpinTest, size_tConstruction)
{
    size_t L(10);
    Hop2Spin hop2Spin(L);
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, hop2Spin.logw );
    EXPECT_TRUE( hop2Spin.matrixUp.data() );
    EXPECT_TRUE( hop2Spin.matrixDn.data() );
    EXPECT_EQ( L, hop2Spin.getL() );
}

TEST(Hop2SpinTest, copyConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrixUp(L,L), matrixDn(L,L);
    randomFill(matrixUp); randomFill(matrixDn);
    complex<double> logw(2.0, 3.0);

    Hop2Spin hop2SpinBase; hop2SpinBase.logw=logw; hop2SpinBase.matrixUp = matrixUp; hop2SpinBase.matrixDn = matrixDn;
    Hop2Spin hop2Spin(hop2SpinBase);

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop2Spin.logw );
    EXPECT_FALSE( diff( matrixUp, hop2Spin.matrixUp, 1e-12 ) );
    EXPECT_FALSE( diff( matrixDn, hop2Spin.matrixDn, 1e-12 ) );
    EXPECT_EQ( L, hop2Spin.getL() );
    EXPECT_FALSE( diff( matrixUp, hop2SpinBase.matrixUp, 1e-12 ) );
    EXPECT_FALSE( diff( matrixDn, hop2SpinBase.matrixDn, 1e-12 ) );
}

TEST(Hop2SpinTest, moveConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrixUp(L,L), matrixDn(L,L);
    randomFill(matrixUp); randomFill(matrixDn);
    complex<double> logw(2.0, 3.0);

    Hop2Spin hop2SpinBase; hop2SpinBase.logw=logw; hop2SpinBase.matrixUp = matrixUp; hop2SpinBase.matrixDn = matrixDn;
    Hop2Spin hop2Spin( move(hop2SpinBase) );

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop2Spin.logw );
    EXPECT_FALSE( diff( matrixUp, hop2Spin.matrixUp, 1e-12 ) );
    EXPECT_FALSE( diff( matrixDn, hop2Spin.matrixDn, 1e-12 ) );
    EXPECT_EQ( L, hop2Spin.getL() );
    EXPECT_FALSE( hop2SpinBase.matrixUp.data() );
    EXPECT_FALSE( hop2SpinBase.matrixDn.data() );
}

TEST(Hop2SpinTest, copyAssigment)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrixUp(L,L), matrixDn(L,L);
    randomFill(matrixUp); randomFill(matrixDn);
    complex<double> logw(2.0, 3.0);

    Hop2Spin hop2SpinBase; hop2SpinBase.logw=logw; hop2SpinBase.matrixUp = matrixUp; hop2SpinBase.matrixDn = matrixDn;
    Hop2Spin hop2Spin; hop2Spin=hop2SpinBase;

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop2Spin.logw );
    EXPECT_FALSE( diff( matrixUp, hop2Spin.matrixUp, 1e-12 ) );
    EXPECT_FALSE( diff( matrixDn, hop2Spin.matrixDn, 1e-12 ) );
    EXPECT_EQ( L, hop2Spin.getL() );
    EXPECT_FALSE( diff( matrixUp, hop2SpinBase.matrixUp, 1e-12 ) );
    EXPECT_FALSE( diff( matrixDn, hop2SpinBase.matrixDn, 1e-12 ) );
}

TEST(Hop2SpinTest, moveAssigment)
{
    size_t L(10);
    TensorHao<complex<double>,2> matrixUp(L,L), matrixDn(L,L);
    randomFill(matrixUp); randomFill(matrixDn);
    complex<double> logw(2.0, 3.0);

    Hop2Spin hop2SpinBase; hop2SpinBase.logw=logw; hop2SpinBase.matrixUp = matrixUp; hop2SpinBase.matrixDn = matrixDn;
    Hop2Spin hop2Spin; hop2Spin=move(hop2SpinBase);

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop2Spin.logw );
    EXPECT_FALSE( diff( matrixUp, hop2Spin.matrixUp, 1e-12 ) );
    EXPECT_FALSE( diff( matrixDn, hop2Spin.matrixDn, 1e-12 ) );
    EXPECT_EQ( L, hop2Spin.getL() );
    EXPECT_FALSE( hop2SpinBase.matrixUp.data() );
    EXPECT_FALSE( hop2SpinBase.matrixDn.data() );
}