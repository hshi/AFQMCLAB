//
// Created by boruoshihao on 7/8/17.
//

#ifndef AFQMCLAB_AFQMCPHASELESS_H
#define AFQMCLAB_AFQMCPHASELESS_H

#include "afqmcPhaselessDefine.h"
#include "afqmcPhaselessMethod.h"

class AfqmcPhaseless
{
 private:
    AfqmcPhaselessMethod method;
    Model model;
    OneBody expMinusDtK, expMinusHalfDtK, expHalfDtK;
    LogOneBody logExpMinusDtK, logExpMinusHalfDtK, logExpHalfDtK;
    TwoBody expMinusDtV;
    TwoBodyForce dynamicForce, constForce;

    OneBodyWalkerRightOperation oneBodyWalkerRightOperation;
    LogOneBodyWalkerRightOperation logOneBodyWalkerRightOperation;
    TwoBodySampleWalkerRightOperation twoBodySampleWalkerRightOperation;

    TwoBodyAux twoBodyAux;
    TwoBodySample twoBodySample;

    WalkerLeft phiT;
    std::vector<WalkerRight> walker;

    ModelMeasureMixed mixedMeasure;

 public:
    AfqmcPhaseless();
    ~AfqmcPhaseless();

    void run();
    void initialParameters();
    void initialMixedMeasure();
    void estimateMemory();
    void measureWithoutProjection();
    void measureWithProjection();
    void prepareStop();

 private:
    void initialPhiT();
    void initialWalker();
    void writeWalkers();
    void initialMgsAndPopControl();

    void projectExpHalfDtK();
    void projectExpMinusHalfDtK();
    void projectExpMinusDtKExpMinusDtV();
    void modifyGM(bool isAdjustable );
    void popControl(bool isAdjustable);

    void addMeasurement();
    void writeAndResetMeasurement();
    void adjustETAndBackGroundThenResetMeasurement();
};

#endif //AFQMCLAB_AFQMCPHASELESS_H