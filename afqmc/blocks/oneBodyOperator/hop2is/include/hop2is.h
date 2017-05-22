//
// Created by boruoshihao on 5/18/17.
//

#ifndef AFQMCLAB_HOP2IS_H
#define AFQMCLAB_HOP2IS_H

#include "../../../../../common/tensorHao/include/tensor_all.h"

//One body operator: two identical spin species.

class Hop2is
{
 public:
    std::complex<double> logw;
    tensor_hao::TensorHao<std::complex<double>,2> matrix;

    Hop2is();
    Hop2is(size_t L);
    Hop2is(const Hop2is& x);
    Hop2is(Hop2is&& x);
    ~Hop2is();

    Hop2is & operator  = (const Hop2is& x);
    Hop2is & operator  = (Hop2is&& x);

    size_t getL() const;
    double getMemory() const;

 private:
    void copy_deep(const Hop2is &x);
    void move_deep(Hop2is &x);
};

#endif //AFQMCLAB_HOP2IS_H
