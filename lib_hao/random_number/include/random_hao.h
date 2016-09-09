#ifndef AFQMCLIB_RANDOM_HAO_H
#define AFQMCLIB_RANDOM_HAO_H

#define SIMPLE_SPRNG

#include "../../../utilities/mpi_hao/include/mpi_fun.h"

#ifdef MPI_HAO
#include <mpi.h> 
#define USE_MPI
#endif

#include "sprng.h"

void random_hao_init(int seed=985456376, int gtype=1);
void random_hao_save();
void random_hao_read();
void random_hao_backup();
double uniform_hao();
double gaussian_hao();

#endif
