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
    size_t thermalSize;
    size_t writeNumber;
    size_t measureSkipStep;
    size_t writeSkipStep;

    int walkerSizePerThread;
    int walkerSize;

    std::string decompType;  // depends on two body operator, check twoBodyOperator for types.
    std::string forceType;   // "dynamicForce", "constForce"
    double forceCap;
    std::string initialPhiTFlag;   //"setFromModel", "setRandomly", "readFromFile"
    std::string initialWalkerFlag; //"setFromModel", "setRandomly", "sampleFromPhiT", "readFromFile", "readAllWalkers"

    size_t mgsStep;
    size_t popControlStep;

    double ET;
    size_t ETAdjustStep;
    size_t ETAdjustMaxSize;

    int seed;  // -1. read file, 0. random, else is seeds

    AfqmcConstraintPathMethod();
    ~AfqmcConstraintPathMethod();

    void read(const std::string& filename);
    void write(const std::string& filename);
    void print();

#ifdef MPI_HAO
    friend void MPIBcast(AfqmcConstraintPathMethod &buffer, int root,  const MPI_Comm& comm);
#endif

 private:
    void setDefault();
    void analysis();
};

#endif //AFQMCLAB_AFQMCCONSTRAINTPATHMETHOD_H