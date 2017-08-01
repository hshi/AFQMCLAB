//
// Created by boruoshihao on 1/10/17.
//

#ifndef AFQMCLAB_SDSDOPERATION_H
#define AFQMCLAB_SDSDOPERATION_H

#include "../../../walker/SD/include/SD.h"

enum class SDSDOperationState
{
    VOID=0,
    LUOVERLAP,
    THETA_T
};

class SDSDOperation
{
    SDSDOperationState state;
    const SD *walkerLeft, *walkerRight;

    tensor_hao::LUDecomp< std::complex<double> > LUOverlap;
    tensor_hao::TensorHao< std::complex<double>, 2 > theta_T;

    std::complex<double> logOverlap;
    tensor_hao::TensorHao< std::complex<double>, 2 > greenMatrix;
    tensor_hao::TensorHao< std::complex<double>, 1 > greenDiagonal;
    tensor_hao::TensorHao< std::complex<double>, 1 > greenOffDiagonal;
 public:
    SDSDOperation();
    SDSDOperation(const SD &walkerLeft_, const SD &walkerRight_);
    ~SDSDOperation();

    SDSDOperationState getState() const;
    const SD *getWalkerLeft() const;
    const SD *getWalkerRight() const;

    const tensor_hao::LUDecomp<std::complex<double>> &returnLUOverlap();
    const tensor_hao::TensorHao<std::complex<double>, 2> &returnTheta_T();

    void set(const SD &walkerLeft_, const SD &walkerRight_);
    void reSet();
    std::complex<double> returnLogOverlap();
    const tensor_hao::TensorHao< std::complex<double>, 2 > &returnGreenMatrix();
    const tensor_hao::TensorHao< std::complex<double>, 1 > &returnGreenDiagonal();
    const tensor_hao::TensorHao< std::complex<double>, 1 > &returnGreenOffDiagonal();

    double getMemory() const;

 private:
    SDSDOperation(const SDSDOperation& x);
    SDSDOperation & operator  = (const SDSDOperation& x);

    void calculateLUOverlap();
    void calculateTheta_T();
};

void setWalkerFromPhiT(std::vector<SD> &walker, const SD& phiT);

#endif //AFQMCLAB_SDSDOPERATION_H