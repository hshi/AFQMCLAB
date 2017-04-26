//
// Created by boruoshihao on 4/16/17.
//
#include "../include/afqmcConstraintPath.h"

using namespace std;
using namespace tensor_hao;

void AfqmcConstraintPath::initialPhiT()
{
    if(method.initialPhiTFlag == "setFromModel")
    {
        fillWalkerFromModel(phiT, model);
        if( MPIRank()==0 ) phiT.write("phiT.dat");
    }
    else if(method.initialPhiTFlag == "setRandomly")
    {
        if( MPIRank()==0 )
        {
            fillWalkerRandomly(phiT, model);
            phiT.write("phiT.dat");
        }
        MPIBcast(phiT);
    }
    else if(method.initialPhiTFlag == "readFromFile")
    {
        if( MPIRank()==0 ) phiT.read("phiT.dat");
        MPIBcast(phiT);
    }
    else
    {
        cout<<"Error!!! Do not recognize initialPhiTFlag!"<<endl;
        exit(1);
    }
}

void AfqmcConstraintPath::initialWalker()
{
    walker.resize(method.walkerSizePerThread);

    if(method.initialWalkerFlag == "setFromModel")
    {
        fillWalkerFromModel(walker[0], model);
        if( MPIRank()==0 ) walker[0].write("phi.dat");

        for(int i = 1; i < method.walkerSizePerThread; ++i)
        {
            walker[i] = walker[0];
        }
    }
    else if(method.initialWalkerFlag == "setRandomly")
    {
        if( MPIRank()==0 )
        {
            fillWalkerRandomly(walker[0], model);
            walker[0].write("phi.dat");
        }
        MPIBcast(walker[0]);

        for(int i = 1; i < method.walkerSizePerThread; ++i)
        {
            walker[i] = walker[0];
        }
    }
    else if(method.initialWalkerFlag == "sampleFromPhiT")
    {
        for(int i = 0; i < method.walkerSizePerThread; ++i)
        {
            sampleWalkerFromPhiT(walker[i], phiT);
        }
    }
    else if(method.initialWalkerFlag == "readFromFile")
    {
        if( MPIRank()==0 ) walker[0].read("phi.dat");
        MPIBcast(walker[0]);

        for(int i = 1; i < method.walkerSizePerThread; ++i)
        {
            walker[i] = walker[0];
        }
    }
    else if(method.initialWalkerFlag == "readAllWalkers")
    {
        string filename;
        int baseNumber = MPIRank() * method.walkerSizePerThread;
        for(int i = 0; i < method.walkerSizePerThread; ++i)
        {
            filename = "./walkers/phi_" + to_string(i+baseNumber) +".dat";
            walker[i].read(filename);
        }
    }
    else
    {
        cout<<"Error!!! Do not recognize initialWalkerFlag!"<<endl;
        exit(1);
    }
}

void AfqmcConstraintPath::writeWalkers()
{
    MPIBarrier();
    if( MPIRank() == 0) system("mkdir -p walkers");
    MPIBarrier();

    string filename;
    int baseNumber = MPIRank() * method.walkerSizePerThread;
    for(int i = 0; i < method.walkerSizePerThread; ++i)
    {
        filename = "./walkers/phi_" + to_string(i+baseNumber) +".dat";
        walker[i].write(filename);
    }
}