//
// Created by boruoshihao on 1/8/17.
//

#ifndef AFQMCLAB_NIUPNIDN_H
#define AFQMCLAB_NIUPNIDN_H

#include "NiupNidnAux.h"
#include "NiupNidnForce.h"
#include "NiupNidnSample.h"

class NiupNidn
{
 private:
    size_t L;
    std::string decompType;  //densityCharge, densitySpin, hopCharge, hopSpin, pairCharge, pairSpin
    double dtUSum;
    tensor_hao::TensorHao<double,1> dtU;
    tensor_hao::TensorHao<std::complex<double>,1> gamma;
    tensor_hao::TensorHao<std::complex<double>,1> constDiag00, constDiag10, constDiag01, constDiag11;

 public:
    NiupNidn();
    NiupNidn(double dt,
             const std::string &decompTypeIn,
             const tensor_hao::TensorHao<double, 1> &U,
             const tensor_hao::TensorHao<double, 1> &mu,
             const tensor_hao::TensorHao<double, 1> &hx,
             const tensor_hao::TensorHao<double, 1> &hy,
             const tensor_hao::TensorHao<double, 1> &hz);
    NiupNidn(const NiupNidn& x);
    NiupNidn(NiupNidn&& x);
    ~NiupNidn();

    NiupNidn & operator  = (const NiupNidn& x);
    NiupNidn & operator  = (NiupNidn&& x);

    size_t getL() const;
    const std::string &getDecompType() const;
    double getDtUSum() const;
    const tensor_hao::TensorHao<double, 1> &getDtU() const;
    const tensor_hao::TensorHao<std::complex<double>, 1> &getGamma() const;
    const tensor_hao::TensorHao<std::complex<double>, 1> &getConstDiag00() const;
    const tensor_hao::TensorHao<std::complex<double>, 1> &getConstDiag10() const;
    const tensor_hao::TensorHao<std::complex<double>, 1> &getConstDiag01() const;
    const tensor_hao::TensorHao<std::complex<double>, 1> &getConstDiag11() const;

    NiupNidnForce readForce(const std::string &filename) const;
    NiupNidnAux sampleAuxFromForce(const NiupNidnForce &force) const;
    double logProbOfAuxFromForce(const NiupNidnAux &aux, const NiupNidnForce &force) const;
    NiupNidnSample getTwoBodySampleFromAux(const NiupNidnAux &aux) const;
    NiupNidnSample getTwoBodySampleFromAuxForce(const NiupNidnAux &aux, const NiupNidnForce &force) const;

    size_t getAuxSize() const;
    size_t getAuxDiffSize(const NiupNidnAux &auxOne, const NiupNidnAux &auxTwo) const;
    double getMemory() const;

 private:
    void copy_deep(const NiupNidn &x);
    void move_deep(NiupNidn &x);

    void setGamma();
    void setConstDiag(double dt,
                      const tensor_hao::TensorHao<double,1> &U,
                      const tensor_hao::TensorHao<double,1> &mu,
                      const tensor_hao::TensorHao<double,1> &hx,
                      const tensor_hao::TensorHao<double,1> &hy,
                      const tensor_hao::TensorHao<double,1> &hz);
    void setTwoBodySampleMatrix(NiupNidnSample &twoBodySample, const NiupNidnAux &aux) const;
};

#endif //AFQMCLAB_NIUPNIDN_H