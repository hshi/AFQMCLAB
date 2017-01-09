//
// Created by boruoshihao on 1/9/17.
//

#ifndef AFQMCLAB_ONSITEDENSITYUPDENSITYDNOPERATESINGLEDETERMINANT_H
#define AFQMCLAB_ONSITEDENSITYUPDENSITYDNOPERATESINGLEDETERMINANT_H

#include "../../walker/include/singleDeterminant.h"
#include "../../twoBodyOperator/onSiteNupNdn/include/onSiteDensityUpDensityDnOperator.h"

std::tuple< std::complex<double>,
    tensor_hao::TensorHao<std::complex<double>,1>,
    tensor_hao::TensorHao<std::complex<double>,1>,
    tensor_hao::TensorHao<std::complex<double>,1>,
    tensor_hao::TensorHao<std::complex<double>,1> >
OnSiteDensityUpDensityDnToOneBody(const OnSiteDensityUpDensityDnOperator &twoBody,
                                  const OnSiteDensityUpDensityDnOperatorAux &field );

void applyTwoBodyToRightWalker(const SingleDeterminant &walker, SingleDeterminant &walkerNew,
                               const OnSiteDensityUpDensityDnOperator &twoBody,
                               const OnSiteDensityUpDensityDnOperatorAux &field);


#endif //AFQMCLAB_ONSITEDENSITYUPDENSITYDNOPERATESINGLEDETERMINANT_H
