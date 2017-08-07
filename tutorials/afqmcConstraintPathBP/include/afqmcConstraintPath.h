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

    OneBodyWalkerRightOperation oneBodyWalkerRightOperation;
    OneBodyWalkerLeftOperation oneBodyWalkerLeftOperation;
    TwoBodySampleWalkerRightOperation twoBodySampleWalkerRightOperation;
    TwoBodySampleWalkerLeftOperation twoBodySampleWalkerLeftOperation;

    TwoBodyAux twoBodyAux;
    TwoBodySample twoBodySample;

    WalkerLeft phiT;
    std::vector<WalkerRight> walker;
    std::vector<bool> walkerIsAlive;

    WalkerWalkerOperation walkerWalkerOperation;
    ModelMeasureObserve observeMeasure;

    bool isBP;
    size_t BPIndex;
    std::vector<WalkerRight> walkerBackup, walkerBPMeasure;
    std::vector<std::vector<TwoBodyAux>> twoBodyAuxBackup, twoBodyAuxBPMeasure;
    std::vector<std::vector<int>> tablePerThreadBackup;
 public:
    AfqmcConstraintPath();
    ~AfqmcConstraintPath();

    void run();
    void initialParameters();
    void initialMeasure();
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
    void projectOneStep(size_t &mgsIndex, size_t &popControlIndex);
    void modifyGM();
    void popControl();
    void checkAndResetWalkerIsAlive();

    void addMixedMeasurement();
    void adjustETAndResetMeasurement();
    void addMeasurement();
    void writeAndResetMeasurement();

    void prepareBackPropagation();
    void prepareBackPropagationMeasAndNextBackup();
    void generateWalkerBackupFromWalkerBPMeasure();
};

#endif //AFQMCLAB_AFQMCCONSTRAINTPATH_H