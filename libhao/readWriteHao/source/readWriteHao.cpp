//
// Created by boruoshihao on 12/17/16.
//
#include <sys/stat.h>
#include <fstream>
#include <iomanip>
#include "../include/readWriteHao.h"

using namespace std;

bool checkFile(const string &filename)
{
    struct stat buffer;
    return (stat (filename.c_str(), &buffer) == 0);
}

void removeFile(const string &filename)
{
    string command = "rm -rf " + filename;
    MPIBarrier();
    if( MPIRank()==0 ) system( command.c_str() );
    MPIBarrier();
}

void writeFile(size_t data, const std::string &filename)
{
    ofstream file;
    file.open(filename, ios::out|ios::app);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    file<<setprecision(16)<<scientific;
    file<<setw(26)<<data<<"\n";
    file.close();
}

void readFile(size_t &data, const std::string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    file >> data;
    file.close();
}

void writeFile(double data, const string &filename)
{
    ofstream file;
    file.open(filename, ios::out|ios::app);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    file<<setprecision(16)<<scientific;
    file<<setw(26)<<data<<"\n";
    file.close();
}

void readFile(double &data, const string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    file >> data;
    file.close();
}

void writeFile(size_t L, const double *data, const string &filename)
{
    ofstream file;
    file.open(filename, ios::out|ios::app);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    file<<setprecision(16)<<scientific;
    for(size_t i = 0; i < L; ++i) file<<setw(26)<<data[i]<<"\n";
    file.close();
}

void readFile(size_t L, double *data, const string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    for(size_t i = 0; i < L; ++i) file>>data[i];
    file.close();
}

void writeFile(size_t L, const double *dataOne, const double *dataTwo, const string &filename)
{
    ofstream file;
    file.open(filename, ios::out|ios::app);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    file<<setprecision(16)<<scientific;
    for(size_t i = 0; i < L; ++i) file<<setw(26)<<dataOne[i]<<setw(26)<<dataTwo[i]<<"\n";
    file.close();
}

void readFile(size_t L, double *dataOne, double *dataTwo, const string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    for(size_t i = 0; i < L; ++i) file>>dataOne[i]>>dataTwo[i];
    file.close();
}

void writeFile(complex<double> data, const string &filename)
{
    ofstream file;
    file.open(filename, ios::out|ios::app);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    file<<setprecision(16)<<scientific;
    file<<setw(26)<<data.real()<<setw(26)<<data.imag()<<"\n";
    file.close();
}

void readFile(complex<double> &data, const string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    double real, imag;
    file >> real >> imag;
    data = complex<double>(real, imag);
    file.close();
}

void writeFile(size_t L, const complex<double> *data, const string &filename)
{
    ofstream file;
    file.open(filename, ios::out|ios::app);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    file<<setprecision(16)<<scientific;
    for(size_t i = 0; i < L; ++i) file<<setw(26)<<data[i].real()<<setw(26)<<data[i].imag()<<"\n";
    file.close();
}

void readFile(size_t L, complex<double> *data, const string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    double real, imag;
    for(size_t i = 0; i < L; ++i) { file>>real>>imag; data[i] = complex<double>(real, imag); }
    file.close();
}

void writeFile(size_t L, const complex<double> *dataOne, const complex<double> *dataTwo, const string &filename)
{
    ofstream file;
    file.open(filename, ios::out|ios::app);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    file<<setprecision(16)<<scientific;
    for(size_t i = 0; i < L; ++i) file<<setw(26)<<dataOne[i].real()<<setw(26)<<dataOne[i].imag()
                                      <<setw(26)<<dataTwo[i].real()<<setw(26)<<dataTwo[i].imag()<<"\n";
    file.close();
}

void readFile(size_t L, complex<double> *dataOne, complex<double> *dataTwo, const string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    double real, imag;
    for(size_t i = 0; i < L; ++i)
    {
        file>>real>>imag; dataOne[i] = complex<double>(real, imag);
        file>>real>>imag; dataTwo[i] = complex<double>(real, imag);
    }
    file.close();
}