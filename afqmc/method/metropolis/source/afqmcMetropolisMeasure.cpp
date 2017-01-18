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