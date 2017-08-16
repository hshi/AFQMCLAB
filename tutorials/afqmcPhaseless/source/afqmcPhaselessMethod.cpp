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
    readBySearchString(thermalSize, "thermalSize", filename);
    readBySearchString(writeNumber, "writeNumber", filename);
    readBySearchString(measureNumberPerWrite, "measureNumberPerWrite", filename);
    readBySearchString(measureSkipStep, "measureSkipStep", filename);

    readBySearchString(walkerSizePerThread, "walkerSizePerThread", filename);
    walkerSize = walkerSizePerThread*MPISize();

    readBySearchString(forceType, "forceType", filename);
    readBySearchString(forceCap, "forceCap", filename);
    readBySearchString(initialPhiTFlag, "initialPhiTFlag", filename);
    readBySearchString(initialWalkerFlag, "initialWalkerFlag", filename);

    readBySearchString(mgsStep, "mgsStep", filename);
    readBySearchString(popControlStep, "popControlStep", filename);

    readBySearchString(ET, "ET", filename);
    readBySearchString(ETAndBackGroundAdjustStep, "ETAndBackGroundAdjustStep", filename);
    readBySearchString(ETAndBackGroundAdjustMaxSize, "ETAndBackGroundAdjustMaxSize", filename);
    readBySearchString(ETAndBackGroundGrowthEstimateStep, "ETAndBackGroundGrowthEstimateStep", filename);
    readBySearchString(ETAndBackGroundGrowthEstimateMaxSize, "ETAndBackGroundGrowthEstimateMaxSize", filename);

    readBySearchString(seed, "seed", filename);

    analysis();
}

void AfqmcPhaselessMethod::write(const std::string &filename)
{
    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}

    file<<left<<endl;

    file<<setw(36)<<"dt "<<setw(26)<<dt<<endl;
    file<<setw(36)<<"thermalSize "<<setw(26)<<thermalSize<<endl;
    file<<setw(36)<<"writeNumber "<<setw(26)<<writeNumber<<endl;
    file<<setw(36)<<"measureNumberPerWrite "<<setw(26)<<measureNumberPerWrite<<endl;
    file<<setw(36)<<"measureSkipStep "<<setw(26)<<measureSkipStep<<endl;
    file<<endl;

    file<<setw(36)<<"walkerSizePerThread "<<setw(26)<<walkerSizePerThread<<endl;
    file<<endl;

    file<<setw(36)<<"forceType "<<setw(26)<<forceType<<endl;
    file<<setw(36)<<"forceCap "<<setw(26)<<forceCap<<endl;
    file<<setw(36)<<"initialPhiTFlag "<<setw(26)<<initialPhiTFlag<<endl;
    file<<setw(36)<<"initialWalkerFlag "<<setw(26)<<initialWalkerFlag<<endl;
    file<<endl;

    file<<setw(36)<<"mgsStep "<<setw(26)<<mgsStep<<endl;
    file<<setw(36)<<"popControlStep "<<setw(26)<<popControlStep<<endl;
    file<<endl;

    file<<setw(36)<<"ET "<<setw(26)<<ET<<endl;
    file<<setw(36)<<"ETAndBackGroundAdjustStep "<<setw(26)<<ETAndBackGroundAdjustStep<<endl;
    file<<setw(36)<<"ETAndBackGroundAdjustMaxSize "<<setw(26)<<ETAndBackGroundAdjustMaxSize<<endl;
    file<<setw(36)<<"ETAndBackGroundGrowthEstimateStep "<<setw(26)<<ETAndBackGroundGrowthEstimateStep<<endl;
    file<<setw(36)<<"ETAndBackGroundGrowthEstimateMaxSize "<<setw(26)<<ETAndBackGroundGrowthEstimateMaxSize<<endl;
    file<<endl;

    file<<setw(36)<<"seed "<<setw(26)<<seed<<endl;
    file<<endl;

    file.close();
}

void AfqmcPhaselessMethod::print()
{
    cout<<left<<endl;

    cout<<setw(36)<<"AFQMC parameters: \n"<<endl;

    cout<<setw(36)<<"dt "<<setw(26)<<dt<<endl;
    cout<<setw(36)<<"thermalSize "<<setw(26)<<thermalSize<<endl;
    cout<<setw(36)<<"writeNumber "<<setw(26)<<writeNumber<<endl;
    cout<<setw(36)<<"measureNumberPerWrite "<<setw(26)<<measureNumberPerWrite<<endl;
    cout<<setw(36)<<"measureSkipStep "<<setw(26)<<measureSkipStep<<endl;
    cout<<endl;

    cout<<setw(36)<<"walkerSizePerThread "<<setw(26)<<walkerSizePerThread<<endl;
    cout<<setw(36)<<"walkerSize "<<setw(26)<<walkerSize<<endl;
    cout<<endl;

    cout<<setw(36)<<"forceType "<<setw(26)<<forceType<<endl;
    cout<<setw(36)<<"forceCap "<<setw(26)<<forceCap<<endl;
    cout<<setw(36)<<"initialPhiTFlag "<<setw(26)<<initialPhiTFlag<<endl;
    cout<<setw(36)<<"initialWalkerFlag "<<setw(26)<<initialWalkerFlag<<endl;
    cout<<endl;

    cout<<setw(36)<<"mgsStep "<<setw(26)<<mgsStep<<endl;
    cout<<setw(36)<<"popControlStep "<<setw(26)<<popControlStep<<endl;
    cout<<endl;

    cout<<setw(36)<<"ET "<<setw(26)<<ET<<endl;
    cout<<setw(36)<<"ETAndBackGroundAdjustStep "<<setw(26)<<ETAndBackGroundAdjustStep<<endl;
    cout<<setw(36)<<"ETAndBackGroundAdjustMaxSize "<<setw(26)<<ETAndBackGroundAdjustMaxSize<<endl;
    cout<<setw(36)<<"ETAndBackGroundGrowthEstimateStep "<<setw(26)<<ETAndBackGroundGrowthEstimateStep<<endl;
    cout<<setw(36)<<"ETAndBackGroundGrowthEstimateMaxSize "<<setw(26)<<ETAndBackGroundGrowthEstimateMaxSize<<endl;
    cout<<endl;

    cout<<setw(36)<<"seed "<<setw(26)<<seed<<endl;
    cout<<endl;
}

#ifdef MPI_HAO
void MPIBcast(AfqmcPhaselessMethod &buffer, int root, MPI_Comm const &comm)
{
    MPIBcast(buffer.dt);
    MPIBcast(buffer.thermalSize);
    MPIBcast(buffer.writeNumber);
    MPIBcast(buffer.measureNumberPerWrite);
    MPIBcast(buffer.measureSkipStep);

    MPIBcast(buffer.walkerSizePerThread);
    MPIBcast(buffer.walkerSize);

    MPIBcast(buffer.forceType);
    MPIBcast(buffer.forceCap);
    MPIBcast(buffer.initialPhiTFlag);
    MPIBcast(buffer.initialWalkerFlag);

    MPIBcast(buffer.mgsStep);
    MPIBcast(buffer.popControlStep);

    MPIBcast(buffer.ET);
    MPIBcast(buffer.ETAndBackGroundAdjustStep);
    MPIBcast(buffer.ETAndBackGroundAdjustMaxSize);
    MPIBcast(buffer.ETAndBackGroundGrowthEstimateStep);
    MPIBcast(buffer.ETAndBackGroundGrowthEstimateMaxSize);

    MPIBcast(buffer.seed);
}
#endif

void AfqmcPhaselessMethod::setDefault()
{
    dt=0.01;
    thermalSize = 200;
    writeNumber = 60;
    measureNumberPerWrite = 2;
    measureSkipStep = 5;

    walkerSizePerThread = 300 / MPISize();
    walkerSize = walkerSizePerThread * MPISize();

    forceType="dynamicForce";
    forceCap = 1.5;
    initialPhiTFlag = "readFromFile";
    initialWalkerFlag = "readFromFile";

    mgsStep = 10;
    popControlStep = 10;

    ET = -10;
    ETAndBackGroundAdjustStep = 10;
    ETAndBackGroundAdjustMaxSize = 100;
    ETAndBackGroundGrowthEstimateStep = 5;
    ETAndBackGroundGrowthEstimateMaxSize = 200;

    seed = 985456376;
}

void AfqmcPhaselessMethod::analysis()
{
    if( std::abs(dt) < 1e-12 )
    {
        cout<<"The code will measure everything without projection!"<<endl;
        return;
    }

    if( dt < 0.0 )
    {
        cout<<"Error!!! dt must be postive!"<<endl;
        exit(1);
    }

    if( writeNumber==0 )
    {
        cout<<"Warning!!! writeNumber = 0, code will not write any measurement to disk!"<<endl;
    }

    if( measureNumberPerWrite == 0 )
    {
        cout<<"Error!!! measureNumberPerWrite = 0, code will not measure anything!"<<endl;
        exit(1);
    }

    if( measureSkipStep ==0 )
    {
        cout<<"Error!!! measureSkipStep ==0, code will not measure anything!"<<endl;
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

    if( ETAndBackGroundAdjustMaxSize > thermalSize )
    {
        cout << "Error!!! We should not adjust ET and backGround after thermalizing!" << endl;
        exit(1);
    }

    if( ETAndBackGroundGrowthEstimateMaxSize > thermalSize )
    {
        cout<<"Error!!! We should not use growth estimator to adjust ET and backGround after thermalizing!"<<endl;
        exit(1);
    }

    if( ETAndBackGroundAdjustMaxSize >= ETAndBackGroundGrowthEstimateMaxSize )
    {
        cout<<"ETAndBackGroundGrowthEstimator is off!"<<endl;
    }
    else
    {
        size_t numberOfMeasure=(ETAndBackGroundGrowthEstimateMaxSize-ETAndBackGroundAdjustMaxSize)/ETAndBackGroundGrowthEstimateStep;
        cout<<"Number Of ETAndBackGroundGrowthEstimation is "<<numberOfMeasure<<endl;

        if( numberOfMeasure == 0 ) cout<<"ETAndBackGroundGrowthEstimator is off!"<<endl;
        else cout<<"ETAndBackGroundGrowthEstimator is on!"<<endl;
    }
}