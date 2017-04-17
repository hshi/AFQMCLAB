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

    if( method.timesliceSize == 0  )
    {
        measureWithoutProjection();
    }
    else
    {
        initialPhiT();

        for(size_t i = 0; i < method.loopSize; ++i)
        {
            initialWalker();
        }
//        prepareStop();
    }
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
    mem += expMinusDtK.getMemory();
    mem += expMinusHalfDtK.getMemory();
    mem += expHalfDtK.getMemory();
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
    initialPhiT();
    initialWalker();
    writeAndResetMeasurement();
}


void AfqmcConstraintPath::prepareStop()
{
    writeWalkers();
    randomHaoSave();
}

