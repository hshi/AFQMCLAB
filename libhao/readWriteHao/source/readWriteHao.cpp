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