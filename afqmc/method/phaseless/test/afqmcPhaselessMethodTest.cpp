//
// Created by boruoshihao on 6/23/17.
//
#include "../include/afqmcPhaselessMethod.h"
#include "../../../../common/testHao/gtest_custom.h"
#include "../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;

void generateAfqmcPhaselessMethodInputFile(const string &filename)
{
    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}

    writeFile("dt = 0.02", file);
    writeFile("timesliceSize = 8000", file);
    writeFile("thermalSize = 1000", file);
    writeFile("measureSkipStep = 20", file);
    writeFile("writeSkipStep = 100", file);
    writeFile("walkerSizePerThread = 200", file);
    writeFile("forceType = constForce", file);
    writeFile("forceCap = 0.5", file);
    writeFile("initialPhiTFlag = setRandomly", file);
    writeFile("initialWalkerFlag = setRandomly", file);
    writeFile("mgsStep = 20", file);
    writeFile("isMgsStepAdjustable = true", file);
    writeFile("mgsStepTolerance = 0.3", file);
    writeFile("popControlStep = 50", file);
    writeFile("isPopControlStepAdjustable = true", file);
    writeFile("popControlStepTolerance = 0.22", file);
    writeFile("ET = -18.0", file);
    writeFile("isETAndBackGroundAdjustable = true", file);
    writeFile("ETAndBackGroundAdjustStep = 20", file);
    writeFile("ETAndBackGroundAdjustMaxSize = 120", file);
    writeFile("isETAndBackGroundGrowthEstimable = true", file);
    writeFile("ETAndBackGroundGrowthEstimateStep = 20", file);
    writeFile("ETAndBackGroundGrowthEstimateSize = 200", file);
    writeFile("seed = 77", file);

    file.close();
}

TEST(afqmcConstraintPathMethodTest, readAndBcast)
{
    string filename = "method.dat";
    generateAfqmcPhaselessMethodInputFile(filename);
    MPIBarrier();

    AfqmcPhaselessMethod method;
    if( MPIRank()==0 ) method.read(filename);
    MPIBcast(method);

    EXPECT_EQ( method.dt, 0.02 );
    EXPECT_EQ( method.timesliceSize, static_cast<size_t>(8000) );
    EXPECT_EQ( method.thermalSize, static_cast<size_t>(1000) );
    EXPECT_EQ( method.measureSkipStep, static_cast<size_t>(20) );
    EXPECT_EQ( method.writeSkipStep, static_cast<size_t>(100) );

    EXPECT_EQ( method.walkerSizePerThread, 200 );
    EXPECT_EQ( method.walkerSize, 200*MPISize() );

    EXPECT_EQ( method.forceType, "constForce" );
    EXPECT_EQ( method.forceCap, 0.5 );
    EXPECT_EQ( method.initialPhiTFlag, "setRandomly" );
    EXPECT_EQ( method.initialWalkerFlag, "setRandomly" );

    EXPECT_EQ( method.mgsStep, static_cast<size_t>(20) );
    EXPECT_EQ( method.isMgsStepAdjustable, true );
    EXPECT_EQ( method.mgsStepTolerance, 0.3 );

    EXPECT_EQ( method.popControlStep, static_cast<size_t>(50) );
    EXPECT_EQ( method.isPopControlStepAdjustable, true );
    EXPECT_EQ( method.popControlStepTolerance, 0.22) ;

    EXPECT_EQ( method.ET, -18.0 );
    EXPECT_EQ( method.isETAndBackGroundAdjustable, true );
    EXPECT_EQ( method.ETAndBackGroundAdjustStep, static_cast<size_t>(20) );
    EXPECT_EQ( method.ETAndBackGroundAdjustMaxSize, static_cast<size_t>(120) );
    EXPECT_EQ( method.isETAndBackGroundGrowthEstimable, true );
    EXPECT_EQ( method.ETAndBackGroundGrowthEstimateStep, static_cast<size_t>(20) );
    EXPECT_EQ( method.ETAndBackGroundGrowthEstimateSize, static_cast<size_t>(200) );

    EXPECT_EQ( method.seed, 77);

    if( MPIRank()==0 ) method.print();
    removeFile(filename);
}