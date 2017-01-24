//
// Created by boruoshihao on 1/15/17.
//

#include "../include/afqmcMetropolis.h"

using namespace std;
using namespace tensor_hao;

AfqmcMetropolis::AfqmcMetropolis() { }

AfqmcMetropolis::~AfqmcMetropolis() { }

void AfqmcMetropolis::run()
{
    initialParameters();

    estimateMemory();

    if( method.timesliceSize == 0  )
    {
        measureWithoutProjection();
    }
    else
    {
        initialWalkerAndField();
        thermal();
        measure();
        prepareStop();
    }
}

void AfqmcMetropolis::initialParameters()
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

    updateNumber=0;
    acceptNumber=0;
    singleUpdateNumber=0;
    singleAcceptNumber=0;
    commuteMeasure.setModel(model);
    observeMeasure.setModel(model);
}

void AfqmcMetropolis::estimateMemory()
{
    //TODO: TO BE ADDED.
}

void AfqmcMetropolis::measureWithoutProjection()
{
    WalkerRight walkerRight;
    WalkerLeft walkerLeft;

    initialWalker(walkerLeft, walkerRight);
    addMeasurement(walkerLeft, walkerRight);
    writeAndResetMeasurement();
}

void AfqmcMetropolis::initialWalkerAndField()
{
    WalkerRight walkerRight;
    WalkerLeft walkerLeft;

    initialWalker(walkerLeft, walkerRight);
    initialField(walkerLeft, walkerRight);
}

void AfqmcMetropolis::thermal()
{
    if( MPIRank()==0 ) cout<<"Start thermal sweep..."<<endl;
    for(size_t i = 0; i < method.thermalSweep; ++i)
    {
        if( MPIRank()==0 ) cout<<i<<endl;
        updateOneSweep(false);
    }
    if( MPIRank()==0 ) cout<<endl;
}

void AfqmcMetropolis::measure()
{
    if( MPIRank()==0 ) cout<<"Start measure sweep..."<<endl;
    for(size_t i = 0; i < method.measureSweep; ++i)
    {
        if( MPIRank()==0 ) cout<<i<<endl;
        updateOneSweep(true);

        if( (i+1) % method.writeSweep == 0 )
        {
            writeAndResetMeasurement();
        }
    }
    if( MPIRank()==0 ) cout<<endl;
}

void AfqmcMetropolis::prepareStop()
{
    calculateAndPrintAcceptRatio();
    writeField();
    randomHaoSave();
}