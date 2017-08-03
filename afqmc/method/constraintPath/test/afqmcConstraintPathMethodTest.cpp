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

    writeFile("dt = 0.02", file);
    writeFile("thermalSize = 1000", file);
    writeFile("writeNumber = 30", file);
    writeFile("measureSkipStep = 20", file);
    writeFile("writeSkipStep = 100", file);
    
    writeFile("walkerSizePerThread = 200", file);

    writeFile("decompType = densityCharge", file);
    writeFile("forceType = constForce", file);
    writeFile("forceCap = 0.5", file);
    writeFile("initialPhiTFlag = setRandomly", file);
    writeFile("initialWalkerFlag = setRandomly", file);
    
    writeFile("mgsStep = 20", file);
    writeFile("popControlStep = 50", file);

    writeFile("ET = -18.0", file);
    writeFile("ETAdjustStep = 20", file);
    writeFile("ETAdjustMaxSize = 120", file);

    writeFile("seed = 77", file);

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

    EXPECT_DOUBLE_EQ( method.dt, 0.02 );
    EXPECT_EQ( method.thermalSize, static_cast<size_t>(1000) );
    EXPECT_EQ( method.writeNumber, static_cast<size_t>(30) );
    EXPECT_EQ( method.measureSkipStep, static_cast<size_t>(20) );
    EXPECT_EQ( method.writeSkipStep, static_cast<size_t>(100) );

    EXPECT_EQ( method.walkerSizePerThread, 200 );
    EXPECT_EQ( method.walkerSize, 200*MPISize() );

    EXPECT_EQ( method.decompType, "densityCharge" );
    EXPECT_EQ( method.forceType, "constForce" );
    EXPECT_DOUBLE_EQ( method.forceCap, 0.5 );
    EXPECT_EQ( method.initialPhiTFlag, "setRandomly" );
    EXPECT_EQ( method.initialWalkerFlag, "setRandomly" );

    EXPECT_EQ( method.mgsStep, static_cast<size_t>(20) );
    EXPECT_EQ( method.popControlStep, static_cast<size_t>(50) );

    EXPECT_DOUBLE_EQ( method.ET, -18.0 );
    EXPECT_EQ( method.ETAdjustStep, static_cast<size_t>(20) );
    EXPECT_EQ( method.ETAdjustMaxSize, static_cast<size_t>(120) );

    EXPECT_EQ( method.seed, 77);

    if( MPIRank()==0 ) method.print();

    removeFile(filename);
}