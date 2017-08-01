//
// Created by boruoshihao on 1/13/17.
//

#ifndef AFQMCLAB_HUBBARDSOCSDSDMEASUREOBSERVE_H
#define AFQMCLAB_HUBBARDSOCSDSDMEASUREOBSERVE_H

#include "HubbardSOCMeasureCommuteSDSD.h"

class HubbardSOCMeasureObserveSDSD : public HubbardSOCMeasureCommuteSDSD
{
 private:
    tensor_hao::TensorHao<std::complex<double>, 2> greenMatrixNum;
    tensor_hao::TensorHao<std::complex<double>, 2> densityDensityNum;
    tensor_hao::TensorHao<std::complex<double>, 2> splusSminusNum;
    tensor_hao::TensorHao<std::complex<double>, 2> sminusSplusNum;
    tensor_hao::TensorHao<std::complex<double>, 2> spairSpairNum;

 public:
    HubbardSOCMeasureObserveSDSD();
    HubbardSOCMeasureObserveSDSD(const HubbardSOC &hubbardSOC_);
    ~HubbardSOCMeasureObserveSDSD();

    void reSet();
    void addMeasurement(SDSDOperation &sdsdOperation, std::complex<double> denIncrement);
    void write() const;
    double getMemory() const;

 private:
    void addGreenMatrix(const tensor_hao::TensorHao<std::complex<double>, 2> &greenMatrix, std::complex<double> denIncrement);
    void addDensityDensity(const tensor_hao::TensorHao<std::complex<double>, 2> &greenMatrix, std::complex<double> denIncrement);
    void addSplusSminus(const tensor_hao::TensorHao<std::complex<double>, 2> &greenMatrix, std::complex<double> denIncrement);
    void addSminusSplus(const tensor_hao::TensorHao<std::complex<double>, 2> &greenMatrix, std::complex<double> denIncrement);
    void addSpairSpair(const tensor_hao::TensorHao<std::complex<double>, 2> &greenMatrix, std::complex<double> denIncrement);

    HubbardSOCMeasureObserveSDSD(const HubbardSOCMeasureObserveSDSD& x);
    HubbardSOCMeasureObserveSDSD & operator  = (const HubbardSOCMeasureObserveSDSD& x);
};

#endif //AFQMCLAB_HUBBARDSOCSDSDMEASUREOBSERVE_H