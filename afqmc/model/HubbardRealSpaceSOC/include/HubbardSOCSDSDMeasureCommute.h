//
// Created by boruoshihao on 1/13/17.
//

#ifndef AFQMCLAB_HUBBARDSOCSDSDMEASURECOMMUTE_H
#define AFQMCLAB_HUBBARDSOCSDSDMEASURECOMMUTE_H

#include "HubbardSOC.h"
#include "../../../blocks/walkerWalkerOperation/SDSDOperation/include/SDSDOperation.h"

class HubbardSOCSDSDMeasureCommute
{
 private:
    const HubbardSOC * hubbardSOC;
    std::complex<double> den;
    std::complex<double> HNum, KNum, VNum, RNum;

 public:
    HubbardSOCSDSDMeasureCommute();
    HubbardSOCSDSDMeasureCommute(const HubbardSOC &hubbardSOC_);
    ~HubbardSOCSDSDMeasureCommute();

    const HubbardSOC *getHubbardSOC() const;

    void initModelNullptr();
    void setModel(const HubbardSOC &hubbardSOC_);
    void reSet();
    tensor_hao::TensorHao< std::complex<double>, 2 > addMeasurement(SDSDOperation &sdsdOperation, std::complex<double> denIncrement);
    void write();
    void writeKNumVumRum();

 private:
    void addEnergy(const tensor_hao::TensorHao<std::complex<double>, 2> &greenMatrix, std::complex<double> denIncrement);
    HubbardSOCSDSDMeasureCommute(const HubbardSOCSDSDMeasureCommute& x);
    HubbardSOCSDSDMeasureCommute & operator  = (const HubbardSOCSDSDMeasureCommute& x);
};

#endif //AFQMCLAB_HUBBARDSOCSDSDMEASURECOMMUTE_H