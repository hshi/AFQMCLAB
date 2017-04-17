//
// Created by boruoshihao on 4/16/17.
//

#ifndef AFQMCLAB_AFQMCCONSTRAINTPATH_H
#define AFQMCLAB_AFQMCCONSTRAINTPATH_H

#include "afqmcConstraintPathDefine.h"
#include "afqmcConstraintPathMethod.h"

class AfqmcConstraintPath
{
 private:
    AfqmcConstraintPathMethod method;
    Model model;
    OneBody expMinusDtK, expMinusHalfDtK, expHalfDtK;
    TwoBody expMinusDtV;
    TwoBodyForce dynamicForce, constForce;
    TwoBodyAux twoBodyAux;

    WalkerLeft phiT;
    std::vector<WalkerRight> walker;

    ModelCommuteMeasure commuteMeasure;

 public:
    AfqmcConstraintPath();
    ~AfqmcConstraintPath();

    void run();
    void initialParameters();
    void estimateMemory();
    void measureWithoutProjection();
    void prepareStop();

 private:
    void initialPhiT();
    void initialWalker();
    void writeWalkers();

    void projection();
    void projectExpHalfDtK();
    void projectExpMinusHalfDtK();
    void projectExpHalfDtKExpMinusDtV();

    void modifyGM();
    void popControl();

    void addMeasurement();
    void writeAndResetMeasurement();
};

#endif //AFQMCLAB_AFQMCCONSTRAINTPATH_H
