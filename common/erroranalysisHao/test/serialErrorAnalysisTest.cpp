#include <iostream>
#include "../include/serialErrorAnalysis.h"
#include "../../testHao/gtest_custom.h"

using namespace std;

TEST(getMeanError, getDivisors)
{
    size_t n=500;
    vector<size_t> divisors;
    vector<size_t> divisors_exact={1,2,4,5,10,20,25,50,100,125,250,500};
    divisors = getDivisors(n);
    EXPECT_VECOTR_EQ(divisors_exact, divisors);
}

class DoubleAnalysisTest: public ::testing::Test
{
public:
    vector<double> array = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0};
    vector<double> mean_block_exact={5.5,5.5,5.5,5.5};
    vector<double> var_block_exact={8.25,  8.  ,  6.25,  0.};
    vector<double> err_block_exact={0.95742710775633810,1.4142135623730951,2.5,0};
};

TEST_F(DoubleAnalysisTest, getMeanPointer)
{
    double mean = getMean( array.size(), array.data() );
    EXPECT_DOUBLE_EQ(mean_block_exact[0], mean);
}

TEST_F(DoubleAnalysisTest, getVariancePointer)
{
    double mean = getMean( array.size(), array.data() );
    double variance  = getVariance( array.size(), array.data(), mean );
    EXPECT_DOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(var_block_exact[0], variance);
}

TEST_F(DoubleAnalysisTest, getErrorPointer)
{
    double mean = getMean( array.size(), array.data() );
    double err  = getError( array.size(), array.data(), mean );
    EXPECT_DOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(DoubleAnalysisTest, getMeanErrorPointer)
{
    double mean, err;
    tie(mean, err) = getMeanError( array.size(), array.data() );
    EXPECT_DOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(DoubleAnalysisTest, getBlockMeanErrorPointer)
{
    double mean, err;
    int blk_size = 2;
    tie(mean, err) = getBlockMeanError( array.size(), blk_size, array.data() );
    EXPECT_DOUBLE_EQ(mean_block_exact[1], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[1], err);
}

TEST_F(DoubleAnalysisTest, getAllBlockMeanErrorPointer)
{
    vector<size_t> divisors;
    vector<double> mean_block, err_block;
    tie( divisors, mean_block, err_block ) = getAllBlockMeanError( array.size(), array.data() );
    EXPECT_VECOTR_DOUBLE_EQ(mean_block_exact, mean_block);
    EXPECT_VECOTR_DOUBLE_EQ(err_block_exact, err_block);
}

TEST_F(DoubleAnalysisTest, getMeanVector)
{
    double mean = getMean(array);
    EXPECT_DOUBLE_EQ(mean_block_exact[0], mean);
}

TEST_F(DoubleAnalysisTest, getVarianceVector)
{
    double mean = getMean( array );
    double variance  = getVariance( array, mean );
    EXPECT_DOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(var_block_exact[0], variance);
}


TEST_F(DoubleAnalysisTest, getErrorVector)
{
    double mean = getMean( array );
    double err  = getError( array, mean );
    EXPECT_DOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(DoubleAnalysisTest, getMeanErrorVector)
{
    double mean, err;
    tie(mean, err) = getMeanError(array);
    EXPECT_DOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(DoubleAnalysisTest, getBlockMeanErrorVector)
{
    double mean, err;
    int blk_size = 2;
    tie(mean, err) = getBlockMeanError( blk_size, array );
    EXPECT_DOUBLE_EQ(mean_block_exact[1], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[1], err);
}

TEST_F(DoubleAnalysisTest, getAllBlockMeanErrorVector)
{
    vector<size_t> divisors;
    vector<double> mean_block, err_block;
    tie(divisors, mean_block, err_block) = getAllBlockMeanError(array);
    EXPECT_VECOTR_DOUBLE_EQ(mean_block_exact, mean_block);
    EXPECT_VECOTR_DOUBLE_EQ(err_block_exact, err_block);
}


class ComplexDoubleAnalysisTest: public ::testing::Test
{
public:
    vector< complex<double> > array = { {1.0,2.0}, {3.0,4.0}, {5.0,6.0}, {7.0,8.0}, {9.0,10.0}, {11, 12}, {13, 14}, {15, 16} };
    vector< complex<double> > mean_block_exact={ {8, 9}, {8, 9}, {8, 9}, {8, 9} };
    vector< complex<double> > var_block_exact={42.,  40.,  32.,   0.};
    vector< complex<double> > err_block_exact={2.4494897427831779, 3.6514837167011072, 5.6568542494923806, 0.0};
};

TEST_F(ComplexDoubleAnalysisTest, getMeanPointer)
{
    complex<double> mean = getMean( array.size(), array.data() );
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[0], mean);
}

TEST_F(ComplexDoubleAnalysisTest, getVariancePointer)
{
    complex<double> mean = getMean( array.size(), array.data() );
    complex<double> variance  = getVariance( array.size(), array.data(), mean );
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_COMPLEXDOUBLE_EQ(var_block_exact[0], variance);
}

TEST_F(ComplexDoubleAnalysisTest, getErrorPointer)
{
    complex<double> mean = getMean( array.size(), array.data() );
    complex<double> err  = getError( array.size(), array.data(), mean );
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_COMPLEXDOUBLE_EQ(err_block_exact[0], err);
}


TEST_F(ComplexDoubleAnalysisTest, getMeanErrorPointer)
{
    complex<double> mean, err;
    tie(mean, err) = getMeanError( array.size(), array.data() );
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_COMPLEXDOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(ComplexDoubleAnalysisTest, getBlockMeanError)
{
    complex<double> mean, err;
    int blk_size = 2;
    tie(mean, err) = getBlockMeanError( array.size(), blk_size, array.data() );
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[1], mean);
    EXPECT_COMPLEXDOUBLE_EQ(err_block_exact[1], err);
}

TEST_F(ComplexDoubleAnalysisTest, getAllBlockMeanErrorPointer)
{
    vector<size_t> divisors;
    vector< complex<double> > mean_block, err_block;
    tie(divisors, mean_block, err_block) = getAllBlockMeanError( array.size(), array.data() );
    EXPECT_VECOTR_COMPLEXDOUBLE_EQ(mean_block_exact, mean_block);
    EXPECT_VECOTR_COMPLEXDOUBLE_EQ(err_block_exact, err_block);
}

TEST_F(ComplexDoubleAnalysisTest, getMeanVector)
{
    complex<double> mean = getMean(array);
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[0], mean);
}

TEST_F(ComplexDoubleAnalysisTest, getVarianceVector)
{
    complex<double> mean = getMean( array );
    complex<double> variance  = getVariance( array, mean );
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_COMPLEXDOUBLE_EQ(var_block_exact[0], variance);
}

TEST_F(ComplexDoubleAnalysisTest, getErrorVector)
{
    complex<double> mean = getMean(array);
    complex<double> err  = getError(array, mean);
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_COMPLEXDOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(ComplexDoubleAnalysisTest, getMeanErrorVector)
{
    complex<double> mean, err;
    tie(mean, err) = getMeanError(array);
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_COMPLEXDOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(ComplexDoubleAnalysisTest, getBlockMeanErrorVector)
{
    complex<double> mean, err;
    int blk_size = 2;
    tie(mean, err) = getBlockMeanError(blk_size, array);
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[1], mean);
    EXPECT_COMPLEXDOUBLE_EQ(err_block_exact[1], err);
}

TEST_F(ComplexDoubleAnalysisTest, getAllBlockMeanErrorVector)
{
    vector<size_t> divisors;
    vector< complex<double> > mean_block, err_block;
    tie(divisors, mean_block, err_block) = getAllBlockMeanError(array);
    EXPECT_VECOTR_COMPLEXDOUBLE_EQ(mean_block_exact, mean_block);
    EXPECT_VECOTR_COMPLEXDOUBLE_EQ(err_block_exact, err_block);
}