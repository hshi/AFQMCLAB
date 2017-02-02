//
// Created by boruoshihao on 1/10/17.
//

#ifndef AFQMCLAB_NIUPNIDNSDOPERATION_H
#define AFQMCLAB_NIUPNIDNSDOPERATION_H

#include "../../../walker/SD/include/SD.h"
#include "../../../twoBodyOperator/NiupNidn/include/NiupNidn.h"

void applyTwoBodySampleToRightWalker(const SD &walker, SD &walkerNew, const NiupNidnSample &twoBodySample);
void applyTwoBodySampleToLeftWalker(const SD &walker, SD &walkerNew, const NiupNidnSample &twoBodySample);
void getForce(NiupNidnForce &force, const NiupNidn &twoBody, const SD &walkerLeft, const SD &walkerRight);
void getForce(NiupNidnForce &force, const NiupNidn &twoBody, const std::string &filename);

std::tuple < std::complex<double>, std::complex<double> >
measureTwoBodySecondOrder(const SD &walkerLeft, const SD &walkerRight, const NiupNidn &niupNidn);

#endif //AFQMCLAB_NIUPNIDNSDOPERATION_H