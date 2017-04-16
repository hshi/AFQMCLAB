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
    file>>timesliceSize;
    file>>loopSize;
    file>>thermalStep;
    file>>measureStep;
    file>>initialPhiTFlag;
    file>>initialWalkerFlag;
    file>>adjustEnergyMaxStep;
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
    MPIBcast(buffer.timesliceSize);
    MPIBcast(buffer.loopSize);
    MPIBcast(buffer.thermalStep);
    MPIBcast(buffer.measureStep);
    MPIBcast(buffer.initialPhiTFlag);
    MPIBcast(buffer.initialWalkerFlag);
    MPIBcast(buffer.adjustEnergyMaxStep);
    MPIBcast(buffer.walkerSizePerThread);
    MPIBcast(buffer.walkerSize);
    MPIBcast(buffer.seed);
}
#endif

void AfqmcConstraintPathMethod::analysis()
{
    walkerSize = walkerSizePerThread*MPISize();

    if( dt * stabilizeStep > 2.0 )
    {
        cout<<"Warning!!! Stable beta is larger than 2.0!"<<endl;
    }

    if( thermalStep > timesliceSize )
    {
        cout<<"Warning!!! thermalStep is larger than timesliceSize!"<<endl;
    }
}
