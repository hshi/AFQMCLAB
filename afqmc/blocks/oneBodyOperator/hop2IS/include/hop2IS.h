//
// Created by boruoshihao on 5/18/17.
//

#ifndef AFQMCLAB_HOP2IS_H
#define AFQMCLAB_HOP2IS_H

#include "../../../../../common/tensorHao/include/tensor_all.h"

//One body operator: two identical spin species.

class Hop2IS
{
 public:
    std::complex<double> logw;
    tensor_hao::TensorHao<std::complex<double>,2> matrix;

    Hop2IS();
    Hop2IS(size_t L);
    Hop2IS(const Hop2IS& x);
    Hop2IS(Hop2IS&& x);
    ~Hop2IS();

    Hop2IS & operator  = (const Hop2IS& x);
    Hop2IS & operator  = (Hop2IS&& x);

    size_t getL() const;
    double getMemory() const;

 private:
    void copy_deep(const Hop2IS &x);
    void move_deep(Hop2IS &x);
};

#endif //AFQMCLAB_HOP2IS_H
