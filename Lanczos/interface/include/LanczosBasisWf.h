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
    LanczosBasisWf(HAO_INT L);
    LanczosBasisWf(const tensor_hao::TensorHao<std::complex<double>, 1> &wf);
    LanczosBasisWf(tensor_hao::TensorHao<std::complex<double>, 1> &&wf);
    LanczosBasisWf(const LanczosBasisWf &x);
    LanczosBasisWf(LanczosBasisWf &&x);

    LanczosBasisWf& operator=(const LanczosBasisWf& x);
    LanczosBasisWf& operator=(LanczosBasisWf&& x);

    const tensor_hao::TensorHao<std::complex<double>, 1> &getWf() const;
    void normalize();
    std::complex<double> calculateOverlapWith(const LanczosBasisWf &wfRight) const;
    void orthogonalizeWith(const LanczosBasisWf &wfBase);
    //TODO: add orthonormalizeWith
    //TODO: read and write
    //TODO: add_equal a * wf
    //TODO: maybe swap?
    //TODO: read note, learn about next ==> careful about 2x2 Lanczos matrix case?
    //TODO: How about dynamic case?
 private:
    void copyDeep(const LanczosBasisWf &x);
    void moveDeep(LanczosBasisWf& x);
};

#endif //AFQMCLIB_LANCZOSBASISWF_H
