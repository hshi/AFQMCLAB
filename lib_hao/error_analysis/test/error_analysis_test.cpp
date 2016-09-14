#include <iostream>
#include "../include/error_analysis.h"
#include "../../../utilities/test_hao/gtest_custom.h"

using namespace std;

TEST(getMeanError, getDivisor)
{
    size_t n=500;
    vector<size_t> fact;
    vector<size_t> fact_exact={1,2,4,5,10,20,25,50,100,125,250,500};
    fact = getDivisor(n);
    EXPECT_VECOTR_EQ(fact_exact, fact);
}

class DoubleAnalysisTest: public ::testing::Test
{
public:
    vector<double> array = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0};
    vector<double> mean_block_exact={5.5,5.5,5.5,5.5};
    vector<double> err_block_exact={0.95742710775633810,1.4142135623730951,2.5,0};
};

TEST_F(DoubleAnalysisTest, getMeanPointer)
{
    double mean;
    getMean(array.size(), array.data(), mean);
    EXPECT_DOUBLE_EQ(mean_block_exact[0], mean);
}

TEST_F(DoubleAnalysisTest, getErrorPointer)
{
    double mean, err;
    getMean(array.size(), array.data(), mean);
    getError(array.size(), array.data(), mean, err);
    EXPECT_DOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(DoubleAnalysisTest, getMeanErrorPointer)
{
    double mean, err;
    getMeanError(array.size(), array.data(), mean, err);
    EXPECT_DOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(DoubleAnalysisTest, getBlockMeanErrorPointer)
{
    double mean, err;
    int blk_size = 2;
    getBlockMeanError(array.size(), blk_size, array.data(), mean, err);
    EXPECT_DOUBLE_EQ(mean_block_exact[1], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[1], err);
}

TEST_F(DoubleAnalysisTest, getAllBlockMeanErrorPointer)
{
    vector<size_t> fact;
    vector<double> mean_block, err_block;
    getAllBlockMeanError(array.size(), array.data(), fact, mean_block, err_block);
    EXPECT_VECOTR_DOUBLE_EQ(mean_block_exact, mean_block);
    EXPECT_VECOTR_DOUBLE_EQ(err_block_exact, err_block);
}

TEST_F(DoubleAnalysisTest, getMeanVector)
{
    double mean;
    getMean(array, mean);
    EXPECT_DOUBLE_EQ(mean_block_exact[0], mean);
}

TEST_F(DoubleAnalysisTest, getErrorVector)
{
    double mean, err;
    getMean(array, mean);
    getError(array, mean, err);
    EXPECT_DOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(DoubleAnalysisTest, getMeanErrorVector)
{
    double mean, err;
    getMeanError(array, mean, err);
    EXPECT_DOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(DoubleAnalysisTest, getBlockMeanErrorVector)
{
    double mean, err;
    int blk_size = 2;
    getBlockMeanError(blk_size, array, mean, err);
    EXPECT_DOUBLE_EQ(mean_block_exact[1], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[1], err);
}

TEST_F(DoubleAnalysisTest, getAllBlockMeanErrorVector)
{
    vector<size_t> fact;
    vector<double> mean_block, err_block;
    getAllBlockMeanError(array, fact, mean_block, err_block);
    EXPECT_VECOTR_DOUBLE_EQ(mean_block_exact, mean_block);
    EXPECT_VECOTR_DOUBLE_EQ(err_block_exact, err_block);
}


class ComplexDoubleAnalysisTest: public ::testing::Test
{
public:
    vector< complex<double> > array = { {1.0,2.0}, {3.0,4.0}, {5.0,6.0}, {7.0,8.0}, {9.0,10.0}, {11, 12}, {13, 14}, {15, 16} };
    vector< complex<double> > mean_block_exact={ {8, 9}, {8, 9}, {8, 9}, {8, 9} };
    vector< double > err_block_exact={2.4494897427831779, 3.6514837167011072, 5.6568542494923806, 0.0};
};

TEST_F(ComplexDoubleAnalysisTest, getMeanPointer)
{
    complex<double> mean;
    getMean(array.size(), array.data(), mean);
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[0], mean);
}

TEST_F(ComplexDoubleAnalysisTest, getErrorPointer)
{
    complex<double> mean; double err;
    getMean(array.size(), array.data(), mean);
    getError(array.size(), array.data(), mean, err);
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(ComplexDoubleAnalysisTest, getMeanErrorPointer)
{
    complex<double> mean; double err;
    getMeanError(array.size(), array.data(), mean, err);
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(ComplexDoubleAnalysisTest, getBlockMeanError)
{
    complex<double> mean; double err;
    int blk_size = 2;
    getBlockMeanError(array.size(), blk_size, array.data(), mean, err);
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[1], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[1], err);
}

TEST_F(ComplexDoubleAnalysisTest, getAllBlockMeanErrorPointer)
{
    vector<size_t> fact;
    vector< complex<double> > mean_block;
    vector<double> err_block;
    getAllBlockMeanError(array.size(), array.data(), fact, mean_block, err_block);
    EXPECT_VECOTR_COMPLEXDOUBLE_EQ(mean_block_exact, mean_block);
    EXPECT_VECOTR_DOUBLE_EQ(err_block_exact, err_block);
}

TEST_F(ComplexDoubleAnalysisTest, getMeanVector)
{
    complex<double> mean;
    getMean(array, mean);
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[0], mean);
}

TEST_F(ComplexDoubleAnalysisTest, getErrorVector)
{
    complex<double> mean; double err;
    getMean(array, mean);
    getError(array, mean, err);
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(ComplexDoubleAnalysisTest, getMeanErrorVector)
{
    complex<double> mean; double err;
    getMeanError(array, mean, err);
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(ComplexDoubleAnalysisTest, getBlockMeanErrorVector)
{
    complex<double> mean; double err;
    int blk_size = 2;
    getBlockMeanError(blk_size, array, mean, err);
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[1], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[1], err);
}

TEST_F(ComplexDoubleAnalysisTest, getAllBlockMeanErrorVector)
{
    vector<size_t> fact;
    vector< complex<double> > mean_block;
    vector<double> err_block;
    getAllBlockMeanError(array, fact, mean_block, err_block);
    EXPECT_VECOTR_COMPLEXDOUBLE_EQ(mean_block_exact, mean_block);
    EXPECT_VECOTR_DOUBLE_EQ(err_block_exact, err_block);
}