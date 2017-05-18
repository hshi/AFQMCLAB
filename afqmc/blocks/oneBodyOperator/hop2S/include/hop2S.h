//
// Created by boruoshihao on 5/17/17.
//

#ifndef AFQMCLAB_HOP2S_H
#define AFQMCLAB_HOP2S_H

#include "../../../../../common/tensorHao/include/tensor_all.h"

//One body operator: two spin species.

class Hop2S
{
 public:
    std::complex<double> logw;
    tensor_hao::TensorHao<std::complex<double>,2> matrixUp, matrixDn;

    Hop2S();
    Hop2S(size_t L);
    Hop2S(const Hop2S& x);
    Hop2S(Hop2S&& x);
    ~Hop2S();

    Hop2S & operator  = (const Hop2S& x);
    Hop2S & operator  = (Hop2S&& x);

    size_t getL() const;
    double getMemory() const;

 private:
    void copy_deep(const Hop2S &x);
    void move_deep(Hop2S &x);
};

#endif //AFQMCLAB_HOP2S_H
