//
// Created by boruoshihao on 12/28/16.
//
#include "../include/hoppingOperator.h"
#include "../../../../common/testHao/gtest_custom.h"


using namespace std;
using namespace tensor_hao;

TEST(hoppingOperatorTest, voidConstruction)
{
    HoppingOperator hop;
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, hop.getLogw() );
    EXPECT_FALSE( hop.getOp().data() );
    EXPECT_EQ( static_cast<size_t>(0), hop.getL() );
}

TEST(hoppingOperatorTest, LConstruction)
{
    size_t L(10);
    HoppingOperator hop(L);
    EXPECT_COMPLEXDOUBLE_EQ( 0.0, hop.getLogw() );
    EXPECT_TRUE( hop.getOp().data() );
    EXPECT_EQ( L, hop.getL() );
}

TEST(hoppingOperatorTest, copyConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> op(L,L);
    randomFill(op);
    complex<double> logw(2.0, 3.0);

    HoppingOperator hopBase(L);
    hopBase.opRef() = op;
    hopBase.logwRef() = logw;

    HoppingOperator hop(hopBase);
    EXPECT_COMPLEXDOUBLE_EQ( logw, hop.getLogw() );
    EXPECT_FALSE( diff( op, hop.getOp(), 1e-12 ) );
    EXPECT_EQ( L, hop.getL() );
    EXPECT_FALSE( diff( op, hopBase.getOp(), 1e-12 ) );
}

TEST(hoppingOperatorTest, moveConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> op(L,L);
    randomFill(op);
    complex<double> logw(2.0, 3.0);

    HoppingOperator hopBase(L);
    hopBase.opRef() = op;
    hopBase.logwRef() = logw;

    HoppingOperator hop( move( hopBase ) );
    EXPECT_COMPLEXDOUBLE_EQ( logw, hop.getLogw() );
    EXPECT_FALSE( diff( op, hop.getOp(), 1e-12 ) );
    EXPECT_EQ( L, hop.getL() );
    EXPECT_FALSE( hopBase.getOp().data() );
}

TEST(hoppingOperatorTest, copyAssignment)
{
    size_t L(10);
    TensorHao<complex<double>,2> op(L,L);
    randomFill(op);
    complex<double> logw(2.0, 3.0);

    HoppingOperator hopBase(L);
    hopBase.opRef() = op;
    hopBase.logwRef() = logw;

    HoppingOperator hop; hop=hopBase;
    EXPECT_COMPLEXDOUBLE_EQ( logw, hop.getLogw() );
    EXPECT_FALSE( diff( op, hop.getOp(), 1e-12 ) );
    EXPECT_EQ( L, hop.getL() );
    EXPECT_FALSE( diff( op, hopBase.getOp(), 1e-12 ) );
}

TEST(hoppingOperatorTest, moveAssignment)
{
    size_t L(10);
    TensorHao<complex<double>,2> op(L,L);
    randomFill(op);
    complex<double> logw(2.0, 3.0);

    HoppingOperator hopBase(L);
    hopBase.opRef() = op;
    hopBase.logwRef() = logw;

    HoppingOperator hop; hop = move( hopBase );
    EXPECT_COMPLEXDOUBLE_EQ( logw, hop.getLogw() );
    EXPECT_FALSE( diff( op, hop.getOp(), 1e-12 ) );
    EXPECT_EQ( L, hop.getL() );
    EXPECT_FALSE( hopBase.getOp().data() );
}