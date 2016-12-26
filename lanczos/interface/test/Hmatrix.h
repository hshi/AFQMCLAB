//
// Created by boruoshihao on 12/8/16.
//

#ifndef AFQMCLAB_HMATRIX_H
#define AFQMCLAB_HMATRIX_H

#include "../include/modelInterface.h"

class Hmatrix : public ModelInterface
{
    tensor_hao::TensorHao<std::complex<double>, 2> Hm;
 public:

    const tensor_hao::TensorHao<std::complex<double>, 2> &getHm() const;

    void resize(size_t L);

    virtual size_t getWfSize() const;

    virtual void applyHToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const;

    virtual void projectSymmetry(LanczosBasisWf &wf) const;
};

#endif //AFQMCLAB_HMATRIX_H