#ifndef AFQMCLIB_RANDOM_HAO_H
#define AFQMCLIB_RANDOM_HAO_H

#define SIMPLE_SPRNG

#include "../mpi_hao/mpi_fun.h"

#ifdef MPI_HAO
#include <mpi.h> 
#define USE_MPI
#endif

#include "sprng.h"

void randomHaoInit(int seed = 985456376, int gtype = 1);
void randomHaoSave();
void randomHaoRead();
void randomHaoBackup();
double uniformHao();
double gaussianHao();

#endif
