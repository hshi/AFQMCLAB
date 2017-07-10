//
// Created by boruoshihao on 4/16/17.
//

#include "../include/afqmcConstraintPath.h"
#include "../include/afqmcWalkerPop.h"

using namespace std;
using namespace tensor_hao;

void AfqmcConstraintPath::projectExpHalfDtK()
{
    WalkerRight walkerTemp;
    for(int i = 0; i < method.walkerSizePerThread; ++i)
    {
        oneBodyWalkerRightOperation.applyToRight(expHalfDtK, walker[i], walkerTemp);
        walker[i] = move( walkerTemp );
    }
}

void AfqmcConstraintPath::projectExpMinusHalfDtK()
{
    WalkerRight walkerTemp;
    for(int i = 0; i < method.walkerSizePerThread; ++i)
    {
        oneBodyWalkerRightOperation.applyToRight(expMinusHalfDtK, walker[i], walkerTemp);
        walker[i] = move( walkerTemp );
    }
}

void AfqmcConstraintPath::projectExpMinusDtKExpMinusDtV()
{
    double phase, norm(0), logProb(0);
    WalkerRight walkerTemp;
    for(int i = 0; i < method.walkerSizePerThread; ++i)
    {
        WalkerWalkerOperation walkerWalkerOperation(phiT, walker[i]);
        phase = ( walkerWalkerOperation.returnLogOverlap() ).imag();
        if( cos(phase) <= 0.0 ) continue;
        walker[i].addLogw( log(cos(phase)) - complex<double>(0, phase) );

        if( method.forceType == "constForce" )
        {
            twoBodyAux = expMinusDtV.sampleAuxFromForce(constForce, method.sampleCap);
            norm = expMinusDtV.sumOfAuxFromForce(constForce, method.sampleCap);
            logProb = expMinusDtV.logProbOfAuxFromForce(twoBodyAux, constForce, method.sampleCap);
        }
        else if( method.forceType == "dynamicForce" )
        {
            getForce( dynamicForce, expMinusDtV, walkerWalkerOperation);
            twoBodyAux = expMinusDtV.sampleAuxFromForce(dynamicForce, method.sampleCap);
            norm = expMinusDtV.sumOfAuxFromForce(dynamicForce, method.sampleCap);
            logProb = expMinusDtV.logProbOfAuxFromForce(twoBodyAux, dynamicForce, method.sampleCap);
        }
        else
        {
            cout<<"Error!!! Do not know method.forceType "<<method.forceType<<endl;
            exit(1);
        }

        TwoBodySample twoBodySample = expMinusDtV.getTwoBodySampleFromAux(twoBodyAux);

        applyTwoBodySampleToRightWalker(walker[i], walkerTemp, twoBodySample);

        walkerTemp.addLogw( log(norm)-logProb + method.dt*ET );

        oneBodyWalkerRightOperation.applyToRight(expMinusDtK, walkerTemp, walker[i]);
    }
}

void AfqmcConstraintPath::modifyGM()
{
    for(int i = 0; i < method.walkerSizePerThread; ++i)
    {
        walker[i].stabilize();
    }
}

void AfqmcConstraintPath::popControl()
{
    vector<double> weightPerThread( method.walkerSizePerThread );
    complex<double> logOverlap;
    double overlapReal;
    for(int i = 0; i < method.walkerSizePerThread; ++i)
    {
        WalkerWalkerOperation walkerWalkerOperation(phiT, walker[i]);

        logOverlap = walkerWalkerOperation.returnLogOverlap();
        overlapReal = ( exp(logOverlap) ).real();

        if( overlapReal <= 0.0) weightPerThread[i] = 0.0;
        else weightPerThread[i] = overlapReal;

        walker[i].addLogw( -logOverlap );
    }

    vector<double> weight;
    if( MPIRank()==0 ) weight.resize( method.walkerSize );
    MPI_Gather( weightPerThread.data(), method.walkerSizePerThread, MPI_DOUBLE_PRECISION,
                weight.data(), method.walkerSizePerThread, MPI_DOUBLE_PRECISION, 0, MPI_COMM_WORLD );

    vector<int> table;
    if( MPIRank()==0 ) table=popConfiguration( MPISize(), weight );

    vector<AfqmcWalkerPop> walkerPop;
    walkerPop.reserve( method.walkerSizePerThread );
    for(int i=0; i<method.walkerSizePerThread; i++) walkerPop.push_back( AfqmcWalkerPop(walker[i]) );
    populationControl(walkerPop, table);
}