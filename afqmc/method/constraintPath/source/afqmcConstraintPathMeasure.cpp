//
// Created by boruoshihao on 4/16/17.
//
#include "../include/afqmcConstraintPath.h"

using namespace std;
using namespace tensor_hao;

void AfqmcConstraintPath::addMeasurement()
{
    complex<double> overlap;
    WalkerRight walkerTemp;
    for(int i = 0; i < method.walkerSizePerThread; ++i)
    {
        applyOneBodyToRightWalker(walker[i], walkerTemp, expHalfDtK);
        WalkerWalkerOperation walkerWalkerOperation(phiT, walkerTemp);
        overlap = exp( walkerWalkerOperation.returnLogOverlap() );
        commuteMeasure.addMeasurement(walkerWalkerOperation, overlap);
    }
}

void AfqmcConstraintPath::writeAndResetMeasurement()
{
    commuteMeasure.write();
    commuteMeasure.reSet();
}


void AfqmcConstraintPath::setET()
{
    ModelCommuteMeasure commuteMeasure;
    complex<double> overlap;
    WalkerRight walkerTemp;

    for(int i = 0; i < method.walkerSizePerThread; ++i)
    {
        applyOneBodyToRightWalker(walker[i], walkerTemp, expHalfDtK);
        WalkerWalkerOperation walkerWalkerOperation(phiT, walkerTemp);
        overlap = exp( walkerWalkerOperation.returnLogOverlap() );
        commuteMeasure.addMeasurement(walkerWalkerOperation, overlap);
    }
    ET = ( commuteMeasure.returnEnergy() ).real();
}