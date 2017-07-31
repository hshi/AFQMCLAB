//
// Created by boruoshihao on 1/17/17.
//
#include "../include/afqmcMetropolis.h"

using namespace std;
using namespace tensor_hao;

void AfqmcMetropolis::updateOneSweep(bool isMeasure)
{
    updateToRightOneSweep(isMeasure);
    updateToLeftOneSweep(isMeasure);
}

void AfqmcMetropolis::updateToRightOneSweep(bool isMeasure)
{
    WalkerLeft walkerLeft = walkerLeftSave[0];
    complex<double> logWeight = logWeightLeftSave[0];

    for(int i = (method.timesliceBlockNumber-1); i > -1 ; --i)
    {
        //Back up for left
        if( i != static_cast<int>(method.timesliceBlockNumber-1) )
        {
            walkerLeftSave[method.timesliceBlockNumber-1-i] = walkerLeft;
            logWeightLeftSave[method.timesliceBlockNumber-1-i] = logWeight;
        }

        for(int j = (method.timesliceBlockSize-1); j > -1 ; --j)
        {
            //Measure
            if( (currentTimeslice+1) % method.measureSkipTimesliceStep == 0 && isMeasure )
            {
                if( currentTimeslice >= static_cast<int>(method.measureSkipTimesliceRight) &&
                    method.timesliceSize >= (method.measureSkipTimesliceLeft+1+currentTimeslice) )
                {
                    measureWithwalkerRightInBlock(walkerLeft, j);
                }
            }

            //Delete to save memory
            walkerRightInBlock[j+1] = WalkerRight();
            logWeightRightInBlock[j+1] = 0.0;

            //Back up for left
            if(i==0)
            {
                walkerLeftInBlock[method.timesliceBlockSize-1-j] = walkerLeft;
                logWeightLeftInBlock[method.timesliceBlockSize-1-j] = logWeight;
            }

            updateToRightOneStep(j, walkerLeft, logWeight);
        }

        setBlockFromRightToLeft(i);

        //Delete to save memory
        if( i != 0 )
        {
            walkerRightSave[i] = WalkerRight();
            logWeightRightSave[i] = 0.0;
        }
    }

    //Back up for left
    walkerLeftInBlock[method.timesliceBlockSize] = move(walkerLeft);
    logWeightLeftInBlock[method.timesliceBlockSize] = logWeight;

    currentTimeslice++;
    currentLogOverlap -= logWeightRightSave[0];
    currentLogOverlap += conj(logWeight);
}

void AfqmcMetropolis::updateToLeftOneSweep(bool isMeasure)
{
    WalkerRight walkerRight = walkerRightSave[0];
    complex<double> logWeight = logWeightRightSave[0];

    for(size_t i = 0; i < method.timesliceBlockNumber; ++i)
    {
        //Back up for right
        if( i != 0 )
        {
            walkerRightSave[i] = walkerRight;
            logWeightRightSave[i] = logWeight;
        }

        for(size_t j = 0; j < method.timesliceBlockSize; ++j)
        {
            //Measure
            if( currentTimeslice % method.measureSkipTimesliceStep == 0 && isMeasure )
            {
                if( currentTimeslice >= static_cast<int>(method.measureSkipTimesliceRight) &&
                    method.timesliceSize >= (method.measureSkipTimesliceLeft+1+currentTimeslice) )
                {
                    measureWithWalkerLeftInBlock(j, walkerRight);
                }
            }

            //Delete to save memory
            walkerLeftInBlock[method.timesliceBlockSize-j] = WalkerLeft();
            logWeightLeftInBlock[method.timesliceBlockSize-j] = 0.0;

            //Back up for right
            if( i == (method.timesliceBlockNumber-1) )
            {
                walkerRightInBlock[j] = walkerRight;
                logWeightRightInBlock[j] = logWeight;
            }

            updateToLeftOneStep(j, walkerRight, logWeight);
        }

        setBlockFromLeftToRight(i+1);

        //Delete to save memory
        if( i != (method.timesliceBlockNumber-1) )
        {
            walkerLeftSave[method.timesliceBlockNumber-1-i] = WalkerLeft();
            logWeightLeftSave[method.timesliceBlockNumber-1-i] = 0.0;
        }
    }

    //Back up for right
    walkerRightInBlock[method.timesliceBlockSize] = move( walkerRight );
    logWeightRightInBlock[method.timesliceBlockSize] = logWeight;

    currentTimeslice--;
    currentLogOverlap -= conj( logWeightLeftSave[0] );
    currentLogOverlap += logWeight;
}

void AfqmcMetropolis::updateToRightOneStep(size_t inBlockIndex, WalkerLeft &walkerLeft, complex<double> &logWeight)
{
    TwoBodyAux auxNew;
    if( method.forceType == "constForce" )
    {
        auxNew = expMinusDtV.sampleAuxFromForce(constForce, method.sampleCap);
    }
    else if( method.forceType == "dynamicForce" )
    {
        getForce( dynamicForce, expMinusDtV, walkerLeft, walkerRightInBlock[inBlockIndex] );
        auxNew = expMinusDtV.sampleAuxFromForce(dynamicForce, method.sampleCap);
    }

    TwoBodySample twoBodySample = expMinusDtV.getTwoBodySampleFromAux(auxNew);

    WalkerLeft walkerLeftTemp;
    twoBodyWalkerOperation.applyToLeft(twoBodySample, walkerLeft, walkerLeftTemp);

    WalkerWalkerOperation walkerWalkerOperation( walkerLeftTemp, walkerRightInBlock[inBlockIndex] );
    complex<double> logOverlapNew = walkerWalkerOperation.returnLogOverlap();

    double logProbNew = returnLogProbOfAux( auxNew );
    double currentLogProb = returnLogProbOfAux( auxiliaryFields[currentTimeslice] );

    double alpha = ( exp(logOverlapNew-currentLogOverlap-logProbNew+currentLogProb) ).real();

    if(alpha<0.0) { cout<<"Sign Problem!!! "<<MPIRank()<<endl; exit(1); }

    updateNumber++; singleUpdateNumber+=expMinusDtV.getAuxSize();

    if( uniformHao() < alpha )
    {
        acceptNumber++; singleAcceptNumber+= expMinusDtV.getAuxDiffSize( auxNew, auxiliaryFields[currentTimeslice] );
        auxiliaryFields[currentTimeslice] = move(auxNew);
        currentLogOverlap = logOverlapNew;
        oneBodyWalkerOperation.applyToLeft(expMinusDtK, walkerLeftTemp, walkerLeft);
    }
    else
    {
        twoBodySample = expMinusDtV.getTwoBodySampleFromAux(auxiliaryFields[currentTimeslice]);
        twoBodyWalkerOperation.applyToLeft(twoBodySample, walkerLeft, walkerLeftTemp);
        oneBodyWalkerOperation.applyToLeft(expMinusDtK, walkerLeftTemp, walkerLeft);
    }

    currentLogOverlap += logWeightRightInBlock[inBlockIndex];
    logWeight = 0.0;
    if( (method.timesliceSize - currentTimeslice) % method.stabilizeStep == 0 )
    {
        logWeight = walkerLeft.normalize();
    }
    currentLogOverlap -= conj( logWeight );

    currentTimeslice--;
}

void AfqmcMetropolis::updateToLeftOneStep(size_t inBlockIndex, WalkerRight &walkerRight, complex<double> &logWeight)
{
    TwoBodyAux auxNew;
    if( method.forceType == "constForce" )
    {
        auxNew = expMinusDtV.sampleAuxFromForce(constForce, method.sampleCap);
    }
    else if( method.forceType == "dynamicForce" )
    {
        getForce( dynamicForce, expMinusDtV, walkerLeftInBlock[method.timesliceBlockSize-1-inBlockIndex], walkerRight );
        auxNew = expMinusDtV.sampleAuxFromForce(dynamicForce, method.sampleCap);
    }

    TwoBodySample twoBodySample = expMinusDtV.getTwoBodySampleFromAux(auxNew);

    WalkerRight walkerRightTemp;
    twoBodyWalkerOperation.applyToRight(twoBodySample, walkerRight, walkerRightTemp);

    WalkerWalkerOperation walkerWalkerOperation( walkerLeftInBlock[method.timesliceBlockSize-1-inBlockIndex], walkerRightTemp );
    complex<double> logOverlapNew = walkerWalkerOperation.returnLogOverlap();

    double logProbNew = returnLogProbOfAux( auxNew );
    double currentLogProb = returnLogProbOfAux( auxiliaryFields[currentTimeslice] );

    double alpha = ( exp(logOverlapNew-currentLogOverlap-logProbNew+currentLogProb) ).real();

    if(alpha<0.0) { cout<<"Sign Problem!!! "<<MPIRank()<<endl; exit(1); }

    updateNumber++; singleUpdateNumber+=expMinusDtV.getAuxSize();

    if( uniformHao() < alpha )
    {
        acceptNumber++; singleAcceptNumber+= expMinusDtV.getAuxDiffSize( auxNew, auxiliaryFields[currentTimeslice] );
        auxiliaryFields[currentTimeslice] = move(auxNew);
        currentLogOverlap = logOverlapNew;
        oneBodyWalkerOperation.applyToRight(expMinusDtK, walkerRightTemp, walkerRight);
    }
    else
    {
        twoBodySample = expMinusDtV.getTwoBodySampleFromAux(auxiliaryFields[currentTimeslice]);
        twoBodyWalkerOperation.applyToRight(twoBodySample, walkerRight, walkerRightTemp);
        oneBodyWalkerOperation.applyToRight(expMinusDtK, walkerRightTemp, walkerRight);
    }

    currentLogOverlap += conj( logWeightLeftInBlock[method.timesliceBlockSize-1-inBlockIndex] );
    logWeight = 0.0;
    if( (currentTimeslice+1) % method.stabilizeStep == 0 )
    {
        logWeight = walkerRight.normalize();
    }
    currentLogOverlap -= logWeight;

    currentTimeslice++;
}

void AfqmcMetropolis::setBlockFromRightToLeft(size_t leftBlockIndex)
{
    if( leftBlockIndex == 0 ) return;

    WalkerRight walkerRightTemp;
    TwoBodySample twoBodySample;
    complex<double> logWeight;

    size_t timeSliceIndex = (leftBlockIndex-1)*method.timesliceBlockSize;
    walkerRightInBlock[0] = walkerRightSave[leftBlockIndex-1];
    logWeightRightInBlock[0] = logWeightRightSave[leftBlockIndex-1];

    for(size_t i = 0; i < (method.timesliceBlockSize - 1); ++i)
    {
        twoBodySample = expMinusDtV.getTwoBodySampleFromAux( auxiliaryFields[timeSliceIndex] );
        twoBodyWalkerOperation.applyToRight(twoBodySample, walkerRightInBlock[i], walkerRightTemp);
        oneBodyWalkerOperation.applyToRight(expMinusDtK, walkerRightTemp, walkerRightInBlock[i+1]);

        timeSliceIndex++;

        logWeight = 0.0;
        if( timeSliceIndex % method.stabilizeStep == 0 )
        {
            logWeight = walkerRightInBlock[i+1].normalize();
        }
        logWeightRightInBlock[i+1] = logWeight;
    }

    walkerRightInBlock[method.timesliceBlockSize] = move(walkerRightSave[leftBlockIndex]);
    logWeightRightInBlock[method.timesliceBlockSize] = logWeightRightSave[leftBlockIndex];
}

void AfqmcMetropolis::setBlockFromLeftToRight(size_t rightBlockIndex)
{
    if( rightBlockIndex == method.timesliceBlockNumber ) return;

    WalkerLeft walkerLeftTemp;
    TwoBodySample twoBodySample;
    complex<double> logWeight;

    int timeSliceIndex = (rightBlockIndex+1)*method.timesliceBlockSize-1;
    walkerLeftInBlock[0] = walkerLeftSave[method.timesliceBlockNumber-(1+rightBlockIndex)];
    logWeightLeftInBlock[0] = logWeightLeftSave[method.timesliceBlockNumber-(1+rightBlockIndex)];

    for(size_t i = 0; i < (method.timesliceBlockSize - 1); ++i)
    {
        twoBodySample = expMinusDtV.getTwoBodySampleFromAux( auxiliaryFields[timeSliceIndex] );
        twoBodyWalkerOperation.applyToLeft(twoBodySample, walkerLeftInBlock[i], walkerLeftTemp);
        oneBodyWalkerOperation.applyToLeft(expMinusDtK, walkerLeftTemp, walkerLeftInBlock[i+1]);

        logWeight = 0.0;
        if( (method.timesliceSize-timeSliceIndex) % method.stabilizeStep == 0 )
        {
            logWeight = walkerLeftInBlock[i+1].normalize();
        }
        logWeightLeftInBlock[i+1] = logWeight;

        timeSliceIndex--;
    }

    walkerLeftInBlock[method.timesliceBlockSize] = move( walkerLeftSave[method.timesliceBlockNumber-rightBlockIndex] );
    logWeightLeftInBlock[method.timesliceBlockSize] = logWeightLeftSave[method.timesliceBlockNumber-rightBlockIndex];
}

double AfqmcMetropolis::returnLogProbOfAux(const TwoBodyAux &twoBodyAux)
{
    if( method.forceType == "constForce" )
    {
        return expMinusDtV.logProbOfAuxFromForce(twoBodyAux, constForce, method.sampleCap);
    }
    else if( method.forceType == "dynamicForce" )
    {
        return expMinusDtV.logProbOfAuxFromForce(twoBodyAux, dynamicForce, method.sampleCap);
    }
    else
    {
        cout<<"Error!!! Do not recognize initialAuxiliaryFlag!"<<endl; exit(1);
    }
}