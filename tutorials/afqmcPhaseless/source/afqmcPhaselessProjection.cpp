//
// Created by boruoshihao on 7/8/17.
//
#include "../include/afqmcPhaseless.h"
#include "../include/afqmcWalkerPop.h"

using namespace std;
using namespace tensor_hao;

void AfqmcPhaseless::projectExpHalfDtK()
{
    WalkerRight walkerTemp;
    if( expHalfDtK.matrix.size() > 0 )
    {
        for(int i = 0; i < method.walkerSizePerThread; ++i)
        {
            oneBodyWalkerRightOperation.applyToRight(expHalfDtK, walker[i], walkerTemp);
            walker[i] = move( walkerTemp );
        }
    }
    else if( logExpHalfDtK.matrix.size() > 0 )
    {
        for(int i = 0; i < method.walkerSizePerThread; ++i)
        {
            logOneBodyWalkerRightOperation.applyToRight(logExpHalfDtK, walker[i], walkerTemp);
            walker[i] = move( walkerTemp );
        }
    }
    else
    {
        cout<<"Error!!! Neither expHalfDtK nor logExpHalfDtK is allocated! "<<endl;
        exit(1);
    }
}

void AfqmcPhaseless::projectExpMinusHalfDtK()
{
    WalkerRight walkerTemp;
    if( expMinusHalfDtK.matrix.size() > 0 )
    {
        for(int i = 0; i < method.walkerSizePerThread; ++i)
        {
            oneBodyWalkerRightOperation.applyToRight(expMinusHalfDtK, walker[i], walkerTemp);
            walker[i] = move( walkerTemp );
        }
    }
    else if( logExpMinusHalfDtK.matrix.size() > 0 )
    {
        for(int i = 0; i < method.walkerSizePerThread; ++i)
        {
            logOneBodyWalkerRightOperation.applyToRight(logExpMinusHalfDtK, walker[i], walkerTemp);
            walker[i] = move( walkerTemp );
        }
    }
    else
    {
        cout<<"Error!!! Neither expMinusHalfDtK nor logExpMinusHalfDtK is allocated! "<<endl;
        exit(1);
    }
}

void AfqmcPhaseless::projectExpMinusDtKExpMinusDtV()
{
    double phase;
    WalkerRight walkerTemp;
    for(int i = 0; i < method.walkerSizePerThread; ++i)
    {
        WalkerWalkerOperation walkerWalkerOperation(phiT, walker[i]);
        phase = ( walkerWalkerOperation.returnLogOverlap() ).imag();
        if( cos(phase) <= 0.0 ) continue;
        walker[i].addLogw( log(cos(phase)) - complex<double>(0, phase) );

        if( method.forceType == "constForce" )
        {
            twoBodyAux = expMinusDtV.sampleAuxFromForce(constForce);
            twoBodySample = expMinusDtV.getTwoBodySampleFromAuxForce(twoBodyAux, constForce);
        }
        else if( method.forceType == "dynamicForce" )
        {
            dynamicForce = mixedMeasure.getForce( expMinusDtV, walkerWalkerOperation, method.forceCap );
            twoBodyAux = expMinusDtV.sampleAuxFromForce(dynamicForce);
            twoBodySample = expMinusDtV.getTwoBodySampleFromAuxForce(twoBodyAux, dynamicForce);
        }
        else
        {
            cout<<"Error!!! Do not know method.forceType "<<method.forceType<<endl;
            exit(1);
        }

        twoBodySampleWalkerRightOperation.applyToRight(twoBodySample, walker[i], walkerTemp);
        walkerTemp.addLogw( method.dt* method.ET );

        if( expMinusDtK.matrix.size() > 0 ) oneBodyWalkerRightOperation.applyToRight(expMinusDtK, walkerTemp, walker[i]);
        else logOneBodyWalkerRightOperation.applyToRight(logExpMinusDtK, walkerTemp, walker[i]);
    }
}

void AfqmcPhaseless::modifyGM(bool isAdjustable)
{
    if( MPIRank()==0 )
    {
        cout<<"In Modified gram schmidt: "<<endl;
        cout<<"Current mgsStep is "<< method.mgsStep <<endl;
    }

    if( isAdjustable )
    {
        double ratio(0.0), ratioMin(1e100), ratioMinGlobal(1e100);
        for(int i = 0; i < method.walkerSizePerThread; ++i)
        {
            walker[i].stabilize( ratio );
            if( ratioMin>ratio ) ratioMin = ratio;
        }

        MPIReduce( ratioMin, ratioMinGlobal, MPI_MIN );
        //Assume method.mgsStep = exp( alpha * ratioMinGlobal )
        method.mgsStep = log(method.mgsStepTolerance)/log(ratioMinGlobal) * method.mgsStep;
        MPIBcast( method.mgsStep );

        if( MPIRank()==0 )
        {
            cout<<"Mgs minimum ratio of different particles is "<< ratioMinGlobal <<endl;
            cout<<"Adjust mgsStep to  "<< method.mgsStep <<endl;
        }
    }
    else
    {
        for(int i = 0; i < method.walkerSizePerThread; ++i)
        {
            walker[i].stabilize();
        }
    }

    if( MPIRank()==0 ) cout<<endl;
}

void AfqmcPhaseless::popControl(bool isAdjustable)
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

    double ratio, average;
    tie(ratio, average) = popCheck(weight);
    if( MPIRank()==0 )
    {
        cout<<"In Population control: "<<endl;
        cout<<"Current popControlStep is "<< method.popControlStep <<endl;
        cout<<"Max weight ratio is "<< ratio <<endl;
        cout<<"Average weight is "<< average <<endl;
    }
    if( isAdjustable )
    {
        if( MPIRank()==0 )
        {
            //Assume method.popControlStep = exp( alpha * ratio )
            method.popControlStep = log(method.popControlStepTolerance)/log(ratio) * method.popControlStep;
            cout<<"Adjust popControlStep to  "<< method.popControlStep <<endl;
        }
        MPIBcast(method.popControlStep);
    }

    vector<int> table;
    if( MPIRank()==0 ) table=popConfiguration( MPISize(), weight );

    vector<AfqmcWalkerPop> walkerPop;
    walkerPop.reserve( method.walkerSizePerThread );
    for(int i=0; i<method.walkerSizePerThread; i++) walkerPop.push_back( AfqmcWalkerPop(walker[i]) );
    populationControl(walkerPop, table);

    if( MPIRank()==0 ) cout<<endl;
}
