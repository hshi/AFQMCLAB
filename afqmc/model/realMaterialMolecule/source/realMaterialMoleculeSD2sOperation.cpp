//
// Created by boruoshihao on 7/8/17.
//

#include "../include/realMaterialMoleculeSD2sOperation.h"

using namespace std;
using namespace tensor_hao;

void fillWalkerRandomly(SD2s &walker, const RealMaterialMolecule &model)
{
    size_t L = model.getL(); size_t Nup = model.getNup(); size_t Ndn = model.getNdn();
    walker.resize(L, Nup, Ndn);
    walker.randomFill();
}

void fillWalkerFromModel(SD2s &walker, RealMaterialMolecule &model)
{
    size_t L = model.getL(); size_t Nup = model.getNup(); size_t Ndn = model.getNdn();
    walker.resize(L, Nup, Ndn);

    model.setKpEigenValueAndVector();
    const TensorHao<double,2> &KpEigenVector = model.getKpEigenVector();

    TensorHao<complex<double>,2> &wfUp = walker.wfUpRef();
    for(size_t i = 0; i < Nup; ++i)
    {
        for(size_t j = 0; j < L; ++j) wfUp(j,i) = KpEigenVector(j,i);
    }

    TensorHao<complex<double>,2> &wfDn = walker.wfDnRef();
    for(size_t i = 0; i < Ndn; ++i)
    {
        for(size_t j = 0; j < L; ++j) wfDn(j,i) = KpEigenVector(j,i);
    }
}