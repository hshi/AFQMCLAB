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
    const tensor_hao::TensorHao<double, 3> *choleskyVecs;
    const tensor_hao::TensorHao<double, 1> *choleskyBg;

    size_t choleskyNumber;
    std::complex<double> sqrtMinusDt;

 public:
    CholeskyReal();
    CholeskyReal(double dt,
                 const tensor_hao::TensorHao<double, 3> &choleskyVecs,
                 const tensor_hao::TensorHao<double, 1> &choleskyBg );
    CholeskyReal(const CholeskyReal& x);
    ~CholeskyReal();

    CholeskyReal & operator  = (const CholeskyReal& x);

    double getDt() const;
    const tensor_hao::TensorHao<double, 3> *getCholeskyVecs() const;
    const tensor_hao::TensorHao<double, 1> *getCholeskyBg() const;
    size_t getCholeskyNumber() const;
    const std::complex<double> &getSqrtMinusDt() const;
    size_t returnBasisSize() const;

    CholeskyRealAux sampleAuxFromForce(const CholeskyRealForce &force) const;
    double logProbOfAuxFromForce(const CholeskyRealAux &aux, const CholeskyRealForce &force) const;
    CholeskyRealSample getTwoBodySampleFromAux(const CholeskyRealAux &aux) const;
    CholeskyRealSample getTwoBodySampleFromAuxForce(const CholeskyRealAux &aux, const CholeskyRealForce &force) const;

    double getMemory() const;
 private:
    void copy_deep(const CholeskyReal &x);
    void setTwoBodySampleMatrix(CholeskyRealSample &choleskyRealSample, const CholeskyRealAux &aux) const;
};

#endif //AFQMCLAB_CHOLESKYREAL_H