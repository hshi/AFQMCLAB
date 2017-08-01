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

    OneBodyWalkerOperation oneBodyWalkerOperation;
    TwoBodyWalkerOperation twoBodyWalkerOperation;

    int currentTimeslice;
    std::complex<double> currentLogOverlap;
    std::vector<TwoBodyAux> auxiliaryFields;
    std::vector<WalkerRight> walkerRightInBlock, walkerRightSave;
    std::vector<WalkerLeft> walkerLeftInBlock, walkerLeftSave;
    std::vector<std::complex<double>> logWeightRightInBlock, logWeightRightSave;
    std::vector<std::complex<double>> logWeightLeftInBlock, logWeightLeftSave;

    long updateNumber, acceptNumber, singleUpdateNumber, singleAcceptNumber;
    ModelMeasureCommute commuteMeasure;
    ModelMeasureObserve observeMeasure;

    long varianceMeasureNumber, varianceSampleNumber;

 public:
    AfqmcMetropolis();
    ~AfqmcMetropolis();

    void run();
    void initialParameters();
    void estimateMemory();
    void measureWithoutProjection();
    void initialWalkerAndField();
    void thermal();
    void measure();
    void prepareStop();
 private:
    void initialWalker(WalkerLeft &walkerLeft, WalkerRight &walkerRight);
    void initialField(WalkerLeft &walkerLeft, WalkerRight &walkerRight);
    void readField();
    void writeField();

    void updateOneSweep(bool isMeasure);
    void updateToRightOneSweep(bool isMeasure);
    void updateToLeftOneSweep(bool isMeasure);
    void updateToRightOneStep(size_t inBlockIndex, WalkerLeft & walkerLeft, std::complex<double> &logWeight);
    void updateToLeftOneStep(size_t inBlockIndex, WalkerRight & walkerRight, std::complex<double> &logWeight);
    void setBlockFromRightToLeft(size_t leftBlockIndex);
    void setBlockFromLeftToRight(size_t rightBlockIndex);
    double returnLogProbOfAux(const TwoBodyAux & twoBodyAux);

    void measureWithwalkerRightInBlock(const WalkerLeft &walkerLeft, size_t inBlockIndex);
    void measureWithWalkerLeftInBlock(size_t inBlockIndex, const WalkerRight &walkerRight);
    void addMeasurement(const WalkerLeft &walkerLeft, const WalkerRight &walkerRight);
    void addMeasurementFixVariance(const WalkerLeft &walkerLeft, const WalkerRight &walkerRight, std::complex<double> logExpMinusTauHAvg);
    std::complex<double> measureLogExpMinusDtV(const WalkerLeft &walkerLeft, const WalkerRight &walkerRight);
    void writeAndResetMeasurement();
    void calculateAndPrintAcceptRatio();
    void calculateVarianceSampleRatio();
};

#endif //AFQMCLAB_METROPOLIS_H