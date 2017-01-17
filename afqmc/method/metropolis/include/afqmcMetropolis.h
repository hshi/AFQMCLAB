//
// Created by boruoshihao on 1/15/17.
//

#ifndef AFQMCLAB_METROPOLIS_H
#define AFQMCLAB_METROPOLIS_H

#include "afqmcMetropolisDefine.h"
#include "afqmcMetropolisMethod.h"

class AfqmcMetropolis
{
 private:
    AfqmcMetropolisMethod method;
    Model model;
    OneBody expMinusDtK, expMinusHalfDtK, expHalfDtK;
    TwoBody expMinusDtV;
    TwoBodyForce dynamicForce, constForce;

    size_t currentTimeslice;
    std::complex<double> currentLogOverlap;
    std::vector<TwoBodyAux> auxiliaryFields;
    std::vector<WalkerRight> walkerRightInBlock, walkerRightSave;
    std::vector<WalkerLeft> walkerLeftInBlock, walkerLeftSave;
    std::vector<std::complex<double>> reWeightRightInBlock, reWeightRightSave;
    std::vector<std::complex<double>> reWeightLeftInBlock, reWeightLeftSave;

    long updateNumber, acceptNumber, singleUpdateNumber, singleAcceptNumber;
    ModelCommuteMeasure commuteMeasure;
    ModelObserveMeasure observeMeasure;

 public:
    AfqmcMetropolis();
    ~AfqmcMetropolis();

    void run();
    void initialParameters();
    void estimateMemory();
    void measureWithoutProjection();

 private:
    void initialWalker(WalkerLeft &walkerLeft, WalkerRight &walkerRight);
};

#endif //AFQMCLAB_METROPOLIS_H
