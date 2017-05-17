//
// Created by boruoshihao on 5/17/17.
//

#ifndef AFQMCLAB_HOP2SPIN_H
#define AFQMCLAB_HOP2SPIN_H

#include "../../../../../common/tensorHao/include/tensor_all.h"

class Hop2Spin
{
 public:
    std::complex<double> logw;
    tensor_hao::TensorHao<std::complex<double>,2> matrixUp, matrixDn;

    Hop2Spin();
    Hop2Spin(size_t L);
    Hop2Spin(const Hop2Spin& x);
    Hop2Spin(Hop2Spin&& x);
    ~Hop2Spin();

    Hop2Spin & operator  = (const Hop2Spin& x);
    Hop2Spin & operator  = (Hop2Spin&& x);

    size_t getL() const;
    double getMemory() const;

 private:
    void copy_deep(const Hop2Spin &x);
    void move_deep(Hop2Spin &x);
};

#endif //AFQMCLAB_HOP2SPIN_H