//
// Created by boruoshihao on 9/26/16.
//

#ifndef AFQMCLAB_LANCZOSBASISWF_H
#define AFQMCLAB_LANCZOSBASISWF_H

#include <complex>
#include "../../../common/tensorHao/include/tensor_all.h"

class LanczosBasisWf
{
    tensor_hao::TensorHao<std::complex<double>, 1> wf;
 public:
    LanczosBasisWf();
    LanczosBasisWf(size_t L);
    LanczosBasisWf(const tensor_hao::TensorHao<std::complex<double>, 1> &wf);
    LanczosBasisWf(tensor_hao::TensorHao<std::complex<double>, 1> &&wf);
    LanczosBasisWf(const LanczosBasisWf &x);
    LanczosBasisWf(LanczosBasisWf &&x);

    LanczosBasisWf& operator=(const tensor_hao::TensorHao<std::complex<double>, 1> &wf);
    LanczosBasisWf& operator=(tensor_hao::TensorHao<std::complex<double>, 1> &&wf);
    LanczosBasisWf& operator=(std::complex<double> x);
    LanczosBasisWf& operator=(const LanczosBasisWf& x);
    LanczosBasisWf& operator=(LanczosBasisWf&& x);

    const tensor_hao::TensorHao<std::complex<double>, 1> &getWf() const;
    tensor_hao::TensorHao<std::complex<double>, 1> &wfRef();
    size_t size() const;
    void resize(size_t L);

    void randomFill();
    void scale(std::complex<double> alpha);
    void addEqual(std::complex<double> alpha, const LanczosBasisWf &wfAdd);
    std::complex<double> calculateOverlapWith(const LanczosBasisWf &wfRight) const;
    void orthogonalizeWith(const LanczosBasisWf &wfBase);
    double normalize();
    void orthonormalizeWith(const LanczosBasisWf &wfBase);

    void read(const std::string& filename);
    void write(const std::string& filename) const;
 private:
    void copyDeep(const tensor_hao::TensorHao<std::complex<double>, 1> &wf);
    void moveDeep(tensor_hao::TensorHao<std::complex<double>, 1>& wf);
};

#endif //AFQMCLAB_LANCZOSBASISWF_H