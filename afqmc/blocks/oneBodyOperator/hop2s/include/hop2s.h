//
// Created by boruoshihao on 5/17/17.
//

#ifndef AFQMCLAB_HOP2S_H
#define AFQMCLAB_HOP2S_H

#include "../../../../../common/tensorHao/include/tensor_all.h"

//One body operator: two spin species.

class Hop2s
{
 public:
    std::complex<double> logw;
    tensor_hao::TensorHao<std::complex<double>,2> matrixUp, matrixDn;

    Hop2s();
    Hop2s(size_t L);
    Hop2s(const Hop2s& x);
    Hop2s(Hop2s&& x);
    ~Hop2s();

    Hop2s & operator  = (const Hop2s& x);
    Hop2s & operator  = (Hop2s&& x);

    size_t getL() const;
    double getMemory() const;

 private:
    void copy_deep(const Hop2s &x);
    void move_deep(Hop2s &x);
};

#endif //AFQMCLAB_HOP2S_H
