//
// Created by boruoshihao on 1/9/17.
//
#include "../include/NiupNidnSample.h"
#include "../../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(NiupNidnSampleTest, voidConstruction)
{
    NiupNidnSample twoBodySample;
    EXPECT_EQ( 0.0, twoBodySample.logw );
    EXPECT_EQ( 0, twoBodySample.diag00.size() );
    EXPECT_EQ( 0, twoBodySample.diag10.size() );
    EXPECT_EQ( 0, twoBodySample.diag01.size() );
    EXPECT_EQ( 0, twoBodySample.diag11.size() );
}

TEST(NiupNidnSampleTest, size_tConstruction)
{
    size_t L=20;
    NiupNidnSample twoBodySample(L);
    EXPECT_EQ( 0.0, twoBodySample.logw );
    EXPECT_EQ( L, twoBodySample.diag00.size() );
    EXPECT_EQ( L, twoBodySample.diag10.size() );
    EXPECT_EQ( L, twoBodySample.diag01.size() );
    EXPECT_EQ( L, twoBodySample.diag11.size() );
}

TEST(NiupNidnSampleTest, copyConstruction)
{
    NiupNidnSample twoBodySampleBase;
    twoBodySampleBase.logw = 2.0;
    twoBodySampleBase.diag00.resize(10);
    twoBodySampleBase.diag10.resize(11);
    twoBodySampleBase.diag01.resize(12);
    twoBodySampleBase.diag11.resize(13);

    NiupNidnSample twoBodySample(twoBodySampleBase);
    EXPECT_EQ( 2.0, twoBodySample.logw );
    EXPECT_EQ( 10, twoBodySample.diag00.size() );
    EXPECT_EQ( 11, twoBodySample.diag10.size() );
    EXPECT_EQ( 12, twoBodySample.diag01.size() );
    EXPECT_EQ( 13, twoBodySample.diag11.size() );
    EXPECT_TRUE( twoBodySampleBase.diag00.data() );
    EXPECT_TRUE( twoBodySampleBase.diag10.data() );
    EXPECT_TRUE( twoBodySampleBase.diag01.data() );
    EXPECT_TRUE( twoBodySampleBase.diag11.data() );
}

TEST(NiupNidnSampleTest, moveConstruction)
{
    NiupNidnSample twoBodySampleBase;
    twoBodySampleBase.logw = 2.0;
    twoBodySampleBase.diag00.resize(10);
    twoBodySampleBase.diag10.resize(11);
    twoBodySampleBase.diag01.resize(12);
    twoBodySampleBase.diag11.resize(13);

    NiupNidnSample twoBodySample( move(twoBodySampleBase) );
    EXPECT_EQ( 2.0, twoBodySample.logw );
    EXPECT_EQ( 10, twoBodySample.diag00.size() );
    EXPECT_EQ( 11, twoBodySample.diag10.size() );
    EXPECT_EQ( 12, twoBodySample.diag01.size() );
    EXPECT_EQ( 13, twoBodySample.diag11.size() );
    EXPECT_FALSE( twoBodySampleBase.diag00.data() );
    EXPECT_FALSE( twoBodySampleBase.diag10.data() );
    EXPECT_FALSE( twoBodySampleBase.diag01.data() );
    EXPECT_FALSE( twoBodySampleBase.diag11.data() );
}

TEST(NiupNidnSampleTest, copyAssignment)
{
    NiupNidnSample twoBodySampleBase;
    twoBodySampleBase.logw = 2.0;
    twoBodySampleBase.diag00.resize(10);
    twoBodySampleBase.diag10.resize(11);
    twoBodySampleBase.diag01.resize(12);
    twoBodySampleBase.diag11.resize(13);

    NiupNidnSample twoBodySample; twoBodySample = twoBodySampleBase;
    EXPECT_EQ( 2.0, twoBodySample.logw );
    EXPECT_EQ( 10, twoBodySample.diag00.size() );
    EXPECT_EQ( 11, twoBodySample.diag10.size() );
    EXPECT_EQ( 12, twoBodySample.diag01.size() );
    EXPECT_EQ( 13, twoBodySample.diag11.size() );
    EXPECT_TRUE( twoBodySampleBase.diag00.data() );
    EXPECT_TRUE( twoBodySampleBase.diag10.data() );
    EXPECT_TRUE( twoBodySampleBase.diag01.data() );
    EXPECT_TRUE( twoBodySampleBase.diag11.data() );
}

TEST(NiupNidnSampleTest, moveAssignment)
{
    NiupNidnSample twoBodySampleBase;
    twoBodySampleBase.logw = 2.0;
    twoBodySampleBase.diag00.resize(10);
    twoBodySampleBase.diag10.resize(11);
    twoBodySampleBase.diag01.resize(12);
    twoBodySampleBase.diag11.resize(13);

    NiupNidnSample twoBodySample; twoBodySample =  move(twoBodySampleBase);
    EXPECT_EQ( 2.0, twoBodySample.logw );
    EXPECT_EQ( 10, twoBodySample.diag00.size() );
    EXPECT_EQ( 11, twoBodySample.diag10.size() );
    EXPECT_EQ( 12, twoBodySample.diag01.size() );
    EXPECT_EQ( 13, twoBodySample.diag11.size() );
    EXPECT_FALSE( twoBodySampleBase.diag00.data() );
    EXPECT_FALSE( twoBodySampleBase.diag10.data() );
    EXPECT_FALSE( twoBodySampleBase.diag01.data() );
    EXPECT_FALSE( twoBodySampleBase.diag11.data() );
}