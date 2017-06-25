//
// Created by boruoshihao on 6/23/17.
//

#include "../include/afqmcPhaselessMethod.h"

using namespace std;

AfqmcPhaselessMethod::AfqmcPhaselessMethod()
{
    setDefault();
}

AfqmcPhaselessMethod::~AfqmcPhaselessMethod()
{

}

void AfqmcPhaselessMethod::read(const std::string &filename)
{
    readBySearchString(dt, "dt", filename);
    readBySearchString(timesliceSize, "timesliceSize", filename);
    readBySearchString(thermalSize, "thermalSize", filename);
    readBySearchString(measureSkipStep, "measureSkipStep", filename);
    readBySearchString(writeSkipStep, "writeSkipStep", filename);

    readBySearchString(walkerSizePerThread, "walkerSizePerThread", filename);
    walkerSize = walkerSizePerThread*MPISize();

    readBySearchString(forceType, "forceType", filename);
    readBySearchString(forceCap, "forceCap", filename);
    readBySearchString(initialPhiTFlag, "initialPhiTFlag", filename);
    readBySearchString(initialWalkerFlag, "initialWalkerFlag", filename);

    readBySearchString(mgsStep, "mgsStep", filename);
    readBySearchString(isMgsStepAdjustable, "isMgsStepAdjustable", filename);
    readBySearchString(mgsStepTolerance, "mgsStepTolerance", filename);

    readBySearchString(popControlStep, "popControlStep", filename);
    readBySearchString(isPopControlStepAdjustable, "isPopControlStepAdjustable", filename);
    readBySearchString(popControlStepTolerance, "popControlStepTolerance", filename);

    readBySearchString(ET, "ET", filename);
    readBySearchString(isETAndBackGroundAdjustable, "isETAndBackGroundAdjustable", filename);
    readBySearchString(ETAndBackGroundAdjustStep, "ETAndBackGroundAdjustStep", filename);
    readBySearchString(ETAndBackGroundAdjustMaxSize, "ETAndBackGroundAdjustMaxSize", filename);
    readBySearchString(isETAndBackGroundGrowthEstimable, "isETAndBackGroundGrowthEstimable", filename);
    readBySearchString(ETAndBackGroundGrowthEstimateStep, "ETAndBackGroundGrowthEstimateStep", filename);
    readBySearchString(ETAndBackGroundGrowthEstimateSize, "ETAndBackGroundGrowthEstimateSize", filename);

    readBySearchString(seed, "seed", filename);

    analysis();
}

void AfqmcPhaselessMethod::print()
{
    cout<<left<<endl;

    cout<<setw(36)<<"AFQMC parameters: "<<endl;
    cout<<setw(36)<<"dt "<<setw(26)<<dt<<endl;
    cout<<setw(36)<<"timesliceSize "<<setw(26)<<timesliceSize<<endl;
    cout<<setw(36)<<"thermalSize "<<setw(26)<<thermalSize<<endl;
    cout<<setw(36)<<"measureSkipStep "<<setw(26)<<measureSkipStep<<endl;
    cout<<setw(36)<<"writeSkipStep "<<setw(26)<<writeSkipStep<<endl;

    cout<<setw(36)<<"walkerSizePerThread "<<setw(26)<<walkerSizePerThread<<endl;
    cout<<setw(36)<<"walkerSize "<<setw(26)<<walkerSize<<endl;

    cout<<setw(36)<<"forceType "<<setw(26)<<forceType<<endl;
    cout<<setw(36)<<"forceCap "<<setw(26)<<forceCap<<endl;
    cout<<setw(36)<<"initialPhiTFlag "<<setw(26)<<initialPhiTFlag<<endl;
    cout<<setw(36)<<"initialWalkerFlag "<<setw(26)<<initialWalkerFlag<<endl;

    cout<<setw(36)<<"mgsStep "<<setw(26)<<mgsStep<<endl;
    cout<<setw(36)<<"isMgsStepAdjustable "<<setw(26)<<isMgsStepAdjustable<<endl;
    cout<<setw(36)<<"mgsStepTolerance "<<setw(26)<<mgsStepTolerance<<endl;

    cout<<setw(36)<<"popControlStep "<<setw(26)<<popControlStep<<endl;
    cout<<setw(36)<<"isPopControlStepAdjustable "<<setw(26)<<isPopControlStepAdjustable<<endl;
    cout<<setw(36)<<"popControlStepTolerance "<<setw(26)<<popControlStepTolerance<<endl;

    cout<<setw(36)<<"ET "<<setw(26)<<ET<<endl;
    cout<<setw(36)<<"isETAndBackGroundAdjustable "<<setw(26)<<isETAndBackGroundAdjustable<<endl;
    cout<<setw(36)<<"ETAndBackGroundAdjustStep "<<setw(26)<<ETAndBackGroundAdjustStep<<endl;
    cout<<setw(36)<<"ETAndBackGroundAdjustMaxSize "<<setw(26)<<ETAndBackGroundAdjustMaxSize<<endl;
    cout<<setw(36)<<"isETAndBackGroundGrowthEstimable "<<setw(26)<<isETAndBackGroundGrowthEstimable<<endl;
    cout<<setw(36)<<"ETAndBackGroundGrowthEstimateStep "<<setw(26)<<ETAndBackGroundGrowthEstimateStep<<endl;
    cout<<setw(36)<<"ETAndBackGroundGrowthEstimateSize "<<setw(26)<<ETAndBackGroundGrowthEstimateSize<<endl;

    cout<<setw(36)<<"seed "<<setw(26)<<seed<<endl;

    cout<<endl;

}

#ifdef MPI_HAO
void MPIBcast(AfqmcPhaselessMethod &buffer, int root, MPI_Comm const &comm)
{
    MPIBcast(buffer.dt);
    MPIBcast(buffer.timesliceSize);
    MPIBcast(buffer.thermalSize);
    MPIBcast(buffer.measureSkipStep);
    MPIBcast(buffer.writeSkipStep);

    MPIBcast(buffer.walkerSizePerThread);
    MPIBcast(buffer.walkerSize);

    MPIBcast(buffer.forceType);
    MPIBcast(buffer.forceCap);
    MPIBcast(buffer.initialPhiTFlag);
    MPIBcast(buffer.initialWalkerFlag);

    MPIBcast(buffer.mgsStep);
    MPIBcast(buffer.isMgsStepAdjustable);
    MPIBcast(buffer.mgsStepTolerance);

    MPIBcast(buffer.popControlStep);
    MPIBcast(buffer.isPopControlStepAdjustable);
    MPIBcast(buffer.popControlStepTolerance);

    MPIBcast(buffer.ET);
    MPIBcast(buffer.isETAndBackGroundAdjustable);
    MPIBcast(buffer.ETAndBackGroundAdjustStep);
    MPIBcast(buffer.ETAndBackGroundAdjustMaxSize);
    MPIBcast(buffer.isETAndBackGroundGrowthEstimable);
    MPIBcast(buffer.ETAndBackGroundGrowthEstimateStep);
    MPIBcast(buffer.ETAndBackGroundGrowthEstimateSize);

    MPIBcast(buffer.seed);
}
#endif

void AfqmcPhaselessMethod::setDefault()
{
    dt = 0.01;
    timesliceSize = 6600;
    thermalSize = 600;
    measureSkipStep = 5;
    writeSkipStep = 100;

    walkerSizePerThread = 300;
    walkerSize = walkerSizePerThread * MPISize();

    forceType="dynamicForce";
    forceCap = 1.5;
    initialPhiTFlag = "readFromFile";
    initialWalkerFlag = "readFromFile";

    mgsStep = 10;
    isMgsStepAdjustable = true;
    mgsStepTolerance = 1e-6;

    popControlStep = 10;
    isPopControlStepAdjustable = true;
    popControlStepTolerance = 3.0;

    ET = -10;
    isETAndBackGroundAdjustable = true;
    ETAndBackGroundAdjustStep = 10;
    ETAndBackGroundAdjustMaxSize = 200;
    isETAndBackGroundGrowthEstimable = true;
    ETAndBackGroundGrowthEstimateStep = 5;
    ETAndBackGroundGrowthEstimateSize = 400;

    seed = 985456376;
}

void AfqmcPhaselessMethod::analysis()
{
    if( dt <= 0.0 )
    {
        cout<<"Error!!! dt must be postive!"<<endl;
        exit(1);
    }

    if( thermalSize > timesliceSize )
    {
        cout<<"Warning!!! thermalSize is larger than timesliceSize!"<<endl;
    }

    if( (timesliceSize-thermalSize)%writeSkipStep != 0 )
    {
        size_t numberOfWrite=(timesliceSize-thermalSize)/writeSkipStep;
        size_t suggestTimesliceSize= writeSkipStep*numberOfWrite+thermalSize;
        cout<<"Warning!!! (timesliceSize-thermalSize)%writeSkipStep is not zero!"<<endl;
        cout<<"To avoid unnecessary projection step, the suggested timesliceSize is "<<suggestTimesliceSize<<endl;
    }

    if( writeSkipStep%measureSkipStep != 0 )
    {
        cout<<"Error!!! writeSkipStep%measureSkipStep is not zero!"<<endl;
        exit(1);
    }

    if( walkerSizePerThread <= 0 )
    {
        cout<<"Error!!! walkerSizePerThread is not a positive number!"<<endl;
        exit(1);
    }

    if( forceCap < 0.0 )
    {
        cout<<"Error!!! forceCap must be positive or zero!"<<endl;
        exit(1);
    }

    if( isMgsStepAdjustable )
    {
        if( mgsStepTolerance<0 )
        {
            cout<<"Error!!! mgsStepTolerance is not a positive number!"<<endl;
            exit(1);
        }
    }

    if( isPopControlStepAdjustable )
    {
        if( popControlStep<0 )
        {
            cout<<"Error!!! popControlStep is not a positive number!"<<endl;
            exit(1);
        }
    }


}

