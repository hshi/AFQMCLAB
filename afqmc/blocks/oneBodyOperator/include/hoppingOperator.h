//
// Created by boruoshihao on 12/28/16.
//

#ifndef AFQMCLAB_HOPPINGOPERATOR_H
#define AFQMCLAB_HOPPINGOPERATOR_H

#include "../../../../common/tensorHao/include/tensor_all.h"

class HoppingOperator
{
 private:
    std::complex<double> logw;
    tensor_hao::TensorHao<std::complex<double>,2> op;

 public:
    HoppingOperator();
    HoppingOperator(std::complex<double> logw, const tensor_hao::TensorHao<std::complex<double>,2> &op);
    HoppingOperator(std::complex<double> logw, tensor_hao::TensorHao<std::complex<double>,2> &&op);
    HoppingOperator(const HoppingOperator& x);
    HoppingOperator(HoppingOperator&& x);
    ~HoppingOperator();

    HoppingOperator & operator  = (const HoppingOperator& x);
    HoppingOperator & operator  = (HoppingOperator&& x);

    const std::complex<double> &getLogw() const;
    const tensor_hao::TensorHao<std::complex<double>, 2> &getOp() const;
    size_t getL() const;

 private:
    void copy_deep(const HoppingOperator &x);
    void move_deep(HoppingOperator &x);
};

#endif //AFQMCLAB_HOPPINGOPERATOR_H