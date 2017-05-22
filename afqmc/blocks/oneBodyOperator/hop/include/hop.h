//
// Created by boruoshihao on 12/28/16.
//

#ifndef AFQMCLAB_HOP_H
#define AFQMCLAB_HOP_H

#include "../../../../../common/tensorHao/include/tensor_all.h"

//One body operator.

class Hop
{
 public:
    std::complex<double> logw;
    tensor_hao::TensorHao<std::complex<double>,2> matrix;

    Hop();
    Hop(size_t L);
    Hop(const Hop& x);
    Hop(Hop&& x);
    ~Hop();

    Hop & operator  = (const Hop& x);
    Hop & operator  = (Hop&& x);

    size_t getL() const;
    double getMemory() const;

 private:
    void copy_deep(const Hop &x);
    void move_deep(Hop &x);
};

#endif //AFQMCLAB_HOP_Hcd