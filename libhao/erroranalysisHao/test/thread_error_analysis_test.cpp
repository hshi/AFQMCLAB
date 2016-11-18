#include "../include/threadErrorAnalysis.h"
#include "../include/serialErrorAnalysis.h"
#include "../../testHao/gtest_custom.h"

using namespace std;

class ComplexDoubleThreadAnalysisTest: public ::testing::Test
{
 public:
    complex<double> valueEachThread, mean_exact, var_exact, err_exact;

    ComplexDoubleThreadAnalysisTest( )
    {
        int rank = MPIRank(); int size = MPISize();

        valueEachThread = complex<double> (rank, rank+1);

        vector< complex<double> > vec(size); for(int i=0; i<size; i++) vec[i]=complex<double>(i,i+1);

        tie(mean_exact, err_exact) = getMeanError(vec);
        var_exact  = getVariance(vec, mean_exact);
    }

    ~ComplexDoubleThreadAnalysisTest( )  {}
};

TEST_F(ComplexDoubleThreadAnalysisTest, calculateMeanBetweenThreads)
{
    complex<double> mean = calculateMeanBetweenThreads(valueEachThread);
    EXPECT_COMPLEXDOUBLE_EQ(mean_exact, mean);
}

TEST_F(ComplexDoubleThreadAnalysisTest, calculateVarianceBetweenThreads)
{
    complex<double> mean = calculateMeanBetweenThreads(valueEachThread);
    complex<double> var  = calculateVarianceBetweenThreads(valueEachThread, mean);
    EXPECT_COMPLEXDOUBLE_EQ(mean_exact, mean);
    if( MPIRank() ==0 )
    {
        EXPECT_COMPLEXDOUBLE_EQ(var_exact, var);
    }
}

TEST_F(ComplexDoubleThreadAnalysisTest, calculateErrorBetweenThreads)
{
    complex<double> mean = calculateMeanBetweenThreads(valueEachThread);
    complex<double> err  = calculateErrorBetweenThreads(valueEachThread, mean);
    EXPECT_COMPLEXDOUBLE_EQ(mean_exact, mean);
    if( MPIRank() ==0 )
    {
        EXPECT_COMPLEXDOUBLE_EQ(err_exact, err);
    }
}

TEST_F(ComplexDoubleThreadAnalysisTest, calculateMeanErrorBetweenThreads)
{
    complex<double> mean, err;
    tie(mean, err) = calculateMeanErrorBetweenThreads(valueEachThread);
    EXPECT_COMPLEXDOUBLE_EQ(mean_exact, mean);
    if( MPIRank() ==0 )
    {
        EXPECT_COMPLEXDOUBLE_EQ(err_exact, err);
    }
}


class ComplexDoubleVectorThreadAnalysisTest: public ::testing::Test
{
 public:
    vector< complex<double> > valueEachThread, mean_exact, var_exact, err_exact;

    ComplexDoubleVectorThreadAnalysisTest( )
    {
        valueEachThread.resize(3); mean_exact.resize(3); var_exact.resize(3); err_exact.resize(3);

        int rank = MPIRank(); int size = MPISize();
        vector< complex<double> > vec(size);
        for(int iArray=0; iArray<3; iArray++)
        {
            valueEachThread[iArray]=complex<double>(rank+iArray, rank+iArray+2);
            for(int iRank=0; iRank<size; iRank++) vec[iRank]=complex<double>(iRank+iArray,iRank+iArray+2);
            tie(mean_exact[iArray], err_exact[iArray]) = getMeanError(vec);
            var_exact[iArray] = getVariance(vec, mean_exact[iArray]);
        }
    }

    ~ComplexDoubleVectorThreadAnalysisTest( )  {}
};

TEST_F(ComplexDoubleVectorThreadAnalysisTest, calculateMeanBetweenThreadsPointer)
{
    vector< complex<double> > mean = calculateMeanBetweenThreads( valueEachThread.size(), valueEachThread.data() );
    EXPECT_VECOTR_COMPLEXDOUBLE_EQ(mean_exact, mean);
}

TEST_F(ComplexDoubleVectorThreadAnalysisTest, calculateVarianceBetweenThreadsPointer)
{
    vector< complex<double> > mean = calculateMeanBetweenThreads( valueEachThread.size(), valueEachThread.data() );
    vector< complex<double> > var  = calculateVarianceBetweenThreads( valueEachThread.size(), valueEachThread.data(),
                                                                      mean.data() );
    EXPECT_VECOTR_COMPLEXDOUBLE_EQ(mean_exact, mean);
    if( MPIRank() == 0 )
    {
        EXPECT_VECOTR_COMPLEXDOUBLE_EQ(var_exact, var);
    }
}

TEST_F(ComplexDoubleVectorThreadAnalysisTest, calculateErrorBetweenThreadsPointer)
{
    vector< complex<double> > mean = calculateMeanBetweenThreads( valueEachThread.size(), valueEachThread.data() );
    vector< complex<double> > err  = calculateErrorBetweenThreads( valueEachThread.size(), valueEachThread.data(),
                                                                   mean.data() );
    EXPECT_VECOTR_COMPLEXDOUBLE_EQ(mean_exact, mean);
    if( MPIRank() == 0 )
    {
        EXPECT_VECOTR_COMPLEXDOUBLE_EQ(err_exact, err);
    }
}

TEST_F(ComplexDoubleVectorThreadAnalysisTest, calculateMeanErrorBetweenThreadsPointer)
{
    vector< complex<double> > mean, err;
    tie( mean, err )  = calculateMeanErrorBetweenThreads( valueEachThread.size(), valueEachThread.data() );
    EXPECT_VECOTR_COMPLEXDOUBLE_EQ(mean_exact, mean);
    if( MPIRank() == 0 )
    {
        EXPECT_VECOTR_COMPLEXDOUBLE_EQ(err_exact, err);
    }
}

TEST_F(ComplexDoubleVectorThreadAnalysisTest, calculateMeanBetweenThreadsVector)
{
    vector< complex<double> > mean = calculateMeanBetweenThreads( valueEachThread );
    EXPECT_VECOTR_COMPLEXDOUBLE_EQ(mean_exact, mean);
}

TEST_F(ComplexDoubleVectorThreadAnalysisTest, calculateVarianceBetweenThreadsVector)
{
    vector< complex<double> > mean = calculateMeanBetweenThreads( valueEachThread );
    vector< complex<double> > variance  = calculateVarianceBetweenThreads( valueEachThread, mean );
    EXPECT_VECOTR_COMPLEXDOUBLE_EQ(mean_exact, mean);
    if( MPIRank() == 0 )
    {
        EXPECT_VECOTR_COMPLEXDOUBLE_EQ(var_exact, variance);
    }
}

TEST_F(ComplexDoubleVectorThreadAnalysisTest, calculateErrorBetweenThreadsVector)
{
    vector< complex<double> > mean = calculateMeanBetweenThreads( valueEachThread );
    vector< complex<double> > err  = calculateErrorBetweenThreads( valueEachThread, mean );
    EXPECT_VECOTR_COMPLEXDOUBLE_EQ(mean_exact, mean);
    if( MPIRank() == 0 )
    {
        EXPECT_VECOTR_COMPLEXDOUBLE_EQ(err_exact, err);
    }
}

TEST_F(ComplexDoubleVectorThreadAnalysisTest, calculateMeanErrorBetweenThreadsVector)
{
    vector< complex<double> > mean, err;
    tie( mean, err )  = calculateMeanErrorBetweenThreads( valueEachThread );
    EXPECT_VECOTR_COMPLEXDOUBLE_EQ(mean_exact, mean);
    if( MPIRank() == 0 )
    {
        EXPECT_VECOTR_COMPLEXDOUBLE_EQ(err_exact, err);
    }
}