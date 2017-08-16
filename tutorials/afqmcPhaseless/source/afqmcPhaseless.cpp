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

    initialMeasure();

    estimateMemory();

    if( std::abs(method.dt) < 1e-12 ) measureWithoutProjection();
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

    isETAndBackGroundAdjustable=false;
    numberOfGrowthMeasure=0;
    if( method.ETAndBackGroundAdjustMaxSize > 0 ) isETAndBackGroundAdjustable=true;
    if( method.ETAndBackGroundAdjustMaxSize < method.ETAndBackGroundGrowthEstimateMaxSize )
    {
        numberOfGrowthMeasure=(method.ETAndBackGroundGrowthEstimateMaxSize-method.ETAndBackGroundAdjustMaxSize)/method.ETAndBackGroundGrowthEstimateStep;
        if( numberOfGrowthMeasure > 0 ) isETAndBackGroundAdjustable=true;
    }

    if( isETAndBackGroundAdjustable )
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

void AfqmcPhaseless::initialMeasure()
{
    mixedMeasure.setModelWalker(model, phiT);
}

void AfqmcPhaseless::estimateMemory()
{
    double mem(0.0);
    mem += model.getMemory();
    if( isETAndBackGroundAdjustable )
    {
        //We will allocate expMinusHalfDtK... later, add twice here.
        mem += ( logExpMinusHalfDtK.getMemory()+logExpHalfDtK.getMemory()+logExpMinusDtK.getMemory() ) * 2.0;
    }
    else
    {
        mem += expMinusHalfDtK.getMemory()+expHalfDtK.getMemory()+expMinusDtK.getMemory();
    }
    mem += expMinusDtV.getMemory();

    mem += constForce.getMemory()*2.0;

    twoBodyAux = expMinusDtV.sampleAuxFromForce(constForce);
    mem += twoBodyAux.getMemory();

    twoBodySample = expMinusDtV.getTwoBodySampleFromAuxForce(twoBodyAux, constForce);
    mem += twoBodySample.getMemory();

    mem += phiT.getMemory();
    mem += ( walker[0].getMemory()+1.0 ) * method.walkerSizePerThread;

    walkerWalkerOperation.set(phiT, walker[0]);
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
    addMixedMeasurement();
    writeAndResetMeasurement();
}

void AfqmcPhaseless::measureWithProjection()
{
    if( MPIRank() == 0 ) cout<<"Start the projection..."<<endl;

    double beta;

    beta = (method.thermalSize+method.writeNumber*method.measureNumberPerWrite*method.measureSkipStep)*method.dt;
    if( MPIRank() == 0 ) cout<<"Total beta will be "<<beta<<endl;

    projectExpMinusHalfDtK();

    size_t mgsIndex(0), popControlIndex(0);

    if( MPIRank() == 0 ) cout<<"\nThermalize..."<<endl;

    for (size_t i = 0; i < method.thermalSize; ++i)
    {
        if ( i<method.ETAndBackGroundAdjustMaxSize )
        {
            if ( i%method.ETAndBackGroundAdjustStep == 0 )
            {
                addMixedMeasurement();
                adjustETAndBackGroundThenResetMeasurement();
            }
        }

        if (i == method.ETAndBackGroundAdjustMaxSize-1)
        {
            if( numberOfGrowthMeasure==0 )
            {
                expMinusDtK     = model.returnExpMinusAlphaK(  method.dt     );
                expMinusHalfDtK = model.returnExpMinusAlphaK(  method.dt*0.5 );
                expHalfDtK      = model.returnExpMinusAlphaK( -method.dt*0.5 );
            }
        }

        if ( numberOfGrowthMeasure>0 )
        {
            if (i < method.ETAndBackGroundGrowthEstimateMaxSize && i >= method.ETAndBackGroundAdjustMaxSize)
            {
                if ( (i + 1 - method.ETAndBackGroundAdjustMaxSize) % method.ETAndBackGroundGrowthEstimateStep == 0 )
                {
                    addMixedMeasurement();
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

        if( MPIRank() == 0 ) cout<<i*method.dt<<endl;
        projectOneStep(mgsIndex, popControlIndex);
    }

    if( MPIRank() == 0 ) cout<<"\nMeasure..."<<endl;

    for (size_t i = 0; i < method.writeNumber; ++i)
    {
        for (size_t j = 0; j < method.measureNumberPerWrite; ++j)
        {
            addMixedMeasurement();

            for (size_t k = 0; k < method.measureSkipStep; ++k)
            {
                beta = ( method.thermalSize+k+j*method.measureSkipStep
                         +i*method.measureSkipStep*method.measureNumberPerWrite)*method.dt;
                if (MPIRank() == 0) cout << beta << endl;
                projectOneStep(mgsIndex, popControlIndex);
            }
        }

        beta = ( method.thermalSize+(i+0.5)*method.measureNumberPerWrite*method.measureSkipStep-0.5 )*method.dt;
        if (MPIRank() == 0) writeFile( beta, "beta.dat", ios::app);
        writeAndResetMeasurement();
    }
}

void AfqmcPhaseless::prepareStop()
{
    if( MPIRank()==0 ) method.write("afqmc_param");
    if( MPIRank()==0 ) model.writeBackGround("model_param");
    projectExpHalfDtK();
    writeWalkers();
    randomHaoSave();

    if( isETAndBackGroundAdjustable )
    {
        if( MPIRank()==0 ) cout<<"logOneBodyWalkerRightOperation information: "<<endl;
        logOneBodyWalkerRightOperation.print();
    }
}