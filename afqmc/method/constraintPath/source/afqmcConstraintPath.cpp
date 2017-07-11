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

    estimateMemory();

    initialPhiT();

    initialWalker();

    if( method.timesliceSize == 0  ) measureWithoutProjection();
    else measureWithProjection();

    prepareStop();
}

void AfqmcConstraintPath::initialParameters()
{
    if( MPIRank()==0 ) method.read("afqmc_param");
    MPIBcast(method);

    randomHaoInit(method.seed, 1);
    if( method.seed != -1 ) randomHaoSave();

    if( MPIRank()==0 ) model.read("model_param");
    MPIBcast(model);

    expMinusDtK     = model.returnExpMinusAlphaK(  method.dt     );
    expMinusHalfDtK = model.returnExpMinusAlphaK(  method.dt*0.5 );
    expHalfDtK      = model.returnExpMinusAlphaK( -method.dt*0.5 );

    expMinusDtV = model.returnExpMinusAlphaV( method.dt, method.decompType );
    getForce(constForce, expMinusDtV, "constForce_param");

    commuteMeasure.setModel(model);
}

void AfqmcConstraintPath::estimateMemory()
{
    double mem(0.0);
    mem += model.getMemory();
    mem += expMinusDtK.getMemory()+expMinusHalfDtK.getMemory()+expHalfDtK.getMemory();
    mem += expMinusDtV.getMemory();
    mem += constForce.getMemory() * 2.0;

    twoBodyAux = expMinusDtV.sampleAuxFromForce(constForce, method.sampleCap);
    mem += twoBodyAux.getMemory();

    fillWalkerRandomly(phiT, model);
    mem += phiT.getMemory();
    WalkerRight walker; fillWalkerRandomly(walker, model);
    mem += walker.getMemory() * method.walkerSizePerThread;

    WalkerWalkerOperation walkerWalkerOperation(phiT, walker);
    ModelCommuteMeasure commuteMeasure(model);
    commuteMeasure.addMeasurement(walkerWalkerOperation, 1.0);
    mem += walkerWalkerOperation.getMemory();
    mem += commuteMeasure.getMemory();

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
    addMeasurement();
    writeAndResetMeasurement();
}

void AfqmcConstraintPath::measureWithProjection()
{
    projectExpMinusHalfDtK();

    setET();

    if( MPIRank() == 0 ) cout<<"Start the projection..."<<endl;

    for(size_t i = 0; i < method.timesliceSize; ++i)
    {
        if( MPIRank() == 0 ) cout<<i<<endl;

        projectExpMinusDtKExpMinusDtV();

        if( (i+1)%method.stabilizeStep == 0 )
        {
            modifyGM();
        }

        if( (i+1)%method.populationControlStep == 0 )
        {
            popControl();
            if( i < method.setETMaxStep ) setET();
        }

        if( i >= method.thermalStep )
        {
            if( (i+1-method.thermalStep)%method.measureSkipTimesliceStep == 0 )
            {
                addMeasurement();
            }

            if( (i+1-method.thermalStep)%method.writeSkipTimesliceStep == 0 )
            {
                if( MPIRank()==0 )
                {
                    writeFile(method.dt * (i - method.writeSkipTimesliceStep * 0.5 + 0.5), "beta.dat", ios::app);
                }
                writeAndResetMeasurement();
            }
        }
    }
}

void AfqmcConstraintPath::prepareStop()
{
    projectExpHalfDtK();
    writeWalkers();
    randomHaoSave();
}