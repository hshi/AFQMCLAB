//
// Created by boruoshihao on 1/17/17.
//
#include "../include/afqmcMetropolis.h"

using namespace std;
using namespace tensor_hao;

void AfqmcMetropolis::measureWithwalkerRightInBlock(const WalkerLeft &walkerLeft, size_t inBlockIndex)
{
    WalkerLeft walkerLeftTemp;
    WalkerRight walkerRightTemp;
    if( method.measureVarianceType == "normal" )
    {
        oneBodyWalkerOperation.applyToLeft(expHalfDtK, walkerLeft, walkerLeftTemp);
        oneBodyWalkerOperation.applyToRight(expHalfDtK, walkerRightInBlock[inBlockIndex+1], walkerRightTemp);
        addMeasurement(walkerLeftTemp, walkerRightTemp);
    }
    else if( method.measureVarianceType == "fixVariance" )
    {
        oneBodyWalkerOperation.applyToLeft(expHalfDtK, walkerLeft, walkerLeftTemp);
        oneBodyWalkerOperation.applyToRight(expHalfDtK, walkerRightInBlock[inBlockIndex], walkerRightTemp);
        //<walkerLeftTemp| exp(-dt H) | walkerRightTemp>
        complex<double> logExpMinusTauHAvg = measureLogExpMinusDtV(walkerLeft, walkerRightInBlock[inBlockIndex]);
        addMeasurementFixVariance(walkerLeftTemp, walkerRightTemp, logExpMinusTauHAvg);
    }
    else
    {
        cout<<"Do not recognize measureVarianceType!"<<endl; exit(1);
    }
}

void AfqmcMetropolis::measureWithWalkerLeftInBlock(size_t inBlockIndex, const WalkerRight &walkerRight)
{
    WalkerLeft walkerLeftTemp;
    WalkerRight walkerRightTemp;
    if( method.measureVarianceType == "normal" )
    {
        oneBodyWalkerOperation.applyToLeft(expHalfDtK, walkerLeftInBlock[method.timesliceBlockSize-inBlockIndex], walkerLeftTemp);
        oneBodyWalkerOperation.applyToRight(expHalfDtK, walkerRight, walkerRightTemp);
        addMeasurement(walkerLeftTemp, walkerRightTemp);
    }
    else if( method.measureVarianceType == "fixVariance" )
    {
        oneBodyWalkerOperation.applyToLeft(expHalfDtK, walkerLeftInBlock[method.timesliceBlockSize-inBlockIndex-1], walkerLeftTemp);
        oneBodyWalkerOperation.applyToRight(expHalfDtK, walkerRight, walkerRightTemp);
        //<walkerLeftTemp| exp(-dt H) | walkerRightTemp>
        complex<double> logExpMinusTauHAvg = measureLogExpMinusDtV(walkerLeftInBlock[method.timesliceBlockSize-inBlockIndex-1], walkerRight);
        addMeasurementFixVariance(walkerLeftTemp, walkerRightTemp, logExpMinusTauHAvg);
    }
    else
    {
        cout<<"Do not recognize measureVarianceType!"<<endl; exit(1);
    }
}

void AfqmcMetropolis::addMeasurement(const WalkerLeft &walkerLeft, const WalkerRight &walkerRight)
{
    WalkerWalkerOperation walkerWalkerOperation(walkerLeft, walkerRight);
    if( method.measureType == "commute" )
    {
        commuteMeasure.addMeasurement(walkerWalkerOperation, 1.0);
    }
    else if( method.measureType == "observable" )
    {
        observeMeasure.addMeasurement(walkerWalkerOperation, 1.0);
    }
}

void AfqmcMetropolis::addMeasurementFixVariance(const WalkerLeft &walkerLeft, const WalkerRight &walkerRight,
                                                complex<double> logExpMinusTauHAvg)
{
    WalkerWalkerOperation walkerWalkerOperation(walkerLeft, walkerRight);
    complex<double> leftRightLogOverlap = walkerWalkerOperation.returnLogOverlap();
    complex<double> denIncrement = exp(leftRightLogOverlap-logExpMinusTauHAvg);

    if( method.measureType == "commute" )
    {
        commuteMeasure.addMeasurement(walkerWalkerOperation, denIncrement);
    }
    else if( method.measureType == "observable" )
    {
        observeMeasure.addMeasurement(walkerWalkerOperation, denIncrement);
    }
}

complex<double> AfqmcMetropolis::measureLogExpMinusDtV(const WalkerLeft &walkerLeft, const WalkerRight &walkerRight)
{
    complex<double> logExpMinusDtVAvg, criteria;
    tie(logExpMinusDtVAvg, criteria) = measureLogTwoBodySecondOrder(walkerLeft, walkerRight, expMinusDtV);

    varianceMeasureNumber++;
    if( criteria.real() > method.secondOrderCap || criteria.real() < -method.secondOrderCap || abs( criteria.imag() ) > 0.1 )
    {
        varianceSampleNumber++;
        logExpMinusDtVAvg = measureLogTwoBodyForceBiasSample(walkerLeft, walkerRight, expMinusDtV, method.sampleCap, method.twoBodySampleSize);
    }

    return logExpMinusDtVAvg;
}

void AfqmcMetropolis::writeAndResetMeasurement()
{
    if( method.measureType == "commute" )
    {
        commuteMeasure.write();
        commuteMeasure.reSet();
    }
    else if( method.measureType == "observable" )
    {
        observeMeasure.write();
        observeMeasure.reSet();
    }
}

void AfqmcMetropolis::calculateAndPrintAcceptRatio()
{
    double totalUpdateNumber = MPISum(updateNumber);
    double totalAcceptNumber = MPISum(acceptNumber);

    if(MPIRank()==0)
    {
        cout<<setprecision(16);
        cout<<"Total Number of update: "<<totalUpdateNumber<<"\n"
            <<"Total Number of accept: "<<totalAcceptNumber<<"\n"
            <<"Accept ratio is: "<<totalAcceptNumber/totalUpdateNumber<<"\n"<<endl;
    }

    double totalSingleUpdateNumber = MPISum(singleUpdateNumber);
    double totalSingleAcceptNumber = MPISum(singleAcceptNumber);
    if(MPIRank()==0)
    {
        cout<<setprecision(16);
        cout<<"Total Number of single auxiliary update: "<<totalSingleUpdateNumber<<"\n"
            <<"Total Number of single auxiliary accept: "<<totalSingleAcceptNumber<<"\n"
            <<"Accept ratio is: "<<totalSingleAcceptNumber/totalSingleUpdateNumber<<"\n"<<endl;
    }
}

void AfqmcMetropolis::calculateVarianceSampleRatio()
{
    if( method.measureVarianceType == "fixVariance" )
    {
        double totalMeasureNumber = MPISum(varianceMeasureNumber);
        double totalSampleNumber = MPISum(varianceSampleNumber);

        if(MPIRank()==0)
        {
            cout<<setprecision(16);
            cout<<"Total Number of varaince measurement: "<<totalMeasureNumber<<"\n"
                <<"Total Number of variance sample: "<<totalSampleNumber<<"\n"
                <<"Sample ratio is: "<<totalSampleNumber/totalMeasureNumber<<"\n"<<endl;
        }
    }
}