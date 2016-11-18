#include <iostream>
#include "../include/kahan.h"
#include "../../testHao/gtest_custom.h"

using namespace std;

TEST (KahanData, void_constructor)
{
    KahanData<double> ksum;
    EXPECT_DOUBLE_EQ( 0.0, ksum.returnAccumulateError() );
    EXPECT_DOUBLE_EQ( 0.0, ksum.returnSum() );
}

TEST (KahanData, value_constructor)
{
    KahanData<double> ksum(0.2);
    EXPECT_DOUBLE_EQ( 0.0, ksum.returnAccumulateError() );
    EXPECT_DOUBLE_EQ( 0.2, ksum.returnSum() );
}

TEST (KahanData, copy_constructor)
{
    KahanData<double> ksum_init(0.2);
    KahanData<double> ksum( ksum_init );
    EXPECT_DOUBLE_EQ( 0.0, ksum.returnAccumulateError() );
    EXPECT_DOUBLE_EQ( 0.2, ksum.returnSum() );
}

TEST (KahanData, copy_assigment)
{
    KahanData<double> ksum_init(0.2);
    KahanData<double> ksum;
    ksum = ksum_init;
    EXPECT_DOUBLE_EQ( 0.0, ksum.returnAccumulateError() );
    EXPECT_DOUBLE_EQ( 0.2, ksum.returnSum() );
}

TEST (KahanData, copy_value)
{
    KahanData<double> ksum;
    ksum = 0.2;
    EXPECT_DOUBLE_EQ( 0.0, ksum.returnAccumulateError() );
    EXPECT_DOUBLE_EQ( 0.2, ksum.returnSum() );
}


TEST (KahanData, add_equal)
{
    KahanData<double> ksum;
    ksum += 0.2;
    EXPECT_DOUBLE_EQ( 0.0, ksum.returnAccumulateError() );
    EXPECT_DOUBLE_EQ( 0.2, ksum.returnSum() );
}

TEST (KahanData, big_sum)
{
    //Here sum_naive will give bad results
    KahanData<double> ksum;
    //double sum_naive=0;
    for (int i=1; i<=499992; i++)
    {
        double j=1000.00001;
        ksum+=j;
        //sum_naive+=j;
        //std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' ); // means pause in fortran
    }
    EXPECT_DOUBLE_EQ( 499992004.99992, ksum.returnSum() );
    //cout<<setprecision(20)<<sum_naive<<endl;
}