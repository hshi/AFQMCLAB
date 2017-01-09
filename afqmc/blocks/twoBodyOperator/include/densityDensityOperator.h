//
// Created by boruoshihao on 12/30/16.
//

#ifndef AFQMCLAB_DENSITYDENSITYOPERATOR_H
#define AFQMCLAB_DENSITYDENSITYOPERATOR_H

#include "../../../../common/tensorHao/include/tensor_all.h"

typedef tensor_hao::TensorHao<int, 1> DensityDensityOperatorAux;
typedef tensor_hao::TensorHao<std::complex<double>, 1> DensityDensityOperatorForce;

struct OneDensityDensityOperator
{
    size_t i;
    size_t j;
    double V;
};

class DensityDensityOperator
{
 private:
    size_t L;
    std::string decompType;  //densityCharge, densitySpin, hopCharge, hopSpin, pairCharge, pairSpin
    tensor_hao::TensorHao<OneDensityDensityOperator,1> op;
    tensor_hao::TensorHao<std::complex<double>,1> gamma;

 public:
    DensityDensityOperator();
    DensityDensityOperator(size_t L, const std::string &decompType, const tensor_hao::TensorHao<OneDensityDensityOperator,1>& op);
    DensityDensityOperator(const DensityDensityOperator& x);
    DensityDensityOperator(DensityDensityOperator&& x);
    ~DensityDensityOperator();

    DensityDensityOperator & operator  = (const DensityDensityOperator& x);
    DensityDensityOperator & operator  = (DensityDensityOperator&& x);

    size_t getL() const;
    const std::string &getDecompType() const;
    const tensor_hao::TensorHao<OneDensityDensityOperator, 1> &getOp() const;
    const tensor_hao::TensorHao<std::complex<double>, 1> &getGamma() const;

    DensityDensityOperatorAux sampleAuxFromForce(const DensityDensityOperatorForce &force, double gammaForceCap=1e50);

 private:
    void copy_deep(const DensityDensityOperator &x);
    void move_deep(DensityDensityOperator &x);
    void setGamma();
};

#endif //AFQMCLAB_DENSITYDENSITYOPERATOR_H