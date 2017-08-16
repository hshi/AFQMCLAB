//
// Created by boruoshihao on 7/8/17.
//
#include "../include/afqmcPhaseless.h"

using namespace std;
using namespace tensor_hao;

void AfqmcPhaseless::addMixedMeasurement()
{
    complex<double> overlap;
    WalkerRight walkerTemp;

    for(int i = 0; i < method.walkerSizePerThread; ++i)
    {
        if( walkerIsAlive[i] )
        {
            if (expHalfDtK.matrix.size() > 0) oneBodyWalkerRightOperation.applyToRight(expHalfDtK, walker[i], walkerTemp);
            else logOneBodyWalkerRightOperation.applyToRight(logExpHalfDtK, walker[i], walkerTemp);

            walkerWalkerOperation.set(phiT, walkerTemp);

            overlap = exp(walkerWalkerOperation.returnLogOverlap());

            mixedMeasure.addMeasurement(walkerWalkerOperation, overlap);
        }
    }
}

void AfqmcPhaseless::writeAndResetMeasurement()
{
    mixedMeasure.write();
    mixedMeasure.reSet();
}

void AfqmcPhaseless::adjustETAndBackGroundThenResetMeasurement()
{
    method.ET = ( mixedMeasure.returnEnergy() ).real();
    model.updateBackGround( mixedMeasure.returnCholeskyBg() );

    if( MPIRank()==0 )
    {
        cout<<"\nAdjust trial energy: "<<method.ET<<endl;
        cout<<"Adjust background: "<<model.getCholeskyBg()<<"\n"<<endl;
    }

    mixedMeasure.reSet();
}