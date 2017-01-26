//
// Created by boruoshihao on 1/13/17.
//

#ifndef AFQMCLAB_HUBBARDSOCSDSDMEASUREOBSERVE_H
#define AFQMCLAB_HUBBARDSOCSDSDMEASUREOBSERVE_H

#include "HubbardSOCSDSDMeasureCommute.h"

class HubbardSOCSDSDMeasureObserve : public HubbardSOCSDSDMeasureCommute
{
 private:
    tensor_hao::TensorHao<std::complex<double>, 2> greenMatrixNum;
    tensor_hao::TensorHao<std::complex<double>, 2> densityDensityNum;
    tensor_hao::TensorHao<std::complex<double>, 2> splusSminusNum;
    tensor_hao::TensorHao<std::complex<double>, 2> sminusSplusNum;
    tensor_hao::TensorHao<std::complex<double>, 2> spairSpairNum;

 public:
    HubbardSOCSDSDMeasureObserve();
    HubbardSOCSDSDMeasureObserve(const HubbardSOC &hubbardSOC_);
    ~HubbardSOCSDSDMeasureObserve();

    void reSet();
    tensor_hao::TensorHao< std::complex<double>, 2 > addMeasurement(SDSDOperation &sdsdOperation, std::complex<double> denIncrement);
    void write();

 private:
    void addGreenMatrix(const tensor_hao::TensorHao<std::complex<double>, 2> &greenMatrix, std::complex<double> denIncrement);
    void addDensityDensity(const tensor_hao::TensorHao<std::complex<double>, 2> &greenMatrix, std::complex<double> denIncrement);
    void addSplusSminus(const tensor_hao::TensorHao<std::complex<double>, 2> &greenMatrix, std::complex<double> denIncrement);
    void addSminusSplus(const tensor_hao::TensorHao<std::complex<double>, 2> &greenMatrix, std::complex<double> denIncrement);
    void addSpairSpair(const tensor_hao::TensorHao<std::complex<double>, 2> &greenMatrix, std::complex<double> denIncrement);

    HubbardSOCSDSDMeasureObserve(const HubbardSOCSDSDMeasureObserve& x);
    HubbardSOCSDSDMeasureObserve & operator  = (const HubbardSOCSDSDMeasureObserve& x);
};

#endif //AFQMCLAB_HUBBARDSOCSDSDMEASUREOBSERVE_H