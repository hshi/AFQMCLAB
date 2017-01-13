//
// Created by boruoshihao on 1/13/17.
//

#include "../include/writeThreadSum.h"
#include "../../../../common/testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(writeThreadSumTest, complexDouble)
{
    string filename="out.dat";

    int rank = MPIRank();
    int size = MPISize();
    complex<double> data( rank, 2.0*rank );
    complex<double> sumExact(0,0);
    for(int i=0; i<size; i++) sumExact += complex<double>(i, 2.0*i);

    writeThreadSum(data, filename);
    MPIBarrier();

    complex<double> sum(1000,200);
    readFile(sum, filename);
    EXPECT_COMPLEXDOUBLE_EQ(sum, sumExact);

    removeFile(filename);
}

TEST(writeThreadSumTest, complexDoubleArray)
{
    string filename="out.dat";

    double size = MPISize();
    complex<double> data[3]={ complex<double>(2.0, 3.0),  complex<double>(1.0, 3.0), complex<double>(1.0, 1.0) } ;
    complex<double> sumExact[3] = { size*data[0], size*data[1], size*data[2] };

    writeThreadSum(3, data, filename);
    MPIBarrier();

    complex<double> sum[3];
    readFile(3, sum, filename);
    EXPECT_POINTER_COMPLEXDOUBLE_EQ(3, sum, sumExact);

    removeFile(filename);
}