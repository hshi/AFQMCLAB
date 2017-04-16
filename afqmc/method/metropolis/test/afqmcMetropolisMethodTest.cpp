//
// Created by boruoshihao on 1/15/17.
//

#include "../include/afqmcMetropolisMethod.h"
#include "../../../../common/testHao/gtest_custom.h"
#include "../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;

void generateAfqmcMetropolisMethodInputFile(const string &filename)
{
    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}

    writeFile(0.01, file);
    writeFile("particleSpin", file);
    writeFile("constForce", file);
    writeFile(0.8, file);
    writeFile(10, file);
    writeFile(50, file);
    writeFile(2, file);
    writeFile(10, file);
    writeFile(6400, file);
    writeFile(32, file);
    writeFile("setFromModel", file);
    writeFile("dynamicForceInitial", file);
    writeFile("commute", file);
    writeFile("normal", file);
    writeFile(2.0, file);
    writeFile(1000, file);
    writeFile(20, file);
    writeFile(1799, file);
    writeFile(1799, file);
    writeFile(3, file);

    file.close();
}

TEST(afqmcMetropolisMethodTest, readAndBcast)
{
    string filename = "method.dat";
    generateAfqmcMetropolisMethodInputFile(filename);
    MPIBarrier();

    AfqmcMetropolisMethod method;
    if( MPIRank()==0 ) method.read(filename);
    MPIBcast(method);
    EXPECT_EQ(0.01, method.dt);
    EXPECT_EQ("particleSpin", method.decompType);
    EXPECT_EQ("constForce", method.forceType);
    EXPECT_EQ(0.8, method.sampleCap);
    EXPECT_EQ(static_cast<size_t>(10), method.thermalSweep);
    EXPECT_EQ(static_cast<size_t>(50), method.measureSweep);
    EXPECT_EQ(static_cast<size_t>(2), method.writeSweep);
    EXPECT_EQ(static_cast<size_t>(10), method.stabilizeStep);
    EXPECT_EQ(static_cast<size_t>(6400), method.timesliceSize);
    EXPECT_EQ(static_cast<size_t>(32), method.timesliceBlockSize);
    EXPECT_EQ(static_cast<size_t>(200), method.timesliceBlockNumber);
    EXPECT_EQ("setFromModel", method.initialWalkerFlag);
    EXPECT_EQ("dynamicForceInitial", method.initialAuxiliaryFlag);
    EXPECT_EQ("commute", method.measureType);
    EXPECT_EQ("normal", method.measureVarianceType);
    EXPECT_EQ(2.0, method.secondOrderCap);
    EXPECT_EQ(static_cast<size_t>(1000), method.twoBodySampleSize);
    EXPECT_EQ(static_cast<size_t>(20), method.measureSkipTimesliceStep);
    EXPECT_EQ(static_cast<size_t>(1799), method.measureSkipTimesliceLeft);
    EXPECT_EQ(static_cast<size_t>(1799), method.measureSkipTimesliceRight);
    EXPECT_EQ(3, method.seed);

    removeFile(filename);
}