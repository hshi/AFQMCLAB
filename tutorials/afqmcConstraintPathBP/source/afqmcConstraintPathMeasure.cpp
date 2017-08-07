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

            observeMeasure.addMeasurement(walkerWalkerOperation, overlap);
        }
    }
}

void AfqmcConstraintPath::adjustETAndResetMeasurement()
{
    method.ET = ( observeMeasure.returnEnergy() ).real();

    if( MPIRank()==0 )
    {
        cout<<"\nAdjust trial energy: "<<method.ET<<"\n"<<endl;
    }

    observeMeasure.reSet();
}

void AfqmcConstraintPath::addMeasurement()
{
    if( !isBP ) return;
    prepareBackPropagationMeasAndNextBackup();

    complex<double> overlap;
    WalkerRight walkerTemp; WalkerLeft phiLeftOne, phiLeftTwo;
    for(int i = 0; i < method.walkerSizePerThread; ++i)
    {
        if( walkerIsAlive[i] )
        {
            oneBodyWalkerRightOperation.applyToRight(expHalfDtK, walker[i], walkerTemp);
            walkerWalkerOperation.set(phiT, walkerTemp);
            overlap = exp( walkerWalkerOperation.returnLogOverlap() );

            oneBodyWalkerLeftOperation.applyToLeft(expMinusHalfDtK, phiT, phiLeftOne);
            for (size_t j = method.backPropagationStep; j >0 ; --j)
            {
                twoBodySample = expMinusDtV.getTwoBodySampleFromAux( twoBodyAuxBPMeasure[i][j-1] );
                twoBodySampleWalkerLeftOperation.applyToLeft(twoBodySample, phiLeftOne, phiLeftTwo);
                oneBodyWalkerLeftOperation.applyToLeft(expMinusDtK, phiLeftTwo, phiLeftOne);

                if( (method.backPropagationStep-j+1)%method.mgsStep == 0 ) phiLeftOne.normalize();
            }
            oneBodyWalkerLeftOperation.applyToLeft(expHalfDtK, phiLeftOne, phiLeftTwo);
            oneBodyWalkerRightOperation.applyToRight(expHalfDtK, walkerBPMeasure[i], walkerTemp);

            walkerWalkerOperation.set(phiLeftTwo, walkerTemp);
            observeMeasure.addMeasurement(walkerWalkerOperation, overlap);
        }
    }
}

void AfqmcConstraintPath::writeAndResetMeasurement()
{
    observeMeasure.write();
    observeMeasure.reSet();
}