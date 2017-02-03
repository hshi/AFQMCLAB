//
// Created by boruoshihao on 12/27/16.
//

#ifndef AFQMCLAB_READWRITEFSTREAM_H
#define AFQMCLAB_READWRITEFSTREAM_H

#include <fstream>
#include <iomanip>
#include <complex>

//For Read
template<class T>  void readFile( T &data, std::ifstream &file)
{
    file>>data;
}

template<class T> void readFile(std::complex<T> &data, std::ifstream &file)
{
    T real, imag;
    file>>real>>imag;
    data = std::complex<T>(real, imag);
}

template<class T>  void readFile(size_t L, T *data, std::ifstream &file)
{
    for(size_t i = 0; i < L; ++i) file>>data[i];
}

template<class T> void readFile(size_t L, std::complex<T> *data, std::ifstream &file)
{
    T real, imag;
    for(size_t i = 0; i < L; ++i) { file>>real>>imag; data[i] = std::complex<T>(real, imag); }
}

//For Write
template<class T> void writeFile(const T &data, std::ofstream &file)
{
    file<<std::setprecision(16)<<std::scientific;
    file<<std::setw(26)<<data<<"\n";
}

template<class T> void writeFile(const std::complex<T> &data, std::ofstream &file)
{
    file<<std::setprecision(16)<<std::scientific;
    file<<std::setw(26)<<data.real()<<std::setw(26)<<data.imag()<<"\n";
}

template<class T> void writeFile(size_t L, const T *data, std::ofstream &file)
{
    file<<std::setprecision(16)<<std::scientific;
    for(size_t i = 0; i < L; ++i) file<<std::setw(26)<<data[i]<<"\n";
}

template<class T> void writeFile(size_t L, const std::complex<T> *data, std::ofstream &file)
{
    file<<std::setprecision(16)<<std::scientific;
    for(size_t i = 0; i < L; ++i) file<<std::setw(26)<<data[i].real()<<std::setw(26)<<data[i].imag()<<"\n";
}

#endif //AFQMCLAB_READWRITEFSTREAM_H
