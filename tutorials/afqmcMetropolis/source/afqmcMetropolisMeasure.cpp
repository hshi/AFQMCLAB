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
        applyOneBodyToLeftWalker(walkerLeft, walkerLeftTemp, expHalfDtK);
        applyOneBodyToRightWalker(walkerRightInBlock[inBlockIndex+1], walkerRightTemp, expHalfDtK);
        addMeasurement(walkerLeftTemp, walkerRightTemp);
    }
    else if( method.measureVarianceType == "fixVariance" )
    {
        applyOneBodyToLeftWalker(walkerLeft, walkerLeftTemp, expHalfDtK);
        applyOneBodyToRightWalker(walkerRightInBlock[inBlockIndex], walkerRightTemp, expHalfDtK);
        //<walkerLeftTemp| exp(-dt H) | walkerRightTemp>
        complex<double> expMinusTauHAvg = measureExpMinusDtV(walkerLeft, walkerRightInBlock[inBlockIndex]);
        addMeasurementFixVariance(walkerLeftTemp, walkerRightTemp, expMinusTauHAvg);
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
        applyOneBodyToLeftWalker(walkerLeftInBlock[method.timesliceBlockSize-inBlockIndex], walkerLeftTemp, expHalfDtK);
        applyOneBodyToRightWalker(walkerRight, walkerRightTemp, expHalfDtK);
        addMeasurement(walkerLeftTemp, walkerRightTemp);
    }
    else if( method.measureVarianceType == "fixVariance" )
    {
        applyOneBodyToLeftWalker(walkerLeftInBlock[method.timesliceBlockSize-inBlockIndex-1], walkerLeftTemp, expHalfDtK);
        applyOneBodyToRightWalker(walkerRight, walkerRightTemp, expHalfDtK);
        //<walkerLeftTemp| exp(-dt H) | walkerRightTemp>
        complex<double> expMinusTauHAvg = measureExpMinusDtV(walkerLeftInBlock[method.timesliceBlockSize-inBlockIndex-1], walkerRight);
        addMeasurementFixVariance(walkerLeftTemp, walkerRightTemp, expMinusTauHAvg);
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
                                                complex<double> expMinusTauHAvg)
{
    WalkerWalkerOperation walkerWalkerOperation(walkerLeft, walkerRight);
    complex<double> leftRightOverlap = exp( walkerWalkerOperation.returnLogOverlap() );
    complex<double> denIncrement = leftRightOverlap/expMinusTauHAvg;

    if( method.measureType == "commute" )
    {
        commuteMeasure.addMeasurement(walkerWalkerOperation, denIncrement);
    }
    else if( method.measureType == "observable" )
    {
        observeMeasure.addMeasurement(walkerWalkerOperation, denIncrement);
    }
}

complex<double> AfqmcMetropolis::measureExpMinusDtV(const WalkerLeft &walkerLeft, const WalkerRight &walkerRight)
{
//    complex<double> expMinusDtVAvg, criteria;
//    tie(expMinusDtVAvg, criteria) = measureTwoBodySecondOrder(walkerLeft, walkerRight, expMinusDtV);

    complex<double> expMinusDtVAvg = measureTwoBodyForceBiasSample(walkerLeft, walkerRight, expMinusDtV, method.sampleCap, 10000);
    return expMinusDtVAvg;
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