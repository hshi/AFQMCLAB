//
// Created by boruoshihao on 1/15/17.
//

#include "../include/afqmcMetropolis.h"
#include "../../../../common/common.h"

using namespace std;
using namespace tensor_hao;

AfqmcMetropolis::AfqmcMetropolis() { }

AfqmcMetropolis::~AfqmcMetropolis() { }

void AfqmcMetropolis::run()
{
    TimerHao timer;
    timer.start();
    if( MPIRank()==0 ) { cout<<"\nStart time:\n";timer.printCurrentTime(); }

    initialParameters();
    estimateMemory();

    timer.end();
    if( MPIRank()==0 ) { cout<<"\n\nEnd time:\n";timer.printCurrentTime(); }
    if( MPIRank()==0 ) { cout<<"The program's running walltime is:\n"; timer.printFormat();}
}

void AfqmcMetropolis::initialParameters()
{
    if( MPIRank()==0 ) method.read("afqmc_param");
    MPIBcast(method);

    randomHaoInit(method.seed, 1);
    if( method.seed != -1 ) randomHaoSave();
    randomHaoBackup();

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
