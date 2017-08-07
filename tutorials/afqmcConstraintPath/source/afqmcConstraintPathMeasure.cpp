//
// Created by boruoshihao on 4/16/17.
//
#include "../include/afqmcConstraintPath.h"

using namespace std;
using namespace tensor_hao;

void AfqmcConstraintPath::addMixedMeasurement()
{
    complex<double> overlap;
    WalkerRight walkerTemp;

    for(int i = 0; i < method.walkerSizePerThread; ++i)
    {
        if( walkerIsAlive[i] )
        {
            oneBodyWalkerRightOperation.applyToRight(expHalfDtK, walker[i], walkerTemp);

            walkerWalkerOperation.set(phiT, walkerTemp);

            overlap = exp( walkerWalkerOperation.returnLogOverlap() );

            mixedMeasure.addMeasurement(walkerWalkerOperation, overlap);
        }
    }
}

void AfqmcConstraintPath::writeAndResetMeasurement()
{
    mixedMeasure.write();
    mixedMeasure.reSet();
}

void AfqmcConstraintPath::adjustETAndResetMeasurement()
{
    method.ET = ( mixedMeasure.returnEnergy() ).real();

    if( MPIRank()==0 )
    {
        cout<<"\nAdjust trial energy: "<<method.ET<<"\n"<<endl;
    }

    mixedMeasure.reSet();
}