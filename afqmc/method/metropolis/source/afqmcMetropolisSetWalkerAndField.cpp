//
// Created by boruoshihao on 1/17/17.
//
#include "../include/afqmcMetropolis.h"

using namespace std;
using namespace tensor_hao;

void AfqmcMetropolis::initialWalker(WalkerLeft &walkerLeft, WalkerRight &walkerRight)
{
    if( method.initalWalkerFlag == "setFromModel" )
    {
        fillWalkerFromModel(walkerLeft, model);
        fillWalkerFromModel(walkerRight, model);

        if( MPIRank()==0 )
        {
            walkerLeft.write("walkerLeft.dat");
            walkerRight.write("walkerRight.dat");
        }
    }
    else if( method.initalWalkerFlag == "setRandomly" )
    {
        fillWalkerRandomly(walkerLeft, model);
        fillWalkerRandomly(walkerRight, model);

        if( MPIRank()==0 )
        {
            walkerLeft.write("walkerLeft.dat");
            walkerRight.write("walkerRight.dat");
        }
    }
    else if( method.initalWalkerFlag == "readFromFile" )
    {
        if( MPIRank()==0 )
        {
            walkerLeft.read("walkerLeft.dat");
            walkerRight.read("walkerRight.dat");
        }
        MPIBcast(walkerLeft);
        MPIBcast(walkerRight);
    }
    else
    {
        cout<<"Error!!! Do not recognize initalWalkerFlag!"<<endl;
        exit(1);
    }
}