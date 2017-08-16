//
// Created by boruoshihao on 4/16/17.
//

#include "../include/afqmcConstraintPath.h"

using namespace std;
using namespace tensor_hao;

AfqmcConstraintPath::AfqmcConstraintPath()  { }

AfqmcConstraintPath::~AfqmcConstraintPath() { }

void AfqmcConstraintPath::run()
{
    initialParameters();

    initialPhiT();

    initialWalker();

    initialMeasure();

    estimateMemory();

    if( std::abs(method.dt) < 1e-12  ) measureWithoutProjection();
    else measureWithProjection();

    prepareStop();
}

void AfqmcConstraintPath::initialParameters()
{
    if( MPIRank()==0 ) method.read("afqmc_param");
    if( MPIRank()==0 ) method.print();
    MPIBcast(method);

    randomHaoInit(method.seed, 1);
    if( method.seed != -1 ) randomHaoSave();

    if( MPIRank()==0 ) model.read("model_param");
    MPIBcast(model);

    expMinusDtK     = model.returnExpMinusAlphaK(  method.dt     );
    expMinusHalfDtK = model.returnExpMinusAlphaK(  method.dt*0.5 );
    expHalfDtK      = model.returnExpMinusAlphaK( -method.dt*0.5 );

    expMinusDtV = model.returnExpMinusAlphaV( method.dt, method.decompType );
    constForce =expMinusDtV.readForce("constForce_param");

    isBP = false;
    walkerBackup.resize(method.walkerSizePerThread);
    walkerBPMeasure.resize(method.walkerSizePerThread);
    twoBodyAuxBackup.resize(method.walkerSizePerThread);
    twoBodyAuxBPMeasure.resize(method.walkerSizePerThread);
    for (int i = 0; i < method.walkerSizePerThread; ++i)
    {
        twoBodyAuxBackup[i].resize(method.backPropagationStep);
        twoBodyAuxBPMeasure[i].resize(method.backPropagationStep);
    }
    tablePerThreadBackup.resize(method.backPropagationStep);
}

void AfqmcConstraintPath::initialMeasure()
{
    observeMeasure.setModel(model);
}

void AfqmcConstraintPath::estimateMemory()
{
    double mem(0.0);
    mem += model.getMemory();
    mem += expMinusDtK.getMemory()+expMinusHalfDtK.getMemory()+expHalfDtK.getMemory();
    mem += expMinusDtV.getMemory();

    mem += constForce.getMemory() * 2.0;

    twoBodyAux = expMinusDtV.sampleAuxFromForce(constForce);
    mem += twoBodyAux.getMemory();

    twoBodySample = expMinusDtV.getTwoBodySampleFromAuxForce(twoBodyAux, constForce);
    mem += twoBodySample.getMemory();

    mem += phiT.getMemory();
    mem += ( walker[0].getMemory()+1.0 ) * method.walkerSizePerThread;

    walkerWalkerOperation.set(phiT, walker[0]);
    observeMeasure.addMeasurement(walkerWalkerOperation, 1.0);
    mem += walkerWalkerOperation.getMemory();
    mem += observeMeasure.getMemory();
    observeMeasure.reSet();

    mem += 2.0 * walker[0].getMemory() * method.walkerSizePerThread;
    mem += 2.0 * method.walkerSizePerThread * method.backPropagationStep * twoBodyAux.getMemory();
    mem += 1.0 * sizeof(int) * method.walkerSizePerThread * method.backPropagationStep / method.popControlStep;

    //Make a slightly big estimation for uncounted memory.
    mem*=1.2;
    if(MPIRank()==0)
    {
        cout<<"Memory need for this program is roughly: "<<mem/1e9<<"G per process."<<endl;
        cout<<"Please make sure available memory is larger than this.\n"<<endl;
    }
}

void AfqmcConstraintPath::measureWithoutProjection()
{
    if( MPIRank() == 0 ) cout<<"Measure without projection."<<endl;

    projectExpMinusHalfDtK();
    addMixedMeasurement();
    writeAndResetMeasurement();
}

void AfqmcConstraintPath::measureWithProjection()
{
    if( MPIRank() == 0 ) cout<<"Start the projection..."<<endl;

    double beta; size_t additionalStep=method.backPropagationStep;
    if(method.backPropagationStep < method.measureSkipStep) additionalStep=0;

    beta = (method.thermalSize+method.writeNumber*method.measureNumberPerWrite*method.measureSkipStep
            + additionalStep)*method.dt;
    if( MPIRank() == 0 ) cout<<"Total beta will be "<<beta<<endl;

    projectExpMinusHalfDtK();

    size_t mgsIndex(0), popControlIndex(0);

    if( MPIRank() == 0 ) cout<<"\nThermalize..."<<endl;

    for (size_t i = 0; i < method.thermalSize; ++i)
    {
        if ( i<method.ETAdjustMaxSize )
        {
            if ( i%method.ETAdjustStep == 0 )
            {
                addMixedMeasurement();
                adjustETAndResetMeasurement();
            }
        }

        if( MPIRank() == 0 ) cout<<i*method.dt<<endl;
        projectOneStep(mgsIndex, popControlIndex);
    }

    if( MPIRank() == 0 ) cout<<"\nMeasure..."<<endl;

    prepareBackPropagation();

    if(method.backPropagationStep >= method.measureSkipStep)
    {
        for (size_t i = 0; i < method.backPropagationStep; ++i)
        {
            if (MPIRank() == 0) cout << (method.thermalSize+i)*method.dt<< endl;
            projectOneStep(mgsIndex, popControlIndex);
        }
    }

    for (size_t i = 0; i < method.writeNumber; ++i)
    {
        for (size_t j = 0; j < method.measureNumberPerWrite; ++j)
        {
            for (size_t k = 0; k < method.measureSkipStep; ++k)
            {
                if( BPIndex==method.backPropagationStep ) addMeasurement();

                beta = ( method.thermalSize+k+j*method.measureSkipStep +i*method.measureSkipStep*method.measureNumberPerWrite
                       +additionalStep )*method.dt;
                if (MPIRank() == 0) cout << beta << endl;
                projectOneStep(mgsIndex, popControlIndex);
            }
            if(method.backPropagationStep < method.measureSkipStep) prepareBackPropagation();
        }

        beta = ( method.thermalSize+(i+0.5)*method.measureNumberPerWrite*method.measureSkipStep-0.5 )*method.dt;
        if (MPIRank() == 0) writeFile( beta, "beta.dat", ios::app);
        writeAndResetMeasurement();
    }
}

void AfqmcConstraintPath::prepareStop()
{
    if( MPIRank()==0 ) method.write("afqmc_param");
    projectExpHalfDtK();
    writeWalkers();
    randomHaoSave();
}