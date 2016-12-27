//
// Created by boruoshihao on 10/25/16.
//

#include "../include/LanczosParam.h"
#include <iostream>
#include <fstream>

using namespace std;

void LanczosParam::read(const string &filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if( !file.is_open() ) { cout << "Error opening file for LanczosParam::read!!!"; exit(1); }
    file>>matrixSize;
    file>>accuracy;
    file>>convergeFlag;
    file>>maxLoop;
    file>>litForProjection;
    file>>lanwfsFlag;
    file.close();
}