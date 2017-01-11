//
// Created by boruoshihao on 1/10/17.
//

#ifndef AFQMCLAB_SDOPERATION_H
#define AFQMCLAB_SDOPERATION_H

#include "../../../walker/SD/include/SD.h"

enum class SDOperationState
{
    VOID=0,
    LUOVERLAP,
    WFLEFTDAGGER
};

class SDOperation
{
    SDOperationState state;
    const SD *walkerLeft, *walkerRight;

    tensor_hao::LUDecomp< std::complex<double> > LUOverlap;
    tensor_hao::TensorHao< std::complex<double>, 2 > wfLeftDagger;
 public:
    SDOperation();
    SDOperation(const SD &walkerLeft_, const SD &walkerRight_);
    ~SDOperation();

    SDOperationState getState() const;
    const SD *getWalkerLeft() const;
    const SD *getWalkerRight() const;

    const tensor_hao::LUDecomp<std::complex<double>> &returnLUOverlap();
    const tensor_hao::TensorHao<std::complex<double>, 2> &returnWfLeftDagger();

    void reSet();
    std::complex<double> returnLogOverlap();
    tensor_hao::TensorHao< std::complex<double>, 2 > returnGreenMatrix();
    tensor_hao::TensorHao< std::complex<double>, 1 > returnGreenDiagonal();
    tensor_hao::TensorHao< std::complex<double>, 1 > returnGreenOffDiagonal();

 private:
    SDOperation(const SDOperation& x);
    SDOperation & operator  = (const SDOperation& x);

    void calculateLUOverlap();
    void calculateWfLeftDagger();
};

#endif //AFQMCLAB_SDOPERATION_H