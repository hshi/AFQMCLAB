//
// Created by boruoshihao on 5/31/17.
//
#include <iostream>
#include "../../testHao/gtest_custom.h"
#include "../../mpiHao/include/mpi_fun.h"
#include "../include/readWriteStringFile.h"
#include "../include/readWriteHdf5.h"

using namespace std;
using namespace H5;

TEST(readWriteHdf5Test, readWriteSize_t)
{
    size_t dataWrite(18), dataRead(0);
    string fileName("file.h5"), dataSetName("dset");

    if( MPIRank()==0 )
    {
        H5File file(fileName, H5F_ACC_TRUNC);
        //Use two writeFile to test remove function.
        writeFile(dataWrite, file, dataSetName);
        writeFile(dataWrite, file, dataSetName);
        file.close();
    }
    MPIBarrier();

    H5File file(fileName, H5F_ACC_RDONLY);
    readFile(dataRead, file, dataSetName);
    file.close();

    EXPECT_EQ(dataRead, dataWrite);

    removeFile(fileName);
}

TEST(readWriteHdf5Test, readWriteDouble)
{
    double dataWrite(2.3), dataRead(0.0);
    string fileName("file.h5"), dataSetName("dset");

    if( MPIRank()==0 )
    {
        H5File file(fileName, H5F_ACC_TRUNC);
        writeFile(dataWrite, file, dataSetName);
        writeFile(dataWrite, file, dataSetName);
        file.close();
    }
    MPIBarrier();

    H5File file(fileName, H5F_ACC_RDONLY);
    readFile(dataRead, file, dataSetName);
    file.close();

    EXPECT_DOUBLE_EQ(dataRead, dataWrite);

    removeFile(fileName);
}

TEST(readWriteHdf5Test, readWriteComplexDouble)
{
    complex<double> dataWrite(2.3,3.1), dataRead(0.0,0.0);
    string fileName("file.h5"), dataSetName("dset");

    if( MPIRank()==0 )
    {
        H5File file(fileName, H5F_ACC_TRUNC);
        writeFile(dataWrite, file, dataSetName);
        writeFile(dataWrite, file, dataSetName);
        file.close();
    }
    MPIBarrier();

    H5File file(fileName, H5F_ACC_RDONLY);
    readFile(dataRead, file, dataSetName);
    file.close();

    EXPECT_COMPLEXDOUBLE_EQ(dataRead, dataWrite);

    removeFile(fileName);
}

TEST(readWriteHdf5Test, readWriteSize_tArray)
{
    size_t L=10;
    vector<size_t> dataWrite(L), dataRead(L);
    for(size_t i = 0; i < L; ++i) dataWrite[i] = i;
    string fileName("file.h5"), dataSetName("dset");

    if( MPIRank()==0 )
    {
        H5File file(fileName, H5F_ACC_TRUNC);
        writeFile(L, dataWrite.data(), file, dataSetName);
        writeFile(L, dataWrite.data(), file, dataSetName);
        file.close();
    }
    MPIBarrier();

    H5File file(fileName, H5F_ACC_RDONLY);
    readFile(L, dataRead.data(), file, dataSetName);
    file.close();

    EXPECT_EQ(dataRead, dataWrite);

    removeFile(fileName);
}

TEST(readWriteHdf5Test, readWriteDoubleArray)
{
    size_t L=10;
    vector<double> dataWrite(L), dataRead(L);
    for(size_t i = 0; i < L; ++i) dataWrite[i] = i+2.333;
    string fileName("file.h5"), dataSetName("dset");

    if( MPIRank()==0 )
    {
        H5File file(fileName, H5F_ACC_TRUNC);
        writeFile(L, dataWrite.data(), file, dataSetName);
        writeFile(L, dataWrite.data(), file, dataSetName);
        file.close();
    }
    MPIBarrier();

    H5File file(fileName, H5F_ACC_RDONLY);
    readFile(L, dataRead.data(), file, dataSetName);
    file.close();

    EXPECT_VECOTR_DOUBLE_EQ(dataRead, dataWrite);

    removeFile(fileName);
}

TEST(readWriteHdf5Test, readWriteComplexDoubleArray)
{
    size_t L=10;
    vector<complex<double>> dataWrite(L), dataRead(L);
    for(size_t i = 0; i < L; ++i) dataWrite[i] = complex<double>(i,i+2.12);
    string fileName("file.h5"), dataSetName("dset");

    if( MPIRank()==0 )
    {
        H5File file(fileName, H5F_ACC_TRUNC);
        writeFile(L, dataWrite.data(), file, dataSetName);
        writeFile(L, dataWrite.data(), file, dataSetName);
        file.close();
    }
    MPIBarrier();

    H5File file(fileName, H5F_ACC_RDONLY);
    readFile(L, dataRead.data(), file, dataSetName);
    file.close();

    EXPECT_VECOTR_COMPLEXDOUBLE_EQ(dataRead, dataWrite);

    removeFile(fileName);
}