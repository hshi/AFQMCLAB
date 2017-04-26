//
// Created by boruoshihao on 4/16/17.
//

#include "../include/afqmcConstraintPathMethod.h"
#include "../../../../common/testHao/gtest_custom.h"
#include "../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;

void generateAfqmcConstraintPathMethodInputFile(const string &filename)
{
    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}

    writeFile(0.01, file);
    writeFile("particleSpin", file);
    writeFile("constForce", file);
    writeFile(0.8, file);
    writeFile(10, file);
    writeFile(12, file);
    writeFile(996, file);
    writeFile(30, file);
    writeFile(3, file);
    writeFile(6, file);
    writeFile("setFromModel", file);
    writeFile("setRandomly", file);
    writeFile(80, file);
    writeFile(120, file);
    writeFile(3, file);

    file.close();
}

TEST(afqmcConstraintPathMethodTest, readAndBcast)
{
    string filename = "method.dat";
    generateAfqmcConstraintPathMethodInputFile(filename);
    MPIBarrier();

    AfqmcConstraintPathMethod method;
    if( MPIRank()==0 ) method.read(filename);
    MPIBcast(method);

    EXPECT_EQ(0.01, method.dt);
    EXPECT_EQ("particleSpin", method.decompType);
    EXPECT_EQ("constForce", method.forceType);
    EXPECT_EQ(0.8, method.sampleCap);
    EXPECT_EQ(static_cast<size_t>(10), method.stabilizeStep);
    EXPECT_EQ(static_cast<size_t>(12), method.populationControlStep);
    EXPECT_EQ(static_cast<size_t>(996), method.timesliceSize);
    EXPECT_EQ(static_cast<size_t>(30), method.thermalStep);
    EXPECT_EQ(static_cast<size_t>(3), method.measureSkipTimesliceStep);
    EXPECT_EQ(static_cast<size_t>(6), method.writeSkipTimesliceStep);
    EXPECT_EQ("setFromModel", method.initialPhiTFlag);
    EXPECT_EQ("setRandomly", method.initialWalkerFlag);
    EXPECT_EQ(static_cast<size_t>(80), method.setETMaxStep);
    EXPECT_EQ(120, method.walkerSizePerThread);
    EXPECT_EQ(120*MPISize(), method.walkerSize);
    EXPECT_EQ(3, method.seed);

    removeFile(filename);
}