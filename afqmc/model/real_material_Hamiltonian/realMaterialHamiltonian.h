//
// Created by boruoshihao on 9/22/16.
//

#ifndef AFQMCLAB_REAL_MATERIAL_HAMILTONIAN_H
#define AFQMCLAB_REAL_MATERIAL_HAMILTONIAN_H

#include <string>
#include "../../../common/tensorHao/include/tensor_all.h"

//The Hamiltionian is:
//H0 = Sum_{i, j, \sigma} K_{i, j, \sigma} C_{i\sigma}^{\dagger} C_{j\sigma}
//H1 = 0.5 * Sum_{\gamma } D_{\gamma} ( P^{\dagger} P + P P^{\dagger} )
//P_{\gamma} = Sum_{i, j, \sigma} p_{i, j, \sigma \gamma} C_{i\sigma}^{\dagger} C_{j\sigma}
class RealMaterialHamiltonian
{
    size_t basisSize, interactionSize;
    tensor_hao::TensorHao< std::complex<double>, 3 > KTensor;
    tensor_hao::TensorHao< std::complex<double>, 4 > PTensor;
    tensor_hao::TensorHao< std::complex<double>, 1 > DEigen;

 public:
    RealMaterialHamiltonian();
    RealMaterialHamiltonian(const std::string &filename);
    RealMaterialHamiltonian(const RealMaterialHamiltonian &x);
    RealMaterialHamiltonian(RealMaterialHamiltonian &&x);

    RealMaterialHamiltonian& operator=(const RealMaterialHamiltonian& x);
    RealMaterialHamiltonian& operator=(RealMaterialHamiltonian&& x);

    size_t getBasisSize() const;
    size_t getInteractionSize() const;
    const tensor_hao::TensorHao<std::complex<double>, 3> &getKTensor() const;
    const tensor_hao::TensorHao<std::complex<double>, 4> &getPTensor() const;
    const tensor_hao::TensorHao<std::complex<double>, 1> &getDEigen() const;

 private:
    void readBasisSizeAndInteractionSize(std::ifstream &file);
    void allocateKTensorandPTensorDEigen();
    void readKTensorPTensorDEigen(std::ifstream &file);
    void copyDeep(const RealMaterialHamiltonian &x);
    void moveDeep(RealMaterialHamiltonian &x);
};

#endif //AFQMCLAB_REAL_MATERIAL_HAMILTONIAN_LANCZOS_H