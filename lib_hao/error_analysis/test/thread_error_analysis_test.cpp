#include "../include/thread_error_analysis.h"
#include "../include/error_analysis.h"
#include "../../../utilities/test_hao/gtest_custom.h"

using namespace std;

TEST(calculateMeanErrorBetweenThread, ComplexDouble)
{
    int rank = MPIRank(); int size = MPISize();

    vector< complex<double> > vec(size); for(int i=0; i<size; i++) vec[i]=complex<double>(i,i+1);
    complex<double> mean_exact;
    double err_exact;
    getMeanError(vec, mean_exact, err_exact);

    complex<double> value_thread(rank, rank+1);
    complex<double> mean;
    double err;
    calculateMeanErrorBetweenThread(value_thread, mean, err);

    if(rank ==0 )
    {
        EXPECT_COMPLEXDOUBLE_EQ(mean_exact, mean);
        EXPECT_DOUBLE_EQ(err_exact, err);
    }
}

TEST(calculateMeanErrorBetweenThread, ComplexDoublePointerVector)
{
    int rank = MPIRank(); int size = MPISize();

    vector< complex<double> > mean_exact(3);
    vector< double >          err_exact(3);
    vector< complex<double> > vec(size);
    for(int i_array=0; i_array<3; i_array++)
    {
        for(int i=0; i<size; i++) vec[i]=complex<double>(i+i_array,i+i_array+2);
        getMeanError(vec, mean_exact[i_array], err_exact[i_array]);
    }

    vector< complex<double> > value_thread(3);
    vector< complex<double> > mean(3);
    vector< double > err; if( rank == 0 ) err.resize(3);
    for(int i_array=0; i_array<3; i_array++) value_thread[i_array]=complex<double>(rank+i_array, rank+i_array+2);

    //Test pointer
    calculateMeanErrorBetweenThread(3, value_thread.data(), mean.data(), err.data());
    if( rank == 0 )
    {
        EXPECT_VECOTR_COMPLEXDOUBLE_EQ(mean_exact, mean);
        EXPECT_VECOTR_DOUBLE_EQ(err_exact, err);
    }

    //Test vector
    calculateMeanErrorBetweenThread(value_thread, mean, err);
    if( rank == 0 )
    {
        EXPECT_VECOTR_COMPLEXDOUBLE_EQ(mean_exact, mean);
        EXPECT_VECOTR_DOUBLE_EQ(err_exact, err);
    }
}