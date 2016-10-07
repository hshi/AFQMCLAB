//
// Created by boruoshihao on 9/2/16.
//
#include "gtest_custom.h"

using namespace std;

float  lit_float  = 1e-5;
double lit_double = 1e-12;

void EXPECT_COMPLEXFLOAT_EQ (complex<float> expected, complex<float> actual)
{
    EXPECT_FLOAT_EQ( expected.real(), actual.real() );
    EXPECT_FLOAT_EQ( expected.imag(), actual.imag() );
}

void EXPECT_COMPLEXDOUBLE_EQ (complex<double> expected, complex<double> actual)
{
    EXPECT_DOUBLE_EQ( expected.real(), actual.real() );
    EXPECT_DOUBLE_EQ( expected.imag(), actual.imag() );
}

void EXPECT_POINTER_DOUBLE_EQ(size_t L, const double *expected, const double *actual)
{
    ::testing::AssertionResult results = ::testing::AssertionSuccess();

    for(size_t i=0; i<L; i++)
    {
        if( abs( expected[i] - actual[i] ) > lit_double )
        {
            results = ::testing::AssertionFailure() << " expected[" << i
                                                    << "] (" << expected[i] << ") != actual[" << i
                                                    << "] (" << actual[i] << ") ";
            break;
        }
    }
        EXPECT_TRUE( results );
}

void EXPECT_POINTER_COMPLEXDOUBLE_EQ(size_t L, const complex<double> *expected, const complex<double> *actual)
{
    ::testing::AssertionResult results = ::testing::AssertionSuccess();

    for(size_t i=0; i<L; i++)
    {
        if( abs( expected[i] - actual[i] ) > lit_double )
        {
            results = ::testing::AssertionFailure() << " expected[" << i
                                                    << "] (" << expected[i] << ") != actual[" << i
                                                    << "] (" << actual[i] << ") ";
            break;
        }
    }
    EXPECT_TRUE( results );
}

void EXPECT_VECOTR_DOUBLE_EQ(const vector<double>& expected, const vector<double>& actual )
{
    EXPECT_EQ( expected.size(), actual.size() );
    EXPECT_POINTER_DOUBLE_EQ( expected.size(), expected.data(), actual.data() );
}

void EXPECT_VECOTR_COMPLEXDOUBLE_EQ(const vector< complex<double> >& expected, const vector< complex<double> >& actual )
{
    EXPECT_EQ( expected.size(), actual.size() );
    EXPECT_POINTER_COMPLEXDOUBLE_EQ( expected.size(), expected.data(), actual.data() );
}