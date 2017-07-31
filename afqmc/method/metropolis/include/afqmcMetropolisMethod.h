//
// Created by boruoshihao on 1/15/17.
//

#ifndef AFQMCLAB_AFQMCMETROPOLISMETHOD_H
#define AFQMCLAB_AFQMCMETROPOLISMETHOD_H

#include "afqmcMetropolisDefine.h"

#ifdef MPI_HAO
class AfqmcMetropolisMethod;
void MPIBcast(AfqmcMetropolisMethod &buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
#endif

class AfqmcMetropolisMethod
{
 public:
    double dt;
    std::string decompType;  // depends on two body operator, check twoBodyOperator for types.
    std::string forceType;   // "dynamicForce", "constForce"
    double sampleCap;
    size_t thermalSweep;
    size_t measureSweep;
    size_t writeSweep;
    size_t stabilizeStep;
    size_t timesliceSize;
    size_t timesliceBlockSize;
    size_t timesliceBlockNumber;
    std::string initialWalkerFlag;    //"setFromModel", "setRandomly", "readFromFile"
    std::string initialAuxiliaryFlag; //"dynamicForceInitial", "constForceInitial", "readFromFile"
    std::string measureType; //"commute", "observable"
    std::string measureVarianceType; //"normal", "fixVariance"
    double secondOrderCap;
    size_t twoBodySampleSize;
    size_t measureSkipTimesliceStep;
    size_t measureSkipTimesliceLeft;
    size_t measureSkipTimesliceRight;
    int seed;  // -1. read file, 0. random, else is seeds

    AfqmcMetropolisMethod();
    ~AfqmcMetropolisMethod();

    void read(const std::string& filename);

#ifdef MPI_HAO
    friend void MPIBcast(AfqmcMetropolisMethod &buffer, int root,  const MPI_Comm& comm);
#endif

 private:
    void analysis();
};

#endif //AFQMCLAB_AFQMCMETROPOLISMETHOD_H
