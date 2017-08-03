//
// Created by boruoshihao on 1/9/17.
//

#ifndef AFQMCLAB_NIUPNIDNSAMPLE_H
#define AFQMCLAB_NIUPNIDNSAMPLE_H

#include "../../../../../common/tensorHao/include/tensor_all.h"

class NiupNidnSample
{
 public:
    std::complex<double> logw;
    tensor_hao::TensorHao<std::complex<double>,1> diag00, diag10, diag01, diag11;

    NiupNidnSample();
    NiupNidnSample(size_t L);
    NiupNidnSample(const NiupNidnSample &x);
    NiupNidnSample(NiupNidnSample &&x);
    ~NiupNidnSample();

    NiupNidnSample & operator  = (const NiupNidnSample& x);
    NiupNidnSample & operator  = (NiupNidnSample&& x);

    size_t getL() const;
    double getMemory() const;

 private:
    void copy_deep(const NiupNidnSample &x);
    void move_deep(NiupNidnSample &x);
};

#endif //AFQMCLAB_NIUPNIDNSAMPLE_H