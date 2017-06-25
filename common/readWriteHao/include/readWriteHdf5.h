//
// Created by boruoshihao on 5/31/17.
//

#ifndef AFQMCLAB_READWRITEHDF5_H
#define AFQMCLAB_READWRITEHDF5_H

#include "../../hdf5Hao/include/hdf5CustomHao.h"

void readFile(size_t &data, const H5::H5File &file, const std::string &dataSetName);
void readFile(double &data, const H5::H5File &file, const std::string &dataSetName);
void readFile(std::complex<double> &data, const H5::H5File &file, const std::string &dataSetName);
void readFile(size_t L, size_t *data, const H5::H5File &file, const std::string &dataSetName);
void readFile(size_t L, double *data, const H5::H5File &file, const std::string &dataSetName);
void readFile(size_t L, std::complex<double> *data, const H5::H5File &file, const std::string &dataSetName);

void writeFile(const size_t &data, H5::H5File &file, const std::string &dataSetName);
void writeFile(const double &data, H5::H5File &file, const std::string &dataSetName);
void writeFile(const std::complex<double> &data, H5::H5File &file, const std::string &dataSetName);
void writeFile(size_t L, const size_t *data, H5::H5File &file, const std::string &dataSetName);
void writeFile(size_t L, const double *data, H5::H5File &file, const std::string &dataSetName);
void writeFile(size_t L, const std::complex<double> *data, H5::H5File &file, const std::string &dataSetName);

#endif //AFQMCLAB_READWRITEHDF5_H