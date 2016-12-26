//
// Created by boruoshihao on 9/2/16.
//

#ifndef AFQMCLAB_GTEST_CUSTOM_H
#define AFQMCLAB_GTEST_CUSTOM_H

#include <complex>
#include <cmath>
#include <vector>
#include "gtest/gtest.h"

void EXPECT_COMPLEXFLOAT_EQ (std::complex<float> expected, std::complex<float> actual);

void EXPECT_COMPLEXDOUBLE_EQ (std::complex<double> expected, std::complex<double> actual);

template<typename T>
void EXPECT_COMPLEX_NEAR(std::complex<T> expected, std::complex<T> actual, double abs_error=1e-12)
{
    EXPECT_NEAR( 0.0, std::abs( expected - actual ), abs_error );
}

template<typename T>
void EXPECT_POINTER_EQ(size_t L, const T *expected, const T *actual)
{
    ::testing::AssertionResult results = ::testing::AssertionSuccess();

    for(size_t i=0; i<L; i++)
    {
        if( expected[i] != actual[i] )
        {
            results = ::testing::AssertionFailure() << " expected[" << i
                                                    << "] (" << expected[i] << ") != actual[" << i
                                                    << "] (" << actual[i] << ") ";
            break;
        }
    }
    EXPECT_TRUE( results );
}

void EXPECT_POINTER_DOUBLE_EQ(size_t L, const double *expected, const double *actual);

void EXPECT_POINTER_COMPLEXDOUBLE_EQ(size_t L, const std::complex<double> *expected, const std::complex<double> *actual);

template<typename T>
void EXPECT_VECOTR_EQ(const std::vector<T>& expected, const std::vector<T>& actual )
{
    EXPECT_EQ(expected, actual);
}

void EXPECT_VECOTR_DOUBLE_EQ(const std::vector<double>& expected, const std::vector<double>& actual );

void EXPECT_VECOTR_COMPLEXDOUBLE_EQ(const std::vector< std::complex<double> >& expected, const std::vector< std::complex<double> >& actual );

#endif //AFQMCLAB_GTEST_CUSTOM_H
