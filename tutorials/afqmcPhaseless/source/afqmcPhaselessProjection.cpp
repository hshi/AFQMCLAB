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
            if( walkerIsAlive[i] )
            {
                oneBodyWalkerRightOperation.applyToRight(expHalfDtK, walker[i], walkerTemp);
                walker[i] = move(walkerTemp);
            }
        }
    }
    else if( logExpHalfDtK.matrix.size() > 0 )
    {
        for(int i = 0; i < method.walkerSizePerThread; ++i)
        {
            if( walkerIsAlive[i] )
            {
                logOneBodyWalkerRightOperation.applyToRight(logExpHalfDtK, walker[i], walkerTemp);
                walker[i] = move(walkerTemp);
            }
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
            if( walkerIsAlive[i] )
            {
                oneBodyWalkerRightOperation.applyToRight(expMinusHalfDtK, walker[i], walkerTemp);
                walker[i] = move(walkerTemp);
            }
        }
    }
    else if( logExpMinusHalfDtK.matrix.size() > 0 )
    {
        for(int i = 0; i < method.walkerSizePerThread; ++i)
        {
            if( walkerIsAlive[i] )
            {
                logOneBodyWalkerRightOperation.applyToRight(logExpMinusHalfDtK, walker[i], walkerTemp);
                walker[i] = move(walkerTemp);
            }
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
    complex<double> auxForce;
    for(int i = 0; i < method.walkerSizePerThread; ++i)
    {
        if( walkerIsAlive[i] )
        {
            WalkerWalkerOperation walkerWalkerOperation(phiT, walker[i]);
            phase = (walkerWalkerOperation.returnLogOverlap()).imag();
            if (cos(phase) <= 0.0) { walkerIsAlive[i] = false; continue; }
            walker[i].addLogw(log(cos(phase)) - complex<double>(0, phase));

            if (method.forceType == "constForce")
            {
                twoBodyAux = expMinusDtV.sampleAuxFromForce(constForce);
                twoBodySample = expMinusDtV.getTwoBodySampleFromAuxForce(twoBodyAux, constForce);
                auxForce = 0.0; for(size_t k = 0; k < model.getCholeskyNumber() ; ++k) auxForce += twoBodyAux(k)*constForce(k);
            }
            else if (method.forceType == "dynamicForce")
            {
                dynamicForce = mixedMeasure.getForce(expMinusDtV, walkerWalkerOperation, method.forceCap);
                twoBodyAux = expMinusDtV.sampleAuxFromForce(dynamicForce);
                twoBodySample = expMinusDtV.getTwoBodySampleFromAuxForce(twoBodyAux, dynamicForce);
                auxForce = 0.0; for(size_t k = 0; k < model.getCholeskyNumber() ; ++k) auxForce += twoBodyAux(k)*dynamicForce(k);
            }
            else
            {
                cout << "Error!!! Do not know method.forceType " << method.forceType << endl;
                exit(1);
            }

            //Cos projection
            phase = auxForce.imag();
            if (cos(phase) <= 0.0) { walkerIsAlive[i] = false; continue; }
            walker[i].addLogw( log( cos(phase) ) );

            twoBodySampleWalkerRightOperation.applyToRight(twoBodySample, walker[i], walkerTemp);

            walkerTemp.addLogw(method.dt * method.ET);

            if (expMinusDtK.matrix.size() > 0) oneBodyWalkerRightOperation.applyToRight(expMinusDtK, walkerTemp, walker[i]);
            else logOneBodyWalkerRightOperation.applyToRight(logExpMinusDtK, walkerTemp, walker[i]);
        }
    }
}

void AfqmcPhaseless::projectOneStep(size_t &mgsIndex, size_t &popControlIndex)
{
    projectExpMinusDtKExpMinusDtV();

    mgsIndex++;
    if (mgsIndex == method.mgsStep)
    {
        modifyGM();
        mgsIndex = 0;
    }

    popControlIndex++;
    if (popControlIndex == method.popControlStep)
    {
        popControl();
        popControlIndex = 0;
    }
}

void AfqmcPhaseless::modifyGM()
{
    for(int i = 0; i < method.walkerSizePerThread; ++i)
    {
        if( walkerIsAlive[i] ) walker[i].stabilize();
    }
}

void AfqmcPhaseless::popControl()
{
    vector<double> weightPerThread( method.walkerSizePerThread );
    complex<double> logOverlap; double overlapReal;
    for(int i = 0; i < method.walkerSizePerThread; ++i)
    {
        if( walkerIsAlive[i] )
        {
            walkerWalkerOperation.set(phiT, walker[i]);

            logOverlap = walkerWalkerOperation.returnLogOverlap();
            overlapReal = (exp(logOverlap)).real();

            if (overlapReal <= 0.0) { weightPerThread[i] = 0.0; walkerIsAlive[i] = false; }
            else { weightPerThread[i] = overlapReal;  walker[i].addLogw( -logOverlap ); }
        }
        else
        {
            weightPerThread[i] = 0.0;
        }
    }

    checkAndResetWalkerIsAlive();

    vector<double> weight;
#ifdef MPI_HAO
    if( MPIRank()==0 ) weight.resize( method.walkerSize );
    MPI_Gather( weightPerThread.data(), method.walkerSizePerThread, MPI_DOUBLE_PRECISION,
                weight.data(), method.walkerSizePerThread, MPI_DOUBLE_PRECISION, 0, MPI_COMM_WORLD );
#else
    weight = move( weightPerThread );
#endif

    double minW, maxW, avgW;
    tie( minW, maxW, avgW ) = popCheck(weight);
    if( MPIRank()==0 )
    {
        cout<<"In Population control: "<<endl;
        cout<<"Min weight is "<< minW <<endl;
        cout<<"Max weight is "<< maxW <<endl;
        cout<<"Average weight is "<< avgW <<endl;
    }

    vector<int> table;
    if( MPIRank()==0 ) table=popConfiguration( MPISize(), weight );

    vector<AfqmcWalkerPop> walkerPop;
    walkerPop.reserve( method.walkerSizePerThread );
    for(int i=0; i<method.walkerSizePerThread; i++) walkerPop.push_back( AfqmcWalkerPop(walker[i]) );
    populationControl(walkerPop, table);

    if( MPIRank()==0 ) cout<<endl;
}

void AfqmcPhaseless::checkAndResetWalkerIsAlive()
{
    size_t aliveWalkerPerThread(0);
    for (int i = 0; i < method.walkerSizePerThread; ++i)
    {
        if( walkerIsAlive[i] ) aliveWalkerPerThread++;
    }

    size_t aliveWalker = MPISum(aliveWalkerPerThread);

    if( MPIRank()==0 )
    {
        cout<<"Total number of walker is "<<method.walkerSize<<"."<<endl;
        cout<<"Currently "<<aliveWalker<<" walkers are still alive."<<endl;
        cout<<"Currently "<<method.walkerSize-aliveWalker<<" walkers are killed."<<endl;
    }

    for (int i = 0; i < method.walkerSizePerThread ; ++i)
    {
        walkerIsAlive[i] = true;
    }
}