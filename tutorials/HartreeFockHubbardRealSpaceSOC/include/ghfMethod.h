//
// Created by boruoshihao on 4/30/17.
//

#ifndef GHF_GHFMETHOD_H
#define GHF_GHFMETHOD_H

#include "afqmclab.h"

class GhfMethod
{
 public:
    std::string initialType; //"setFromModel", "readWaveFunction", "readOrderParameter"
    std::string convergeType; //"energy", "orderParameter"
    double convergeTolerance;
    size_t maxIterateStep;
    double annealMagnitude;
    size_t annealStep;
    double relaxMagnitude; // 1.0 fully relax to new order paramter, 0.0 not update
    int seed;  // -1. read file, 0. random, else is seeds

    GhfMethod();
    ~GhfMethod();

    void read(const std::string& filename);

#ifdef MPI_HAO
    friend void MPIBcast(GhfMethod &buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
#endif

 private:
    void analysis();
};

#endif //GHF_GHFMETHOD_H