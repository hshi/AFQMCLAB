//
// Created by boruoshihao on 4/16/17.
//
#include "../include/afqmcConstraintPath.h"

using namespace std;
using namespace tensor_hao;

void AfqmcConstraintPath::addMeasurement()
{
    complex<double> overlap;
    for(int i = 0; i < method.walkerSizePerThread; ++i)
    {
        WalkerWalkerOperation walkerWalkerOperation(phiT, walker[i]);
        //TODO: For CPQMC time exp(tK/2) back to measure
        overlap = exp( walkerWalkerOperation.returnLogOverlap() );
        commuteMeasure.addMeasurement(walkerWalkerOperation, overlap);
    }
}

void AfqmcConstraintPath::writeAndResetMeasurement()
{
    commuteMeasure.write();
    commuteMeasure.reSet();
}