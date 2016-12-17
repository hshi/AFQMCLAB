//
// Created by boruoshihao on 12/17/16.
//

#ifndef AFQMCLIB_READWRITEHAO_H
#define AFQMCLIB_READWRITEHAO_H

#include "../../mpiHao/include/mpi_fun.h"
#include "../../tensorHao/include/tensor_all.h"


bool checkFile (const std::string &filename);
void removeFile(const std::string &filename);

void writeFile(double data, const std::string& filename);
void readFile(double data, const std::string& filename);

void writeFile(size_t L, const double *data, const std::string& filename);
void readFile(size_t L, double *data, const std::string& filename);

void writeFile(size_t L, const double *dataOne, const double *dataTwo, const std::string& filename);
void readFile(size_t L, double *dataOne, double *dataTwo, const std::string& filename);

#endif //AFQMCLIB_READWRITEHAO_H