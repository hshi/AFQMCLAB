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
        if( MPIRank()==0 )
        {
            fillWalkerRandomly(walkerLeft, model);
            fillWalkerRandomly(walkerRight, model);
            walkerLeft.write("walkerLeft.dat");
            walkerRight.write("walkerRight.dat");
        }
        MPIBcast(walkerLeft);
        MPIBcast(walkerRight);
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

void AfqmcMetropolis::initialField(WalkerLeft &walkerLeft, WalkerRight &walkerRight)
{
    auxiliaryFields.resize( method.timesliceSize );

    if( method.initalAuxiliaryFlag == "readFromFile") readField();

    walkerRightInBlock.resize(method.timesliceBlockSize+1);
    logWeightRightInBlock.resize(method.timesliceBlockSize+1);
    walkerRightSave.resize(method.timesliceBlockNumber);
    logWeightRightSave.resize(method.timesliceBlockNumber);

    walkerLeftInBlock.resize(method.timesliceBlockSize+1);
    logWeightLeftInBlock.resize(method.timesliceBlockSize+1);
    walkerLeftSave.resize(method.timesliceBlockNumber);
    logWeightLeftSave.resize(method.timesliceBlockNumber);

    WalkerRight walkerRightTemp;
    TwoBodySample twoBodySample;

    currentTimeslice = 0;
    complex<double> logWeight(0,0);
    applyOneBodyToRightWalker(walkerRight, walkerRightTemp, expMinusHalfDtK);
    for(size_t i = 0; i < method.timesliceBlockNumber; ++i)
    {
        walkerRightSave[i] = walkerRightTemp;
        logWeightRightSave[i] = logWeight;

        for(size_t j = 0; j < method.timesliceBlockSize; ++j)
        {
            if( i == (method.timesliceBlockNumber-1) )
            {
                walkerRightInBlock[j] = walkerRightTemp;
                logWeightRightInBlock[j] = logWeight;
            }

            if( method.initalAuxiliaryFlag == "constForceInitial" )
            {
                auxiliaryFields[currentTimeslice] = expMinusDtV.sampleAuxFromForce(constForce, method.sampleCap);
            }
            else if( method.initalAuxiliaryFlag == "dynamicForceInitial" )
            {
                getForce(dynamicForce, expMinusDtV, walkerLeft, walkerRightTemp);
                auxiliaryFields[currentTimeslice] = expMinusDtV.sampleAuxFromForce(dynamicForce, method.sampleCap);
            }

            twoBodySample = expMinusDtV.getTwoBodySampleFromAux( auxiliaryFields[currentTimeslice] );
            applyTwoBodySampleToRightWalker(walkerRightTemp, walkerRight, twoBodySample);
            applyOneBodyToRightWalker(walkerRight, walkerRightTemp, expMinusDtK);

            currentTimeslice++;

            logWeight = 0.0;
            if( currentTimeslice % method.stabilizeStep ==0 ) logWeight = walkerRightTemp.normalize();
        }
    }

    walkerRightInBlock[method.timesliceBlockSize] = move(walkerRightTemp);
    logWeightRightInBlock[method.timesliceBlockSize] = logWeight;

    applyOneBodyToLeftWalker(walkerLeft, walkerLeftSave[0], expMinusHalfDtK);
    logWeightLeftSave[0] = 0.0;

    currentTimeslice--;
    applyTwoBodySampleToRightWalker(walkerRightInBlock[method.timesliceBlockSize-1], walkerRight, twoBodySample);
    WalkerWalkerOperation walkerWalkerOperation(walkerLeftSave[0], walkerRight);
    currentLogOverlap = walkerWalkerOperation.returnLogOverlap();
}

void AfqmcMetropolis::readField()
{
    auxiliaryFields.resize( method.timesliceSize );
    string filename="auxiliaryFields_" + to_string( MPIRank() ) +".dat";
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) { cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    for(size_t i = 0; i < method.timesliceSize; ++i)
    {
        auxiliaryFields[i].read(file);
    }
    file.close();
}

void AfqmcMetropolis::writeField()
{
    TimerHao timer;
    timer.start();

    string filename="auxiliaryFields_" + to_string( MPIRank() ) +".dat";
    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if ( ! file.is_open() ) { cout << "Error opening file in File!!! "<<filename<<endl; exit(1); }
    for(size_t i = 0; i < method.timesliceSize; ++i)
    {
        auxiliaryFields[i].write(file);
    }
    file.close();

    timer.end();
    if( MPIRank()==0 ) { cout<<"AfqmcMetropolis::writeField walltime is:\n"; timer.print();}
}