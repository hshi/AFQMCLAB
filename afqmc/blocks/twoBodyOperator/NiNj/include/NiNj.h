//
// Created by boruoshihao on 12/30/16.
//

#ifndef AFQMCLAB_NINJ_H
#define AFQMCLAB_NINJ_H

#include "NiNjAux.h"
#include "NiNjForce.h"

struct OneNiNj
{
    size_t i;
    size_t j;
    double V;
};

class NiNj
{
 private:
    size_t L;
    std::string decompType;  //densityCharge, densitySpin, hopCharge, hopSpin, pairCharge, pairSpin
    tensor_hao::TensorHao<OneNiNj,1> op;
    tensor_hao::TensorHao<std::complex<double>,1> gamma;

 public:
    NiNj();
    NiNj(size_t L, const std::string &decompType, const tensor_hao::TensorHao<OneNiNj,1>& op);
    NiNj(const NiNj& x);
    NiNj(NiNj&& x);
    ~NiNj();

    NiNj & operator  = (const NiNj& x);
    NiNj & operator  = (NiNj&& x);

    size_t getL() const;
    const std::string &getDecompType() const;
    const tensor_hao::TensorHao<OneNiNj, 1> &getOp() const;
    const tensor_hao::TensorHao<std::complex<double>, 1> &getGamma() const;

    NiNjAux sampleAuxFromForce(const NiNjForce &force, double gammaForceCap=1e50);

 private:
    void copy_deep(const NiNj &x);
    void move_deep(NiNj &x);
    void setGamma();
};

#endif //AFQMCLAB_NINJ_H