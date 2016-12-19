//
// Created by boruoshihao on 12/17/16.
//

#include <iostream>
#include "../include/readWriteHao.h"
#include "../../testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(readWriteHaoTest, checkFile)
{
    string filename = "readWriteTest.dat";
    removeFile(filename);
    EXPECT_FALSE( checkFile(filename) );

    MPIBarrier();
    if( MPIRank() == 0 ) system("touch readWriteTest.dat");
    MPIBarrier();

    EXPECT_TRUE( checkFile(filename) );
    removeFile(filename);
}

TEST(readWriteHaoTest, readWriteDouble)
{
    string filename = "readWriteTest.dat";
    double a, b;
    a = 0.23567;
    writeFile(a, filename);
    readFile(b, filename);
    removeFile(filename);
    EXPECT_EQ(a, b);
}

TEST(readWriteHaoTest, readWriteDoublePointer)
{
    string filename = "readWriteTest.dat";
    double a[10], b[10];
    for(size_t i = 0; i < 10; ++i) a[i] =  i*0.2;

    writeFile(10, a, filename);
    readFile(10, b, filename);
    removeFile(filename);

    EXPECT_POINTER_DOUBLE_EQ(10, a, b);
}

TEST(readWriteHaoTest, readWriteDoubleTwoPointer)
{
    string filename = "readWriteTest.dat";
    double a1[10], a2[10], b1[10], b2[10];
    for(size_t i = 0; i < 10; ++i) { a1[i] =  i*0.2; a2[i] =  i*0.3; }

    writeFile(10, a1, a2, filename);
    readFile(10, b1, b2, filename);
    removeFile(filename);

    EXPECT_POINTER_DOUBLE_EQ(10, a1, b1);
    EXPECT_POINTER_DOUBLE_EQ(10, a2, b2);
}

TEST(readWriteHaoTest, readWriteComplexDouble)
{
    string filename = "readWriteTest.dat";
    complex<double> a, b;
    a = complex<double> (0.23567, 2.335);
    writeFile(a, filename);
    readFile(b, filename);
    removeFile(filename);
    EXPECT_COMPLEXDOUBLE_EQ(a, b);
}

TEST(readWriteHaoTest, readWriteComplexDoublePointer)
{
    string filename = "readWriteTest.dat";
    complex<double> a[10], b[10];
    for(size_t i = 0; i < 10; ++i) a[i] =  complex<double>(i*0.2, i*0.3);

    writeFile(10, a, filename);
    readFile(10, b, filename);
    removeFile(filename);

    EXPECT_POINTER_COMPLEXDOUBLE_EQ(10, a, b);
}

TEST(readWriteHaoTest, readWriteComplexDoubleTwoPointer)
{
    string filename = "readWriteTest.dat";
    complex<double> a1[10], a2[10], b1[10], b2[10];
    for(size_t i = 0; i < 10; ++i) { a1[i] =  complex<double>(i*0.2, i*0.3); a2[i] =  complex<double>(i*0.3, i*0.4); }

    writeFile(10, a1, a2, filename);
    readFile(10, b1, b2, filename);
    removeFile(filename);

    EXPECT_POINTER_COMPLEXDOUBLE_EQ(10, a1, b1);
    EXPECT_POINTER_COMPLEXDOUBLE_EQ(10, a2, b2);
}