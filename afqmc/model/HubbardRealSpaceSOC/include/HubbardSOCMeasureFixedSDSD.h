//
// Created by Hao Shi on 8/1/17.
//

#ifndef AFQMCLAB_HUBBARDSOCMEASUREFIXEDSDSD_H
#define AFQMCLAB_HUBBARDSOCMEASUREFIXEDSDSD_H

#include "HubbardSOC.h"
#include "../../../blocks/walkerWalkerOperation/SDSDOperation/include/SDSDOperation.h"

class HubbardSOCMeasureFixedSDSD
{
 private:
    const HubbardSOC * hubbardSOC;
    const SD *walkerLeft;

    std::complex<double> den;
    std::complex<double> KNum, VNum, RNum, HNum;
    tensor_hao::TensorHao<std::complex<double>, 1> NupNum, NdnNum, SplusNum, SminusNum;
    std::complex<double> NupTotNum, NdnTotNum, SplusTotNum, SminusTotNum;

    tensor_hao::TensorHao<std::complex<double>,2> wfDaggerK;

 public:
    HubbardSOCMeasureFixedSDSD();
    HubbardSOCMeasureFixedSDSD(const HubbardSOC& hubbardSOC_, const SD& walkerLeft_);
    ~HubbardSOCMeasureFixedSDSD();

    void initModelWalkerNullptr();
    void setModelWalker(const HubbardSOC& hubbardSOC_, const SD& walkerLeft_);
    void reSet();
    std::complex<double> returnEnergy();
    void addMeasurement(SDSDOperation &sdsdOperation, std::complex<double> denIncrement);
    NiupNidnForce getForce(const NiupNidn &niupNidn, SDSDOperation &sdsdOperation, double cap=1.0);

    void write() const;
    double getMemory() const;

 private:
    HubbardSOCMeasureFixedSDSD(const HubbardSOCMeasureFixedSDSD& x);
    HubbardSOCMeasureFixedSDSD & operator = (const HubbardSOCMeasureFixedSDSD& x);

    void initWfDaggerK();
    void checkWalkerLeft(const SDSDOperation &sdsdOperation);
    void addEnergy(SDSDOperation &sdsdOperation, std::complex<double> denIncrement);
    void addNupNdn(SDSDOperation &sdsdOperation, std::complex<double> denIncrement);
    void addSplusSminus(SDSDOperation &sdsdOperation, std::complex<double> denIncrement);
};


#endif //AFQMCLAB_HUBBARDSOCMEASUREFIXEDSDSD_H
