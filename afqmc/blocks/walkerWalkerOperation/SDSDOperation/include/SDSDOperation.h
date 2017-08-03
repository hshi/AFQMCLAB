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

    std::complex<double> logOverlap; bool logOverlapIsCalculated;
    tensor_hao::TensorHao< std::complex<double>, 2 > greenMatrix; bool greenMatrixIsCalculated;
    tensor_hao::TensorHao< std::complex<double>, 1 > greenDiagonal; bool greenDiagonalIsCalculated;
    tensor_hao::TensorHao< std::complex<double>, 1 > greenOffDiagonal; bool greenOffDiagonalIsCalculated;
 public:
    SDSDOperation();
    SDSDOperation(const SD &walkerLeft_, const SD &walkerRight_);
    ~SDSDOperation();

    SDSDOperationState getState() const;
    const SD *getWalkerLeft() const;
    const SD *getWalkerRight() const;
    
    void set(const SD &walkerLeft_, const SD &walkerRight_);
    void reSet();
    
    const tensor_hao::LUDecomp<std::complex<double>> &returnLUOverlap();
    const tensor_hao::TensorHao<std::complex<double>, 2> &returnTheta_T();
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

void setWalkerFromPhiT(std::vector<SD> &walker, std::vector<bool> &walkerIsAlive, const SD& phiT);

#endif //AFQMCLAB_SDSDOPERATION_H