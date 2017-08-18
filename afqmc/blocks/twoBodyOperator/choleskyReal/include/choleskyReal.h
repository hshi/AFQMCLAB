//
// Created by boruoshihao on 5/23/17.
//

#ifndef AFQMCLAB_CHOLESKYREAL_H
#define AFQMCLAB_CHOLESKYREAL_H

#include "choleskyRealAux.h"
#include "choleskyRealForce.h"
#include "choleskyRealSample.h"

class CholeskyReal
{
 private:
    double dt;
    std::complex<double> sqrtMinusDt;
    size_t choleskyNumber;
    tensor_hao::TensorHao<std::complex<double>, 3> sqrtMinusDtCholeskyVecs;
    const tensor_hao::TensorHao<double, 1> *choleskyBg;

 public:
    CholeskyReal();
    CholeskyReal(double dt,
                 const tensor_hao::TensorHao<double, 3> &choleskyVecs,
                 const tensor_hao::TensorHao<double, 1> &choleskyBg );
    CholeskyReal(const CholeskyReal& x);
    CholeskyReal(CholeskyReal&& x);
    ~CholeskyReal();

    CholeskyReal & operator  = (const CholeskyReal& x);
    CholeskyReal & operator  = (CholeskyReal&& x);

    double getDt() const;
    const tensor_hao::TensorHao<std::complex<double>, 3> &getSqrtMinusDtCholeskyVecs() const;
    const tensor_hao::TensorHao<double, 1> *getCholeskyBg() const;
    size_t getCholeskyNumber() const;
    const std::complex<double> &getSqrtMinusDt() const;
    size_t returnBasisSize() const;

    CholeskyRealForce readForce(const std::string &filename) const;
    CholeskyRealAux sampleAuxFromForce(const CholeskyRealForce &force) const;
    std::complex<double> logProbOfAuxFromForce(const CholeskyRealAux &aux, const CholeskyRealForce &force) const;
    CholeskyRealSample getTwoBodySampleFromAux(const CholeskyRealAux &aux) const;
    CholeskyRealSample getTwoBodySampleFromAuxForce(const CholeskyRealAux &aux, const CholeskyRealForce &force) const;

    double getMemory() const;
 private:
    void copy_deep(const CholeskyReal &x);
    void move_deep(CholeskyReal &x);
    void initialSqrtMinusDtCholeskyVecs(const tensor_hao::TensorHao<double, 3> &choleskyVecs);
    void setTwoBodySampleMatrix(CholeskyRealSample &choleskyRealSample, const CholeskyRealAux &aux) const;
};

#endif //AFQMCLAB_CHOLESKYREAL_H