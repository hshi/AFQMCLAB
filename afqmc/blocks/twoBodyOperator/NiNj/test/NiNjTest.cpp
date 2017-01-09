//
// Created by boruoshihao on 12/30/16.
//

#include "../include/NiNj.h"
#include "../../../../../common/testHao/gtest_custom.h"
#include "../../../../../common/mathHao/include/simple_fun.h"

using namespace std;
using namespace tensor_hao;

TEST(DensityDensityOperatorTest, voidConstruction)
{
    NiNj dd;
    EXPECT_EQ( static_cast<size_t>(0), dd.getL() );
    EXPECT_EQ( static_cast<size_t>(0), dd.getOp().size() );
    EXPECT_EQ( static_cast<size_t>(0), dd.getGamma().size() );
}

TEST(DensityDensityOperatorTest, densityChargeConstruction)
{
    size_t L(10);
    string decompType="densityCharge";
    TensorHao<OneNiNj, 1> op(5);
    for(size_t k = 0; k < op.size(); ++k)
    {
        op(k).i = k;
        op(k).j = k+1;
        op(k).V = 2.12*k;
    }
    NiNj dd(L, decompType, op);
    EXPECT_EQ( L, dd.getL() );
    EXPECT_EQ( decompType, dd.getDecompType() );
    EXPECT_EQ( op.size(), dd.getOp().size() );
    EXPECT_EQ( op.size(), dd.getGamma().size() );

    for(size_t k = 0; k < op.size(); ++k)
    {
        EXPECT_COMPLEXDOUBLE_EQ( solveCoshxEqExpy( op(k).V/2.0 ),  ( dd.getGamma() )(k) );
    }
}

TEST(DensityDensityOperatorTest, densitySpinConstruction)
{
    size_t L(10);
    string decompType="densitySpin";
    TensorHao<OneNiNj, 1> op(5);
    for(size_t k = 0; k < op.size(); ++k)
    {
        op(k).i = k;
        op(k).j = k+1;
        op(k).V = 2.12*k;
    }
    NiNj dd(L, decompType, op);
    EXPECT_EQ( L, dd.getL() );
    EXPECT_EQ( decompType, dd.getDecompType() );
    EXPECT_EQ( op.size(), dd.getOp().size() );
    EXPECT_EQ( op.size(), dd.getGamma().size() );

    for(size_t k = 0; k < op.size(); ++k)
    {
        EXPECT_COMPLEXDOUBLE_EQ( solveCoshxEqExpy( -op(k).V/2.0 ),  ( dd.getGamma() )(k) );
    }
}

TEST(DensityDensityOperatorTest, hopChargeConstruction)
{
    size_t L(10);
    string decompType="hopCharge";
    TensorHao<OneNiNj, 1> op(5);
    for(size_t k = 0; k < op.size(); ++k)
    {
        op(k).i = k;
        op(k).j = k+1;
        op(k).V = 2.12*k;
    }
    NiNj dd(L, decompType, op);
    EXPECT_EQ( L, dd.getL() );
    EXPECT_EQ( decompType, dd.getDecompType() );
    EXPECT_EQ( op.size(), dd.getOp().size() );
    EXPECT_EQ( op.size(), dd.getGamma().size() );

    for(size_t k = 0; k < op.size(); ++k)
    {
        EXPECT_COMPLEXDOUBLE_EQ( solveCoshxEqExpy( -op(k).V/2.0 ),  ( dd.getGamma() )(k) );
    }
}

TEST(DensityDensityOperatorTest, hopSpinConstruction)
{
    size_t L(10);
    string decompType="hopSpin";
    TensorHao<OneNiNj, 1> op(5);
    for(size_t k = 0; k < op.size(); ++k)
    {
        op(k).i = k;
        op(k).j = k+1;
        op(k).V = 2.12*k;
    }
    NiNj dd(L, decompType, op);
    EXPECT_EQ( L, dd.getL() );
    EXPECT_EQ( decompType, dd.getDecompType() );
    EXPECT_EQ( op.size(), dd.getOp().size() );
    EXPECT_EQ( op.size(), dd.getGamma().size() );

    for(size_t k = 0; k < op.size(); ++k)
    {
        EXPECT_COMPLEXDOUBLE_EQ( solveCosxEqExpy( -op(k).V/2.0 ),  ( dd.getGamma() )(k) );
    }
}