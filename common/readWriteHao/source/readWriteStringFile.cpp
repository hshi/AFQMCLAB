//
// Created by boruoshihao on 12/17/16.
//
#include <sys/stat.h>
#include <fstream>
#include "../../mpiHao/include/mpi_fun.h"
#include "../include/readWriteStringFile.h"

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
    if( MPIRank()==0 )
    {
        int flag=system( command.c_str() );
        if(flag != 0) cout<<"WARNING!!! system command does not exit properly!"<<endl;
    }
    MPIBarrier();
}

size_t getFileLineSize(const std::string &filename)
{
    ifstream file(filename);
    string line;
    size_t lineSize(0);
    while( getline(file, line) ) lineSize++;
    file.close();
    return lineSize;
}
