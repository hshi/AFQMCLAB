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
    tensor_hao::TensorHao<OneDensityDensityOperator,1> op;

 public:
    DensityDensityOperator();
    DensityDensityOperator(size_t L);
    DensityDensityOperator(const DensityDensityOperator& x);
    DensityDensityOperator(DensityDensityOperator&& x);
    ~DensityDensityOperator();

    DensityDensityOperator & operator  = (const DensityDensityOperator& x);
    DensityDensityOperator & operator  = (DensityDensityOperator&& x);

//    const std::complex<double> &getLogw() const;
//    const tensor_hao::TensorHao<std::complex<double>, 2> &getOp() const;
//    std::complex<double> &logwRef();
//    tensor_hao::TensorHao<std::complex<double>, 2> &opRef();
//    size_t getL() const;
//
 private:
    void copy_deep(const DensityDensityOperator &x);
    void move_deep(DensityDensityOperator &x);
};

#endif //AFQMCLAB_DENSITYDENSITYOPERATOR_H