//
// Created by boruoshihao on 1/13/17.
//

#ifndef AFQMCLAB_HUBBARDSOCSDSDMEASURE_H
#define AFQMCLAB_HUBBARDSOCSDSDMEASURE_H

#include "HubbardSOC.h"
#include "../../../blocks/walkerWalkerOperation/SDSDOperation/include/SDSDOperation.h"

class HubbardSOCSDSDMeasure
{
 private:
    const HubbardSOC * hubbardSOC;
    std::complex<double> den;
    std::complex<double> HNum, KNum, VNum, RNum;
    tensor_hao::TensorHao<std::complex<double>, 2> greenMatrixNum;
    tensor_hao::TensorHao<std::complex<double>, 2> densityDensityNum;
    tensor_hao::TensorHao<std::complex<double>, 2> splusSminusNum;
    tensor_hao::TensorHao<std::complex<double>, 2> sminusSplusNum;
    tensor_hao::TensorHao<std::complex<double>, 2> spairSpairNum;

 public:
    HubbardSOCSDSDMeasure();
    HubbardSOCSDSDMeasure(const HubbardSOC &hubbardSOC_);
    ~HubbardSOCSDSDMeasure();

    void setModel(const HubbardSOC &hubbardSOC_);
    void reSet();
    void addMeasurement(SDSDOperation &sdsdOperation, std::complex<double> denIncrement);
    void write();
 private:
    void addEnergy(const tensor_hao::TensorHao<std::complex<double>, 2> &greenMatrix, std::complex<double> denIncrement);
    void addGreenMatrix(const tensor_hao::TensorHao<std::complex<double>, 2> &greenMatrix, std::complex<double> denIncrement);
    void addDensityDensity(const tensor_hao::TensorHao<std::complex<double>, 2> &greenMatrix, std::complex<double> denIncrement);
    void addSplusSminus(const tensor_hao::TensorHao<std::complex<double>, 2> &greenMatrix, std::complex<double> denIncrement);
    void addSminusSplus(const tensor_hao::TensorHao<std::complex<double>, 2> &greenMatrix, std::complex<double> denIncrement);
    void addSpairSpair(const tensor_hao::TensorHao<std::complex<double>, 2> &greenMatrix, std::complex<double> denIncrement);

    HubbardSOCSDSDMeasure(const HubbardSOCSDSDMeasure& x);
    HubbardSOCSDSDMeasure & operator  = (const HubbardSOCSDSDMeasure& x);
};

#endif //AFQMCLAB_HUBBARDSOCSDSDMEASURE_H