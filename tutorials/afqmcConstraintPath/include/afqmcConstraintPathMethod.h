//
// Created by boruoshihao on 4/16/17.
//

#ifndef AFQMCLAB_AFQMCCONSTRAINTPATHMETHOD_H
#define AFQMCLAB_AFQMCCONSTRAINTPATHMETHOD_H

#include "afqmcConstraintPathDefine.h"

#ifdef MPI_HAO
class AfqmcConstraintPathMethod;
void MPIBcast(AfqmcConstraintPathMethod &buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
#endif

class AfqmcConstraintPathMethod
{
 public:
    double dt;
    std::string decompType;  // depends on two body operator, check twoBodyOperator for types.
    std::string forceType;   // "dynamicForce", "constForce"
    double sampleCap;
    size_t stabilizeStep;
    size_t populationControlStep;
    size_t timesliceSize;
    size_t thermalStep;
    size_t measureSkipTimesliceStep;
    size_t writeSkipTimesliceStep;
    std::string initialPhiTFlag;   //"setFromModel", "setRandomly", "readFromFile"
    std::string initialWalkerFlag; //"setFromModel", "setRandomly", "sampleFromPhiT", "readFromFile", "readAllWalkers"
    size_t setETMaxStep;
    int walkerSizePerThread;
    int walkerSize;
    int seed;  // -1. read file, 0. random, else is seeds

    AfqmcConstraintPathMethod();
    ~AfqmcConstraintPathMethod();

    void read(const std::string& filename);

#ifdef MPI_HAO
    friend void MPIBcast(AfqmcConstraintPathMethod &buffer, int root,  const MPI_Comm& comm);
#endif

 private:
    void analysis();
};

#endif //AFQMCLAB_AFQMCCONSTRAINTPATHMETHOD_H