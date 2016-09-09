#include <iostream>
#include "../include/error_analysis.h"
#include "../../../utilities/test_hao/gtest_custom.h"

using namespace std;

TEST(error_analysis, get_factors)
{
    size_t n=500;
    vector<size_t> fact;
    vector<size_t> fact_exact={1,2,4,5,10,20,25,50,100,125,250,500};
    get_factors(n,fact);
    EXPECT_VECOTR_EQ(fact_exact, fact);
}

class DoubleAnalysisTest: public ::testing::Test
{
public:
    vector<double> array = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0};
    vector<double> mean_block_exact={5.5,5.5,5.5,5.5};
    vector<double> err_block_exact={0.95742710775633810,1.4142135623730951,2.5,0};
};

TEST_F(DoubleAnalysisTest, get_average_pointer)
{
    double mean;
    get_average( array.size(), array.data(), mean );
    EXPECT_DOUBLE_EQ(mean_block_exact[0], mean);
}

TEST_F(DoubleAnalysisTest, get_err_pointer)
{
    double mean, err;
    get_average( array.size(), array.data(), mean );
    get_err(array.size(),array.data(), mean, err);
    EXPECT_DOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(DoubleAnalysisTest, error_analysis_pointer)
{
    double mean, err;
    error_analysis(array.size(),array.data(), mean, err);
    EXPECT_DOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(DoubleAnalysisTest, error_analysis_blk_pointer)
{
    double mean, err;
    int blk_size = 2;
    error_analysis_blk(array.size(), blk_size, array.data(), mean, err);
    EXPECT_DOUBLE_EQ(mean_block_exact[1], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[1], err);
}

TEST_F(DoubleAnalysisTest, error_analysis_blk_loop_pointer)
{
    vector<size_t> fact;
    vector<double> mean_block, err_block;
    error_analysis_blk_loop(array.size(), array.data(), fact, mean_block,err_block);
    EXPECT_VECOTR_DOUBLE_EQ(mean_block_exact, mean_block);
    EXPECT_VECOTR_DOUBLE_EQ(err_block_exact, err_block);
}

TEST_F(DoubleAnalysisTest, get_average_vector)
{
    double mean;
    get_average( array, mean );
    EXPECT_DOUBLE_EQ(mean_block_exact[0], mean);
}

TEST_F(DoubleAnalysisTest, get_err_vector)
{
    double mean, err;
    get_average( array, mean );
    get_err(array, mean, err);
    EXPECT_DOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(DoubleAnalysisTest, error_analysis_vector)
{
    double mean, err;
    error_analysis(array, mean, err);
    EXPECT_DOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(DoubleAnalysisTest, error_analysis_blk_vector)
{
    double mean, err;
    int blk_size = 2;
    error_analysis_blk(blk_size, array, mean, err);
    EXPECT_DOUBLE_EQ(mean_block_exact[1], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[1], err);
}

TEST_F(DoubleAnalysisTest, error_analysis_blk_loop_vector)
{
    vector<size_t> fact;
    vector<double> mean_block, err_block;
    error_analysis_blk_loop(array, fact, mean_block,err_block);
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

TEST_F(ComplexDoubleAnalysisTest, get_average_pointer)
{
    complex<double> mean;
    get_average( array.size(), array.data(), mean );
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[0], mean);
}

TEST_F(ComplexDoubleAnalysisTest, get_err_pointer)
{
    complex<double> mean; double err;
    get_average( array.size(), array.data(), mean );
    get_err(array.size(),array.data(), mean, err);
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(ComplexDoubleAnalysisTest, error_analysis_pointer)
{
    complex<double> mean; double err;
    error_analysis(array.size(),array.data(), mean, err);
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(ComplexDoubleAnalysisTest, error_analysis_blk_pointer)
{
    complex<double> mean; double err;
    int blk_size = 2;
    error_analysis_blk(array.size(), blk_size, array.data(), mean, err);
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[1], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[1], err);
}

TEST_F(ComplexDoubleAnalysisTest, error_analysis_blk_loop_pointer)
{
    vector<size_t> fact;
    vector< complex<double> > mean_block;
    vector<double> err_block;
    error_analysis_blk_loop(array.size(), array.data(), fact, mean_block,err_block);
    EXPECT_VECOTR_COMPLEXDOUBLE_EQ(mean_block_exact, mean_block);
    EXPECT_VECOTR_DOUBLE_EQ(err_block_exact, err_block);
}

TEST_F(ComplexDoubleAnalysisTest, get_average_vector)
{
    complex<double> mean;
    get_average( array, mean );
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[0], mean);
}

TEST_F(ComplexDoubleAnalysisTest, get_err_vector)
{
    complex<double> mean; double err;
    get_average(array, mean );
    get_err(array, mean, err);
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(ComplexDoubleAnalysisTest, error_analysis_vector)
{
    complex<double> mean; double err;
    error_analysis(array, mean, err);
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[0], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[0], err);
}

TEST_F(ComplexDoubleAnalysisTest, error_analysis_blk_vector)
{
    complex<double> mean; double err;
    int blk_size = 2;
    error_analysis_blk(blk_size, array, mean, err);
    EXPECT_COMPLEXDOUBLE_EQ(mean_block_exact[1], mean);
    EXPECT_DOUBLE_EQ(err_block_exact[1], err);
}

TEST_F(ComplexDoubleAnalysisTest, error_analysis_blk_loop_vector)
{
    vector<size_t> fact;
    vector< complex<double> > mean_block;
    vector<double> err_block;
    error_analysis_blk_loop(array, fact, mean_block,err_block);
    EXPECT_VECOTR_COMPLEXDOUBLE_EQ(mean_block_exact, mean_block);
    EXPECT_VECOTR_DOUBLE_EQ(err_block_exact, err_block);
}