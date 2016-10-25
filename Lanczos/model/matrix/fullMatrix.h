//
// Created by boruoshihao on 10/25/16.
//

#ifndef AFQMCLIB_FULLMATRIX_H
#define AFQMCLIB_FULLMATRIX_H

#include "../../interface/include/modelInterface.h"
#include "../../interface/include/LanczosBasisWf.h"

class FullMatrix : public ModelInterface
{
    tensor_hao::TensorHao<std::complex<double>, 2> Hm;
 public:

    const tensor_hao::TensorHao<std::complex<double>, 2> &getHm() const;

    void resize(size_t L);

    virtual size_t getWfSize() const;

    virtual void applyHToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const;

    virtual void projectSymmetry(LanczosBasisWf &wf) const;
};

#endif //AFQMCLIB_FULLMATRIX_H