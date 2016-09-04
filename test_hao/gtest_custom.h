//
// Created by boruoshihao on 9/2/16.
//

#ifndef AFQMCLIB_GTEST_CUSTOM_H
#define AFQMCLIB_GTEST_CUSTOM_H

#include <complex>
#include <cmath>
#include "gtest/gtest.h"

void EXPECT_COMPLEXFLOAT_EQ (std::complex<float> expected, std::complex<float> actual);

void EXPECT_COMPLEXDOUBLE_EQ (std::complex<double> expected, std::complex<double> actual);

template<typename T>
void EXPECT_POINTER_EQ(size_t L,  T * expected, T * actual )
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

void EXPECT_POINTER_DOUBLE_EQ(size_t L,  double * expected, double * actual );

void EXPECT_POINTER_COMPLEXDOUBLE_EQ(size_t L,  std::complex<double> * expected, std::complex<double> * actual );

#endif //AFQMCLIB_GTEST_CUSTOM_H
