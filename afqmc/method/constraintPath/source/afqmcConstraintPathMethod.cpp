//
// Created by boruoshihao on 4/16/17.
//

#include "../include/afqmcConstraintPathMethod.h"

using namespace std;

AfqmcConstraintPathMethod::AfqmcConstraintPathMethod()
{

}

AfqmcConstraintPathMethod::~AfqmcConstraintPathMethod()
{

}

void AfqmcConstraintPathMethod::read(const string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}

    file>>dt;
    file>>decompType;
    file>>forceType;
    file>>sampleCap;
    file>>stabilizeStep;
    file>>populationControlStep;
    file>>timesliceSize;
    file>>thermalStep;
    file>>measureSkipTimesliceStep;
    file>>writeSkipTimesliceStep;
    file>>initialPhiTFlag;
    file>>initialWalkerFlag;
    file>>setETMaxStep;
    file>>walkerSizePerThread;
    file>>seed;

    file.close();

    analysis();
}

#ifdef MPI_HAO
void MPIBcast(AfqmcConstraintPathMethod &buffer, int root, MPI_Comm const &comm)
{
    MPIBcast(buffer.dt);
    MPIBcast(buffer.decompType);
    MPIBcast(buffer.forceType);
    MPIBcast(buffer.sampleCap);
    MPIBcast(buffer.stabilizeStep);
    MPIBcast(buffer.populationControlStep);
    MPIBcast(buffer.timesliceSize);
    MPIBcast(buffer.thermalStep);
    MPIBcast(buffer.measureSkipTimesliceStep);
    MPIBcast(buffer.writeSkipTimesliceStep);
    MPIBcast(buffer.initialPhiTFlag);
    MPIBcast(buffer.initialWalkerFlag);
    MPIBcast(buffer.setETMaxStep);
    MPIBcast(buffer.walkerSizePerThread);
    MPIBcast(buffer.walkerSize);
    MPIBcast(buffer.seed);
}
#endif

void AfqmcConstraintPathMethod::analysis()
{
    walkerSize = walkerSizePerThread*MPISize();

    if( (timesliceSize-thermalStep)%writeSkipTimesliceStep != 0 )
    {
        size_t numberOfWrite=(timesliceSize-thermalStep)/writeSkipTimesliceStep;
        timesliceSize = writeSkipTimesliceStep*numberOfWrite+thermalStep;
        cout<<"Warning!!! (timesliceSize-thermalStep)%writeSkipTimesliceStep is not zero!"<<endl;
        cout<<"Cut timesliceSize to avoid unnecessary projection step: "<<timesliceSize<<endl;
    }

    if( dt <= 0.0 )
    {
        cout<<"Error!!! dt must be postive!"<<endl;
        exit(1);
    }

    if( sampleCap < 0.0 )
    {
        cout<<"Error!!! sampleCap must be positive or zero!"<<endl;
        exit(1);
    }

    if( dt * stabilizeStep > 2.0 )
    {
        cout<<"Warning!!! Stabilization beta is larger than 2.0!"<<endl;
    }

    if( dt * populationControlStep > 2.0 )
    {
        cout<<"Warning!!! Population control beta is larger than 2.0!"<<endl;
    }

    if( thermalStep > timesliceSize )
    {
        cout<<"Warning!!! thermalStep is larger than timesliceSize!"<<endl;
    }

    if( writeSkipTimesliceStep%measureSkipTimesliceStep != 0 )
    {
        cout<<"Warning!!! writeSkipTimesliceStep%measureSkipTimesliceStep is not zero!"<<endl;
    }

    if( dt * setETMaxStep > 2.0 )
    {
        cout<<"Warning!!! dt * setETMaxStep is larger than 2.0!"<<endl;
    }

    if( walkerSizePerThread <= 0 )
    {
        cout<<"Error!!! walkerSizePerThread is not a positive number!"<<endl;
        exit(1);
    }
}