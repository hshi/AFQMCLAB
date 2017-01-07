//
// Created by boruoshihao on 10/20/16.
//
#include <fstream>
#include "../include/LanczosInterface.h"
#include "../../../common/readWriteHao/include/readWriteHao.h"

using namespace tensor_hao;

using namespace std;

void Lanczos::readEigenValues(size_t numberOfWaveFunctions)
{
    string filename;
    eigenvalues.resize(numberOfWaveFunctions);
    for(size_t i = 0; i < numberOfWaveFunctions; ++i)
    {
        filename="eigenvalue_" + to_string(i) +".dat";
        readFile( eigenvalues[i], filename );
    }
}

void Lanczos::readEigenStates(size_t numberOfWaveFunctions)
{
    string filename;
    eigenstates.resize(numberOfWaveFunctions);
    for(size_t i = 0; i < numberOfWaveFunctions; ++i)
    {
        filename="eigenstate_" + to_string(i) +".dat";
        eigenstates[i].read(filename);
    }
}

void Lanczos::writeEigenValues(size_t startIndex) const
{
    string filename;
    for(size_t i = startIndex; i < eigenvalues.size(); ++i)
    {
        filename = "eigenvalue_" + to_string(i) + ".dat";
        writeFile(eigenvalues[i], filename);
    }
}

void Lanczos::writeEigenStates(size_t startIndex) const
{
    string filename;
    for(size_t i = startIndex; i < eigenstates.size(); ++i)
    {
        filename="eigenstate_" + to_string(i) +".dat";
        eigenstates[i].write(filename);
    }
}

void Lanczos::readLanMatrixStatus(const string &prefixName)
{
    string filename = prefixName + "Status.dat";
    ifstream file;
    file.open(filename, ios_base::in);
    if( !file.is_open() ) { cout << "Error opening file for read lanczosMatrixStatus!!!"; exit(1); }
    size_t lanSize, lanwfSize;
    file >> lanSize >> lanStatus;
    file.close();

    if( lanStatus == string("none") )
        return;
    if( lanStatus == string("both") || lanStatus == string("bothConverged") || lanStatus == string("full") || lanStatus == string("fullConverged") )
        lanwfSize = lanSize + 1;
    if( lanStatus == string("recurse") || lanStatus == string("recurseConverged") )
        lanwfSize = 4;

    lana.resize( lanSize );
    lanb.resize( lanSize );
    lanwfs.resize( lanwfSize );
}

void Lanczos::readLanMatrixElements(const string &prefixName)
{
    string filename = prefixName + "Elements.dat";
    ifstream file;
    file.open(filename, ios_base::in);
    if( !file.is_open() ) { cout << "Error opening file for read lanczosMatrixElements!!!"; exit(1); }
    for(size_t i = 0; i < lana.size(); ++i)
    {
        file >> lana[i] >> lanb[i];
    }
    file.close();
}

void Lanczos::readLanMatrixWavefunctions(const string &prefixName)
{
    string filename;
    for(size_t i = 0; i < lanwfs.size(); ++i)
    {
        filename = prefixName + "Wf_" + to_string(i) + ".dat";
        lanwfs[i].read(filename);
    }
}

void Lanczos::writeLanMatrixStatus(const string &prefixName) const
{
    string filename = prefixName + "Status.dat";
    ofstream file;
    file.open(filename, ios_base::out | ios_base::trunc);
    if( !file.is_open() )  { cout << "Error opening file for write lanczosMatrixStatus!!!"; exit(1); }
    file << setw(26) << lana.size() << setw(26) << lanStatus << "\n";
    file.close();
}

void Lanczos::writeLanMatrixElements(const string &prefixName) const
{
    string filename = prefixName + "Elements.dat";
    ofstream file;
    file.open(filename, ios_base::out | ios_base::trunc);
    if( !file.is_open() )  { cout << "Error opening file for write lanczosMatrixElements!!!"; exit(1); }
    file<<setprecision(16)<<scientific;
    for(size_t i = 0; i < lana.size(); ++i)
    {
        file << setw(26) << lana[i] << setw(26) << lanb[i] << "\n";
    }
    file.close();
}

void Lanczos::writeLanMatrixWavefunctions(const string &prefixName) const
{
    size_t lanwfSize(0);
    if( lanStatus == string("none") )
        return;
    if( lanStatus == string("both") || lanStatus == string("bothConverged") || lanStatus == string("full") || lanStatus == string("fullConverged") )
        lanwfSize = lana.size() + 1;
    if( lanStatus == string("recurse") || lanStatus == string("recurseConverged") )
        lanwfSize = 4;

    string filename;
    for(size_t i = 0; i < lanwfSize; ++i)
    {
        filename = prefixName + "Wf_" + to_string(i) + ".dat";
        lanwfs[i].write(filename);
    }
}