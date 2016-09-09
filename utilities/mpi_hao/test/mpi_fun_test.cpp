#include "gtest/gtest.h"
#include "../include/mpi_fun.h"
#include "../../test_hao/gtest_custom.h"

using namespace std;

#ifdef MPI_HAO

TEST (MPIBcast, int)
{
    int i=0;
    if(MPIRank()==0) i=2;
    MPIBcast(i);

    EXPECT_EQ (2, i);
}

TEST (MPIBcast, long)
{
    long i=0;
    if(MPIRank()==0) i=2;
    MPIBcast(i);

    EXPECT_EQ (2, i);
}

TEST (MPIBcast, longlong)
{
    long long i=0;
    if(MPIRank()==0) i=2;
    MPIBcast(i);

    EXPECT_EQ (2, i);
}

TEST (MPIBcast, size_t)
{
    size_t i=0;
    if(MPIRank()==0) i=2;
    MPIBcast(i);

    EXPECT_EQ (2, i);
}

TEST (MPIBcast, float)
{
    float i=0;
    if(MPIRank()==0) i=2.23;
    MPIBcast(i);

    EXPECT_FLOAT_EQ (2.23, i);
}

TEST (MPIBcast, double)
{
    double i=0;
    if(MPIRank()==0) i=2.23;
    MPIBcast(i);

    EXPECT_DOUBLE_EQ (2.23, i);
}

TEST (MPIBcast, complex_float)
{
    complex<float> i(0,0);
    if(MPIRank()==0) i=complex<float>(2.0, 2.2);
    MPIBcast(i);

    EXPECT_COMPLEXFLOAT_EQ(complex<float>(2.0, 2.2), i);
}

TEST (MPIBcast, complex_double)
{
    complex<double> i(0,0);
    if(MPIRank()==0) i=complex<double>(2.0, 2.2);
    MPIBcast(i);

    EXPECT_COMPLEXDOUBLE_EQ(complex<double>(2.0, 2.2), i);
}

TEST (MPIBcast, int_pointer)
{
    int a[3] = {};
    int b[3] = {1, 2, 3};
    if(MPIRank()==0)
    {
        for(int i=0; i<3; i++) a[i]=b[i];
    }
    MPIBcast(3,a);

    EXPECT_POINTER_EQ(3, b, a);
}

TEST (MPIBcast, double_pointer)
{
    double a[3] = {};
    double b[3] = {1.2, 3.6, 9.8};
    if(MPIRank()==0)
    {
        for(int i=0; i<3; i++) a[i]=b[i];
    }
    MPIBcast(3,a);

    EXPECT_POINTER_DOUBLE_EQ(3, b, a);
}

TEST (MPIBcast, complexdouble_pointer)
{
    complex<double> a[3] = {};
    complex<double> b[3] = { {1.2, 2.3}, {3.6, 7.8}, {9.8, 12.5} };
    if(MPIRank()==0)
    {
        for(int i=0; i<3; i++) a[i]=b[i];
    }
    MPIBcast(3,a);

    EXPECT_POINTER_COMPLEXDOUBLE_EQ(3, b, a);
}

TEST(MPISum, int)
{
    int i    = 2;
    int size = MPISize();
    int sum  = MPISum(i);

    if( MPIRank()==0 ) EXPECT_EQ(i*size, sum);
}

TEST(MPISum, long)
{
    long i    = 2;
    long size = MPISize();
    long sum  = MPISum(i);

    if( MPIRank()==0 ) EXPECT_EQ(i*size, sum);
}

TEST(MPISum, longlong)
{
    long long i    = 2;
    long long size = MPISize();
    long long sum  = MPISum(i);

    if( MPIRank()==0 ) EXPECT_EQ(i*size, sum);
}

TEST(MPISum, float)
{
    float i    = 2.0;
    float size = MPISize();
    float sum  = MPISum(i);

    if( MPIRank()==0 ) EXPECT_FLOAT_EQ(i*size, sum);
}

TEST(MPISum, double)
{
    double i    = 2.0;
    double size = MPISize();
    double sum  = MPISum(i);

    if( MPIRank()==0 ) EXPECT_DOUBLE_EQ(i*size, sum);
}

TEST(MPISum, complex_float)
{
    complex<float> i    ={2.0, 3.0};
    complex<float> size = MPISize();
    complex<float> sum  = MPISum(i);

    if( MPIRank()==0 ) EXPECT_COMPLEXFLOAT_EQ(i*size, sum);
}

TEST(MPISum, complex_double)
{
    complex<double> i    ={2.0, 3.0};
    double size = MPISize();
    complex<double> sum  = MPISum(i);

    if( MPIRank()==0 ) EXPECT_COMPLEXDOUBLE_EQ(i*size, sum);
}

TEST(MPISum, double_pointer)
{
    double s[3] = { 2.22, 3.860, 5.239 };
    double expected[3] = {};
    double actual[3] = {};

    double size = MPISize();
    for (int i = 0; i < 3; ++i)
    {
        expected[i] = s[i] * size;
    }

    MPISum( 3, s, actual );

    if( MPIRank()==0 ) EXPECT_POINTER_DOUBLE_EQ(3, expected , actual);
}


TEST(MPISum, complexdouble_pointer)
{
    complex<double> s[3] = { {2.2, 3.0}, {3, 8.9}, {5.2, 7.111} };
    complex<double> expected[3] = {};
    complex<double> actual[3] = {};

    double size = MPISize();
    for (int i = 0; i < 3; ++i)
    {
        expected[i] = s[i] * size;
    }

    MPISum( 3, s, actual );

    if( MPIRank()==0 ) EXPECT_POINTER_COMPLEXDOUBLE_EQ(3, expected , actual);
}


TEST(MPIGather, double)
{
    double i=MPIRank();
    int size = MPISize();

    double actual[size];
    MPIGather(i,actual);

    double expected[size];
    for (int j = 0; j < size ; ++j)
    {
        expected[j] = j;
    }

    if( MPIRank()==0 ) EXPECT_POINTER_DOUBLE_EQ(size, expected , actual);
}


TEST(MPIGather, complex_double)
{
    complex<double> i( MPIRank()*1.0, MPIRank()*2.0 );
    int size = MPISize();

    complex<double> actual[size];
    MPIGather(i,actual);

    complex<double> expected[size];
    for (int j = 0; j < size ; ++j)
    {
        expected[j] = complex<double>( j, j*2.0 );
    }

    if( MPIRank()==0 ) EXPECT_POINTER_COMPLEXDOUBLE_EQ(size, expected , actual);
}
#else

TEST(MPIFun, serial)
{
    complex<double> buffer(1.9,2.3);
    complex<double> buffer_array[3] = { {1.2, 3.0}, {5.2, 1.0}, {7.0, 8.999} };

    complex<double> expected = buffer;
    complex<double> expected_array[3];
    for(int i=0; i<3; i++) expected_array[i] = buffer_array[i];


    //Test MPISzie and MPIRank
    EXPECT_EQ( 1, MPISize() );
    EXPECT_EQ( 0, MPIRank() );


    //Test MPIBcast
    MPIBcast(buffer);
    EXPECT_COMPLEXDOUBLE_EQ( expected, buffer );
    MPIBcast(3, buffer_array);
    EXPECT_POINTER_COMPLEXDOUBLE_EQ( 3, expected_array, buffer_array );

    //Test MPISum
    buffer = MPISum(buffer);
    EXPECT_COMPLEXDOUBLE_EQ( expected, buffer );
    MPISum( 3, expected_array, buffer_array );
    EXPECT_POINTER_COMPLEXDOUBLE_EQ( 3, expected_array, buffer_array );
}

#endif