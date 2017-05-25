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

    CholeskyRealAux sampleAuxFromForce(const CholeskyRealForce &force, double cap=1e300) const;
    double logOfAuxFromForce(const CholeskyRealAux &aux, const CholeskyRealForce &force, double cap = 1e300) const;
    double sumOfAuxFromForce(const CholeskyRealForce &force, double cap = 1e300) const;
    CholeskyRealSample getTwoBodySampleFromAux(const CholeskyRealAux &aux) const;



 private:
    void copy_deep(const CholeskyReal &x);
};

#endif //AFQMCLAB_CHOLESKYREAL_H