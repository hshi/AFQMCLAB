//
// Created by boruoshihao on 6/5/17.
//

#ifndef AFQMCLAB_REALMATERIALMOLECULEFIXEDSD2SSD2IS_H
#define AFQMCLAB_REALMATERIALMOLECULEFIXEDSD2SSD2IS_H

#include "realMaterialMolecule.h"
#include "../../../blocks/walkerWalkerOperation/SD2sSD2isOperation/include/SD2sSD2isOperation.h"

class RealMaterialMoleculeFixedSD2sSD2is
{
 private:
    const RealMaterialMolecule *realMaterialMolecule;
    const SD2s  *walkerLeft;

    std::complex<double> den;
    std::complex<double> TNum;
    tensor_hao::TensorHao<std::complex<double>, 1> choleskyBgNum;
    tensor_hao::TensorHao<std::complex<double>, 1> choleskyExNum;
    std::complex<double> HNum;

    tensor_hao::TensorHao<std::complex<double>,2> wfUpDaggerT, wfDnDaggerT;
    tensor_hao::TensorHao<std::complex<double>,3> wfUpDaggerCholeskyVecs, wfDnDaggerCholeskyVecs;
 public:
    RealMaterialMoleculeFixedSD2sSD2is();
    RealMaterialMoleculeFixedSD2sSD2is(const RealMaterialMolecule& realMaterialMolecule_, const SD2s &walkerLeft_);
    ~RealMaterialMoleculeFixedSD2sSD2is();

    void initModelWalkerNullptr();
    void setModelWalker(const RealMaterialMolecule& realMaterialMolecule_, const SD2s &walkerLeft_);
    void reSet();
    std::complex<double> returnEnergy();
    tensor_hao::TensorHao<double, 1> returnCholeskyBg();
    void addMeasurement(SD2sSD2isOperation &sd2sSD2isOperation, std::complex<double> denIncrement);

    void write() const;
    double getMemory() const;
 private:
    RealMaterialMoleculeFixedSD2sSD2is(const RealMaterialMoleculeFixedSD2sSD2is& x);
    RealMaterialMoleculeFixedSD2sSD2is & operator  = (const RealMaterialMoleculeFixedSD2sSD2is& x);

    void initWfDaggerT();
    void initWfDaggerCholeskyVecs();
    void checkWalkerLeft(const SD2sSD2isOperation &sd2sSD2isOperation);
    void addEnergy(const tensor_hao::TensorHao<std::complex<double>, 2> &thetaUp_T,
                   const tensor_hao::TensorHao<std::complex<double>, 2> &thetaDn_T,
                   std::complex<double> denIncrement);
    std::complex<double> calculateTenergy(const tensor_hao::TensorHao<std::complex<double>, 2> &thetaUp_T,
                                          const tensor_hao::TensorHao<std::complex<double>, 2> &thetaDn_T);
    tensor_hao::TensorHao<std::complex<double>, 1> calculateCholeskyBg(const tensor_hao::TensorHao<std::complex<double>, 2> &thetaUp_T,
                                                                       const tensor_hao::TensorHao<std::complex<double>, 2> &thetaDn_T);
    tensor_hao::TensorHao<std::complex<double>, 1> calculateCholeskyEx(const tensor_hao::TensorHao<std::complex<double>, 2> &thetaUp_T,
                                                                       const tensor_hao::TensorHao<std::complex<double>, 2> &thetaDn_T);
};

#endif //AFQMCLAB_REALMATERIALMOLECULEFIXEDSD2SSD2IS_H