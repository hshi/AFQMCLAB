//
// Created by boruoshihao on 1/17/17.
//
#include "../include/afqmcMetropolis.h"

using namespace std;
using namespace tensor_hao;

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
