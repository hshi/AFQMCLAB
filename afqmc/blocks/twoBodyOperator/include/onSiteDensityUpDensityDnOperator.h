//
// Created by boruoshihao on 1/8/17.
//

#ifndef AFQMCLAB_ONSITEDENSITYUPDENSITYDNOPERATOR_H
#define AFQMCLAB_ONSITEDENSITYUPDENSITYDNOPERATOR_H

#include "../../../../common/tensorHao/include/tensor_all.h"

typedef tensor_hao::TensorHao<int, 1> OnSiteDensityUpDensityDnOperatorAux;
typedef tensor_hao::TensorHao<std::complex<double>, 1> OnSiteDensityUpDensityDnOperatorForce;

class OnSiteDensityUpDensityDnOperator
{
 private:
    size_t L;
    std::string decompType;  //densityCharge, densitySpin, hopCharge, hopSpin, pairCharge, pairSpin
    double USum;
    tensor_hao::TensorHao<std::complex<double>,1> gamma;
    tensor_hao::TensorHao<std::complex<double>,1> constDiag00, constDiag10, constDiag01, constDiag11;

 public:
    OnSiteDensityUpDensityDnOperator();
    OnSiteDensityUpDensityDnOperator(double dt, const std::string &decompTypeIn,
                                     const tensor_hao::TensorHao<double, 1> &U,
                                     const tensor_hao::TensorHao<double, 1> &mu,
                                     const tensor_hao::TensorHao<double, 1> &hx,
                                     const tensor_hao::TensorHao<double, 1> &hy,
                                     const tensor_hao::TensorHao<double, 1> &hz);
    OnSiteDensityUpDensityDnOperator(const OnSiteDensityUpDensityDnOperator& x);
    OnSiteDensityUpDensityDnOperator(OnSiteDensityUpDensityDnOperator&& x);
    ~OnSiteDensityUpDensityDnOperator();

    OnSiteDensityUpDensityDnOperator & operator  = (const OnSiteDensityUpDensityDnOperator& x);
    OnSiteDensityUpDensityDnOperator & operator  = (OnSiteDensityUpDensityDnOperator&& x);

    size_t getL() const;
    const std::string &getDecompType() const;
    double getUSum() const;
    const tensor_hao::TensorHao<std::complex<double>, 1> &getGamma() const;
    const tensor_hao::TensorHao<std::complex<double>, 1> &getConstDiag00() const;
    const tensor_hao::TensorHao<std::complex<double>, 1> &getConstDiag10() const;
    const tensor_hao::TensorHao<std::complex<double>, 1> &getConstDiag01() const;
    const tensor_hao::TensorHao<std::complex<double>, 1> &getConstDiag11() const;

    OnSiteDensityUpDensityDnOperatorAux sampleAuxFromForce(const OnSiteDensityUpDensityDnOperatorForce &force,
                                                           double gammaForceCap=1e300);
    double logProbOfAuxFromForce(const OnSiteDensityUpDensityDnOperatorAux &field,
                                 const OnSiteDensityUpDensityDnOperatorForce &force,
                                 double gammaForceCap=1e300);

 private:
    void copy_deep(const OnSiteDensityUpDensityDnOperator &x);
    void move_deep(OnSiteDensityUpDensityDnOperator &x);

    void setGamma(double dt, const tensor_hao::TensorHao<double,1> &U);
    void setConstDiag(double dt, const tensor_hao::TensorHao<double,1> &U,
                      const tensor_hao::TensorHao<double,1> &mu,
                      const tensor_hao::TensorHao<double,1> &hx,
                      const tensor_hao::TensorHao<double,1> &hy,
                      const tensor_hao::TensorHao<double,1> &hz);
};

#endif //AFQMCLAB_ONSITEDENSITYUPDENSITYDNOPERATOR_H