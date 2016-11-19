//
// Created by boruoshihao on 10/28/16.
//

#ifndef AFQMCLIB_LANCZOSBASIS_H
#define AFQMCLIB_LANCZOSBASIS_H

#include <cstddef>
#include "../../../../libhao/tensorHao/include/tensor_all.h"

struct TableElement
{
    size_t index;
    int coefficient;
};

class LanczosBasis
{
    size_t sizeOfBasis, numberOfParticle, index;

    tensor_hao::TensorHao<size_t,1> positionOfParticle,emptyPositionForParticle;
    tensor_hao::TensorHao<size_t,1> tempPositionOfParticle;
    tensor_hao::TensorHao<size_t,2> binomialTable;

 public:
    LanczosBasis(size_t L, size_t N);

    size_t getSizeOfBasis() const;
    size_t getNumberOfParticle() const;
    size_t getIndex() const;
    const tensor_hao::TensorHao<size_t,1> &getPositionOfParticle() const;
    const tensor_hao::TensorHao<size_t, 1> &getEmptyPositionForParticle() const;
    const tensor_hao::TensorHao<size_t,2> &getBinomialTable() const;

    void init();
    int next();
    void reSet(size_t index);
    size_t getIndexFromPosition(const tensor_hao::TensorHao<size_t,1> &position);

    TableElement getInfoByCiDaggerCj(size_t i, size_t j);
 private:
    void setPositions();
    void setBinomialTable();

    LanczosBasis(const LanczosBasis& x);
    LanczosBasis & operator  = (const LanczosBasis& x);
};

#endif //AFQMCLIB_LANCZOSBASIS_H