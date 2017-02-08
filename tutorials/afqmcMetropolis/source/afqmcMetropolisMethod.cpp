//
// Created by boruoshihao on 1/15/17.
//

#include "../include/afqmcMetropolisMethod.h"

using namespace std;

AfqmcMetropolisMethod::AfqmcMetropolisMethod()
{

}

AfqmcMetropolisMethod::~AfqmcMetropolisMethod()
{

}

void AfqmcMetropolisMethod::read(const string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}

    file>>dt;
    file>>decompType;
    file>>forceType;
    file>>sampleCap;
    file>>thermalSweep;
    file>>measureSweep;
    file>>writeSweep;
    file>>stabilizeStep;
    file>>timesliceSize;
    file>>timesliceBlockSize;
    file>>initalWalkerFlag;
    file>>initalAuxiliaryFlag;
    file>>measureType;
    file>>measureVarianceType;
    file>>secondOrderCap;
    file>>twoBodySampleSize;
    file>>measureSkipTimesliceStep;
    file>>measureSkipTimesliceLeft;
    file>>measureSkipTimesliceRight;
    file>>seed;

    file.close();

    analysis();
}

#ifdef MPI_HAO
void MPIBcast(AfqmcMetropolisMethod &buffer, int root, MPI_Comm const &comm)
{
    MPIBcast(buffer.dt);
    MPIBcast(buffer.decompType);
    MPIBcast(buffer.forceType);
    MPIBcast(buffer.sampleCap);
    MPIBcast(buffer.thermalSweep);
    MPIBcast(buffer.measureSweep);
    MPIBcast(buffer.writeSweep);
    MPIBcast(buffer.stabilizeStep);
    MPIBcast(buffer.timesliceSize);
    MPIBcast(buffer.timesliceBlockSize);
    MPIBcast(buffer.timesliceBlockNumber);
    MPIBcast(buffer.initalWalkerFlag);
    MPIBcast(buffer.initalAuxiliaryFlag);
    MPIBcast(buffer.measureType);
    MPIBcast(buffer.measureVarianceType);
    MPIBcast(buffer.secondOrderCap);
    MPIBcast(buffer.twoBodySampleSize);
    MPIBcast(buffer.measureSkipTimesliceStep);
    MPIBcast(buffer.measureSkipTimesliceLeft);
    MPIBcast(buffer.measureSkipTimesliceRight);
    MPIBcast(buffer.seed);
}
#endif

void AfqmcMetropolisMethod::analysis()
{
    timesliceBlockNumber = timesliceSize / timesliceBlockSize;
    if( timesliceBlockNumber*timesliceBlockSize != timesliceSize )
    {
        cout<<"Error!!! timesliceSize can not be divided by timesliceBlockSize!"<<endl;
        exit(1);
    }

    if( measureSweep % writeSweep != 0 )
    {
        cout<<"Warning!!! It is better to have measureSweep % writeSweep == 0!"<<endl;
    }

    if( measureType == "commute")
    {
        cout<<"Only the physics quantities commuted with H will be measured!"<<endl;
        cout<<"If measureSkipTimesliceLeft/Right==0, the statistical error bar will be smaller, the trotter error is ~(dt)^2."<<endl;
        cout<<"If measureSkipTimesliceLeft/Right is large, the trotter error is smaller ~(dt)^4."<<endl;
    }
    else if( measureType == "observable")
    {
        cout<<"All the physics quantities will be measured!"<<endl;
        cout<<"Set measureSkipTimesliceLeft/Right to be larger enough, the trotter error of energy is ~(dt)^4."<<endl;
    }
    else
    {
        cout<<"ERROR!!! Do not know the measureType!"<<endl;
        exit(1);
    }

    bool observFlag = false;
    size_t measureNumber = timesliceSize/measureSkipTimesliceStep+1;
    size_t index;
    for(size_t i=0; i<=measureNumber; i++)
    {
        index=i*measureSkipTimesliceStep;
        if( index>=(measureSkipTimesliceRight+1) && timesliceSize>=(measureSkipTimesliceLeft+index) ) {observFlag=true;}
        if( index>=(measureSkipTimesliceRight) && timesliceSize>=(measureSkipTimesliceLeft+index+1) ) {observFlag=true;}
    }
    if( !observFlag )
    {
        if( timesliceSize == 0 )
        {
            cout<<"Only measure from intial wave function."<<endl;
        }
        else
        {
            cout<<"ERROR!!! Nothing will be measured!!!"<<endl;
            cout<<"If you want to update the auxiliary fields, please use thermalSweep instead of measureSkipTimesliceLeft/Right."<<endl;
            exit(1);
        }
    }
}