//
// Created by boruoshihao on 12/30/16.
//

#ifndef AFQMCLAB_DENSITYDENSITYOPERATOR_H
#define AFQMCLAB_DENSITYDENSITYOPERATOR_H

#include "../../../../common/tensorHao/include/tensor_all.h"

struct OneDensityDensityOperator
{
    size_t i;
    size_t j;
    std::complex<double> V;
};


class DensityDensityOperator
{
 private:
    size_t L;
    std::string decompType;  //densityCharge, densitySpin, hopCharge, hopSpin, pairCharge, pairSpin
    tensor_hao::TensorHao<OneDensityDensityOperator,1> op;
    tensor_hao::TensorHao<OneDensityDensityOperator,1> gamma;

 public:
    DensityDensityOperator();
    DensityDensityOperator(size_t L, const tensor_hao::TensorHao<OneDensityDensityOperator,1>& op, const std::string &decompType);
    DensityDensityOperator(const DensityDensityOperator& x);
    DensityDensityOperator(DensityDensityOperator&& x);
    ~DensityDensityOperator();

    DensityDensityOperator & operator  = (const DensityDensityOperator& x);
    DensityDensityOperator & operator  = (DensityDensityOperator&& x);

    size_t getL() const;
    const std::string &getDecompType() const;
    const tensor_hao::TensorHao<OneDensityDensityOperator, 1> &getOp() const;
    const tensor_hao::TensorHao<OneDensityDensityOperator, 1> &getGamma() const;
 private:
    void copy_deep(const DensityDensityOperator &x);
    void move_deep(DensityDensityOperator &x);
    void setGamma();
};

#endif //AFQMCLAB_DENSITYDENSITYOPERATOR_H