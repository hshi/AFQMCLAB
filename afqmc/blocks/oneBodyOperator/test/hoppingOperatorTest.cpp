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

TEST(hoppingOperatorTest, copyOpConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> op(L,L);
    randomFill(op);
    complex<double> logw(2.0, 3.0);

    HoppingOperator hop(logw, op);

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop.getLogw() );
    EXPECT_FALSE( diff( op, hop.getOp(), 1e-12 ) );
    EXPECT_EQ( L, hop.getL() );
}

TEST(hoppingOperatorTest, moveOpConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> opBase(L,L), op;
    randomFill(opBase); op = opBase;
    complex<double> logw(2.0, 3.0);

    HoppingOperator hop(logw, move(op) );

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop.getLogw() );
    EXPECT_FALSE( diff( opBase, hop.getOp(), 1e-12 ) );
    EXPECT_EQ( L, hop.getL() );
    EXPECT_FALSE( op.data() );
}

TEST(hoppingOperatorTest, copyConstruction)
{
    size_t L(10);
    TensorHao<complex<double>,2> op(L,L);
    randomFill(op);
    complex<double> logw(2.0, 3.0);

    HoppingOperator hopBase(logw, op);
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

    HoppingOperator hopBase(logw, op);
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

    HoppingOperator hopBase(logw, op);
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

    HoppingOperator hopBase(logw, op);
    HoppingOperator hop; hop = move( hopBase );

    EXPECT_COMPLEXDOUBLE_EQ( logw, hop.getLogw() );
    EXPECT_FALSE( diff( op, hop.getOp(), 1e-12 ) );
    EXPECT_EQ( L, hop.getL() );
    EXPECT_FALSE( hopBase.getOp().data() );
}