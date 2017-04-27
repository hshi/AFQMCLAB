//
// Created by boruoshihao on 12/17/16.
//

#ifndef AFQMCLAB_READWRITESTRINGFILE_H
#define AFQMCLAB_READWRITESTRINGFILE_H

#include <iostream>
#include <fstream>
#include <complex>
#include <iomanip>

bool checkFile (const std::string &filename);
void removeFile(const std::string &filename);
size_t getFileLineSize(const std::string &filename);

//For read
template<class T> void readFile(T &data, const std::string &filename, size_t skipStep=0)
{
    std::ifstream file;
    file.open(filename, std::ios::in);
    if ( ! file.is_open() ) {std::cout << "Error opening file in File!!! "<<filename<<std::endl; exit(1);}
    for(size_t i = 0; i < skipStep; ++i) file>>data;
    file >> data;
    file.close();
}

template<class T> void readFile(std::complex<T> &data, const std::string &filename, size_t skipStep=0)
{
    std::ifstream file;
    file.open(filename, std::ios::in);
    if ( ! file.is_open() ) {std::cout << "Error opening file in File!!! "<<filename<<std::endl; exit(1);}
    T real, imag;
    for(size_t i = 0; i < skipStep; ++i) file >> real >> imag;
    file >> real >> imag;
    data = std::complex<T>(real, imag);
    file.close();
}

template<class T>  void readFile(size_t L, T *data, const std::string& filename, size_t skipStep=0)
{
    std::ifstream file;
    file.open(filename, std::ios::in);
    if ( ! file.is_open() ) {std::cout << "Error opening file in File!!! "<<filename<<std::endl; exit(1);}
    for(size_t i = 0; i < skipStep; ++i) file>>data[0];
    for(size_t i = 0; i < L; ++i) file>>data[i];
    file.close();
}

template<class T> void readFile(size_t L, T *dataOne, T *dataTwo, const std::string &filename, size_t skipStep=0)
{
    std::ifstream file;
    file.open(filename, std::ios::in);
    if ( ! file.is_open() ) {std::cout << "Error opening file in File!!! "<<filename<<std::endl; exit(1);}
    for(size_t i = 0; i < skipStep; ++i) file>>dataOne[0]>>dataTwo[0];
    for(size_t i = 0; i < L; ++i) file>>dataOne[i]>>dataTwo[i];
    file.close();
}

template<class T> void readFile(size_t L, std::complex<T> *data, const std::string &filename, size_t skipStep=0)
{
    std::ifstream file;
    file.open(filename, std::ios::in);
    if ( ! file.is_open() ) {std::cout << "Error opening file in File!!! "<<filename<<std::endl; exit(1);}
    T real, imag;
    for(size_t i = 0; i < skipStep; ++i) file>>real>>imag;
    for(size_t i = 0; i < L; ++i) { file>>real>>imag; data[i] = std::complex<T>(real, imag); }
    file.close();
}

template<class T> void readFile(size_t L, std::complex<T> *dataOne, std::complex<T> *dataTwo, const std::string &filename, size_t skipStep=0)
{
    std::ifstream file;
    file.open(filename, std::ios::in);
    if ( ! file.is_open() ) {std::cout << "Error opening file in File!!! "<<filename<<std::endl; exit(1);}
    T real, imag;
    for(size_t i = 0; i < skipStep; ++i) { file>>real>>imag; file>>real>>imag; }
    for(size_t i = 0; i < L; ++i)
    {
        file>>real>>imag; dataOne[i] = std::complex<T>(real, imag);
        file>>real>>imag; dataTwo[i] = std::complex<T>(real, imag);
    }
    file.close();
}

template<class T> void writeFile(T data, const std::string &filename, std::ios_base::openmode type= std::ios::trunc)
{
    std::ofstream file;
    file.open(filename, std::ios::out|type);
    if ( ! file.is_open() ) {std::cout << "Error opening file in File!!! "<<filename<<std::endl; exit(1);}
    file<<std::setprecision(16)<<std::scientific;
    file<<std::setw(26)<<data<<"\n";
    file.close();
}

template<class T> void writeFile(std::complex<T> data, const std::string &filename, std::ios_base::openmode type= std::ios::trunc)
{
    std::ofstream file;
    file.open(filename, std::ios::out|type);
    if ( ! file.is_open() ) {std::cout << "Error opening file in File!!! "<<filename<<std::endl; exit(1);}
    file<<std::setprecision(16)<<std::scientific;
    file<<std::setw(26)<<data.real()<<std::setw(26)<<data.imag()<<"\n";
    file.close();
}

template<class T> void writeFile(size_t L, const T *data, const std::string &filename, std::ios_base::openmode type= std::ios::trunc)
{
    std::ofstream file;
    file.open(filename, std::ios::out|type);
    if ( ! file.is_open() ) {std::cout << "Error opening file in File!!! "<<filename<<std::endl; exit(1);}
    file<<std::setprecision(16)<<std::scientific;
    for(size_t i = 0; i < L; ++i) file<<std::setw(26)<<data[i]<<"\n";
    file.close();
}

template<class T> void writeFile(size_t L, const T *dataOne, const T *dataTwo, const std::string &filename, std::ios_base::openmode type= std::ios::trunc)
{
    std::ofstream file;
    file.open(filename, std::ios::out|type);
    if ( ! file.is_open() ) {std::cout << "Error opening file in File!!! "<<filename<<std::endl; exit(1);}
    file<<std::setprecision(16)<<std::scientific;
    for(size_t i = 0; i < L; ++i) file<<std::setw(26)<<dataOne[i]<<std::setw(26)<<dataTwo[i]<<"\n";
    file.close();
}

template<class T> void writeFile(size_t L, const std::complex<T> *data, const std::string &filename, std::ios_base::openmode type= std::ios::trunc)
{
    std::ofstream file;
    file.open(filename, std::ios::out|type);
    if ( ! file.is_open() ) {std::cout << "Error opening file in File!!! "<<filename<<std::endl; exit(1);}
    file<<std::setprecision(16)<<std::scientific;
    for(size_t i = 0; i < L; ++i) file<<std::setw(26)<<data[i].real()<<std::setw(26)<<data[i].imag()<<"\n";
    file.close();
}

template<class T> void writeFile(size_t L, const std::complex<T> *dataOne, const std::complex<T> *dataTwo,
                                 const std::string &filename, std::ios_base::openmode type= std::ios::trunc)
{
    std::ofstream file;
    file.open(filename, std::ios::out|type);
    if ( ! file.is_open() ) {std::cout << "Error opening file in File!!! "<<filename<<std::endl; exit(1);}
    file<<std::setprecision(16)<<std::scientific;
    for(size_t i = 0; i < L; ++i) file<<std::setw(26)<<dataOne[i].real()<<std::setw(26)<<dataOne[i].imag()
                                      <<std::setw(26)<<dataTwo[i].real()<<std::setw(26)<<dataTwo[i].imag()<<"\n";
    file.close();
}

#endif //AFQMCLAB_READWRITESTRINGFILE_H
