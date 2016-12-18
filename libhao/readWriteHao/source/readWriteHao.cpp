//
// Created by boruoshihao on 12/17/16.
//
#include <sys/stat.h>
#include <fstream>
#include "../include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

bool checkFile(const std::string &filename)
{
    struct stat buffer;
    return (stat (filename.c_str(), &buffer) == 0);
}

void removeFile(const std::string &filename)
{
    string command = "rm -rf " + filename;
    MPIBarrier();
    if( MPIRank()==0 ) system( command.c_str() );
    MPIBarrier();
}

void writeFile(double data, const std::string &filename)
{
    ofstream file;
    file.open(filename, ios::out|ios::app);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    file<<setprecision(16)<<scientific;
    file<<setw(26)<<data<<"\n";
    file.close();
}

void readFile(double data, const std::string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    file >> data;
    file.close();
}

void writeFile(size_t L, const double *data, const std::string &filename)
{
    ofstream file;
    file.open(filename, ios::out|ios::app);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    file<<setprecision(16)<<scientific;
    for(size_t i = 0; i < L; ++i) file<<setw(26)<<data[i]<<"\n";
    file.close();
}

void readFile(size_t L, double *data, const std::string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    for(size_t i = 0; i < L; ++i) file>>data[i];
    file.close();
}

void writeFile(size_t L, const double *dataOne, const double *dataTwo, const std::string &filename)
{
    ofstream file;
    file.open(filename, ios::out|ios::app);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    file<<setprecision(16)<<scientific;
    for(size_t i = 0; i < L; ++i) file<<setw(26)<<dataOne[i]<<setw(26)<<dataTwo[i]<<"\n";
    file.close();
}

void readFile(size_t L, double *dataOne, double *dataTwo, const std::string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    for(size_t i = 0; i < L; ++i) file>>dataOne[i]>>dataTwo[i];
    file.close();
}