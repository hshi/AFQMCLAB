//
// Created by boruoshihao on 7/8/17.
//

#include "../include/afqmcPhaseless.h"

using namespace std;
using namespace tensor_hao;

AfqmcPhaseless::AfqmcPhaseless() { }

AfqmcPhaseless::~AfqmcPhaseless() { }

void AfqmcPhaseless::run()
{
    initialParameters();

    initialPhiT();

    initialWalker();

    initialMixedMeasure();

    estimateMemory();

    if( method.timesliceSize == 0  ) measureWithoutProjection();
    else measureWithProjection();

    prepareStop();
}

void AfqmcPhaseless::initialParameters()
{
    if( MPIRank()==0 ) method.read("afqmc_param");
    if( MPIRank()==0 ) method.print();
    MPIBcast(method);

    randomHaoInit(method.seed, 1);
    if( method.seed != -1 ) randomHaoSave();

    if( MPIRank()==0 ) model.read("model_param");
    MPIBcast(model);

    if( method.isETAndBackGroundAdjustable )
    {
        logExpMinusDtK     = model.returnLogExpMinusAlphaK(  method.dt     );
        logExpMinusHalfDtK = model.returnLogExpMinusAlphaK(  method.dt*0.5 );
        logExpHalfDtK      = model.returnLogExpMinusAlphaK( -method.dt*0.5 );
    }
    else
    {
        expMinusDtK     = model.returnExpMinusAlphaK(  method.dt     );
        expMinusHalfDtK = model.returnExpMinusAlphaK(  method.dt*0.5 );
        expHalfDtK      = model.returnExpMinusAlphaK( -method.dt*0.5 );
    }

    expMinusDtV = model.returnExpMinusAlphaV( method.dt );
    constForce = expMinusDtV.readForce("constForce_param");
}

void AfqmcPhaseless::initialMixedMeasure()
{
    logOneBodyWalkerRightOperation.reset("dynamicOrder", 0, 1e-14);
    mixedMeasure.setModelWalker(model, phiT);
}

void AfqmcPhaseless::estimateMemory()
{
    double mem(0.0);
    mem += model.getMemory();
    mem += expMinusHalfDtK.getMemory()+expHalfDtK.getMemory()+expMinusDtK.getMemory();
    mem += logExpMinusHalfDtK.getMemory()+logExpHalfDtK.getMemory()+logExpMinusDtK.getMemory();
    mem += expMinusDtV.getMemory();

    mem += constForce.getMemory()*2.0;

    twoBodyAux = expMinusDtV.sampleAuxFromForce(constForce);
    mem += twoBodyAux.getMemory();

    twoBodySample = expMinusDtV.getTwoBodySampleFromAuxForce(twoBodyAux, constForce);
    mem += twoBodySample.getMemory();

    mem += phiT.getMemory();
    mem += walker[0].getMemory() * method.walkerSizePerThread;

    WalkerWalkerOperation walkerWalkerOperation(phiT, walker[0]);
    mixedMeasure.addMeasurement(walkerWalkerOperation, 1.0);
    mem += walkerWalkerOperation.getMemory();
    mem += mixedMeasure.getMemory();
    mixedMeasure.reSet();

    //Make a slightly big estimation for uncounted memory.
    mem*=1.2;
    if(MPIRank()==0)
    {
        cout<<"Memory need for this program is roughly: "<<mem/1e9<<"G per process."<<endl;
        cout<<"Please make sure available memory is larger than this.\n"<<endl;
    }
}

void AfqmcPhaseless::measureWithoutProjection()
{
    if( MPIRank() == 0 ) cout<<"Measure without projection."<<endl;

    projectExpMinusHalfDtK();
    addMeasurement();
    writeAndResetMeasurement();
}

void AfqmcPhaseless::measureWithProjection()
{
    if( MPIRank() == 0 ) cout<<"Start the projection..."<<endl;

    projectExpMinusHalfDtK();

    size_t mgsIndex(0), popControlIndex(0);
    for(size_t i = 0; i < method.timesliceSize; ++i)
    {
        if (MPIRank() == 0) cout << i << endl;

        if (method.isETAndBackGroundAdjustable)
        {
            if (i < method.ETAndBackGroundAdjustMaxSize)
            {
                if (i % method.ETAndBackGroundAdjustStep == 0)
                {
                    addMeasurement();
                    adjustETAndBackGroundThenResetMeasurement();
                }
            }

            if (i == method.ETAndBackGroundAdjustMaxSize-1)
            {
                if( !method.isETAndBackGroundGrowthEstimable )
                {
                    expMinusDtK     = model.returnExpMinusAlphaK(  method.dt     );
                    expMinusHalfDtK = model.returnExpMinusAlphaK(  method.dt*0.5 );
                    expHalfDtK      = model.returnExpMinusAlphaK( -method.dt*0.5 );
                }
            }
        }

        if (method.isETAndBackGroundGrowthEstimable)
        {
            if (i < method.ETAndBackGroundGrowthEstimateMaxSize && i >= method.ETAndBackGroundAdjustMaxSize)
            {
                if ( (i + 1 - method.ETAndBackGroundAdjustMaxSize) % method.ETAndBackGroundGrowthEstimateStep == 0 )
                {
                    addMeasurement();
                }

                if ( i == (method.ETAndBackGroundGrowthEstimateMaxSize - 1) )
                {
                    adjustETAndBackGroundThenResetMeasurement();
                    expMinusDtK     = model.returnExpMinusAlphaK(  method.dt     );
                    expMinusHalfDtK = model.returnExpMinusAlphaK(  method.dt*0.5 );
                    expHalfDtK      = model.returnExpMinusAlphaK( -method.dt*0.5 );
                }
            }
        }

        projectExpMinusDtKExpMinusDtV();

        mgsIndex++;
        if (mgsIndex == method.mgsStep)
        {
            modifyGM( method.isMgsStepAdjustable );
            mgsIndex = 0;
        }

        popControlIndex++;
        if (popControlIndex == method.popControlStep )
        {
            popControl( method.isPopControlStepAdjustable );
            popControlIndex = 0;
        }

        if (i >= method.thermalSize)
        {
            if ((i + 1 - method.thermalSize) % method.measureSkipStep == 0)
            {
                addMeasurement();
            }

            if ((i + 1 - method.thermalSize) % method.writeSkipStep == 0)
            {
                if (MPIRank() == 0)
                {
                    writeFile(method.dt * (i - method.writeSkipStep * 0.5 + 0.5), "beta.dat", ios::app);
                }
                writeAndResetMeasurement();
            }
        }
    }
}

void AfqmcPhaseless::prepareStop()
{
    if( MPIRank()==0 ) method.write("afqmc_param");
    if( MPIRank()==0 ) model.writeBackGround("model_param");
    projectExpHalfDtK();
    writeWalkers();
    randomHaoSave();
}