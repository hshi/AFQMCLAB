//
// Created by boruoshihao on 9/26/16.
//

#ifndef AFQMCLIB_LANCZOSBASISWF_H
#define AFQMCLIB_LANCZOSBASISWF_H

#include <complex>
#include "../../../libhao/tensor_hao/include/tensor_all.h"

class LanczosBasisWf
{
    tensor_hao::TensorHao<std::complex<double>, 1> wf;
 public:
    LanczosBasisWf();
    LanczosBasisWf(int L);
    LanczosBasisWf(const tensor_hao::TensorHao<std::complex<double>, 1> &wf);
    LanczosBasisWf(tensor_hao::TensorHao<std::complex<double>, 1> &&wf);
    LanczosBasisWf(const LanczosBasisWf &x);
    LanczosBasisWf(LanczosBasisWf &&x);

    LanczosBasisWf& operator=(const LanczosBasisWf& x);
    LanczosBasisWf& operator=(LanczosBasisWf&& x);

    const tensor_hao::TensorHao<std::complex<double>, 1> &getWf() const;
    void normalize();
 private:
    void copyDeep(const LanczosBasisWf &x);
    void moveDeep(LanczosBasisWf& x);
};

#endif //AFQMCLIB_LANCZOSBASISWF_H
