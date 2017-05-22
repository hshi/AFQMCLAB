//
// Created by boruoshihao on 12/27/16.
//

#ifndef AFQMCLAB_READWRITETEMPLATEFORTENSOR_H
#define AFQMCLAB_READWRITETEMPLATEFORTENSOR_H

#include <complex>
#include <iostream>
#include <fstream>
#include <iomanip>

template<class T>  void readFileForTensor(size_t L, T *data, std::ifstream &file)
{
    for(size_t i = 0; i < L; ++i) file>>data[i];
}

template<class T> void readFileForTensor(size_t L, std::complex<T> *data, std::ifstream &file)
{
    T real, imag;
    for(size_t i = 0; i < L; ++i) { file>>real>>imag; data[i] = std::complex<T>(real, imag); }
}

template<class T> void writeFileForTensor(size_t L, const T *data, std::ofstream &file)
{
    file<<std::setprecision(16)<<std::scientific;
    for(size_t i = 0; i < L; ++i) file<<std::setw(26)<<data[i]<<"\n";
}

template<class T> void writeFileForTensor(size_t L, const std::complex<T> *data, std::ofstream &file)
{
    file<<std::setprecision(16)<<std::scientific;
    for(size_t i = 0; i < L; ++i) file<<std::setw(26)<<data[i].real()<<std::setw(26)<<data[i].imag()<<"\n";
}

#endif //AFQMCLAB_READWRITETEMPLATEFORTENSOR_H