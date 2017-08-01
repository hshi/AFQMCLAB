//
// Created by boruoshihao on 1/13/17.
//

#ifndef AFQMCLAB_HUBBARDSOCSDSDMEASURECOMMUTE_H
#define AFQMCLAB_HUBBARDSOCSDSDMEASURECOMMUTE_H

#include "HubbardSOC.h"
#include "../../../blocks/walkerWalkerOperation/SDSDOperation/include/SDSDOperation.h"

class HubbardSOCMeasureCommuteSDSD
{
 private:
    const HubbardSOC * hubbardSOC;
    std::complex<double> den;
    std::complex<double> HNum, KNum, VNum, RNum;

 public:
    HubbardSOCMeasureCommuteSDSD();
    HubbardSOCMeasureCommuteSDSD(const HubbardSOC &hubbardSOC_);
    ~HubbardSOCMeasureCommuteSDSD();

    const HubbardSOC *getHubbardSOC() const;

    void initModelNullptr();
    void setModel(const HubbardSOC &hubbardSOC_);
    void reSet();
    std::complex<double> returnEnergy();
    void addMeasurement(SDSDOperation &sdsdOperation, std::complex<double> denIncrement);
    void write() const;
    void writeKNumVumRum() const;
    double getMemory() const;

 private:
    void addEnergy(const tensor_hao::TensorHao<std::complex<double>, 2> &greenMatrix, std::complex<double> denIncrement);
    HubbardSOCMeasureCommuteSDSD(const HubbardSOCMeasureCommuteSDSD& x);
    HubbardSOCMeasureCommuteSDSD & operator  = (const HubbardSOCMeasureCommuteSDSD& x);
};

#endif //AFQMCLAB_HUBBARDSOCSDSDMEASURECOMMUTE_H