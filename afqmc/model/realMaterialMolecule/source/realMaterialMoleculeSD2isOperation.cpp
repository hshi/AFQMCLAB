//
// Created by boruoshihao on 7/8/17.
//

#include "../include/realMaterialMoleculeSD2isOperation.h"

using namespace std;
using namespace tensor_hao;

void fillWalkerRandomly(SD2is &walker, const RealMaterialMolecule &model)
{
    size_t L = model.getL(); size_t Nup = model.getNup(); size_t Ndn = model.getNdn();
    walker.resize(L, Nup, Ndn);
    walker.randomFill();
}

void fillWalkerFromModel(SD2is &walker, RealMaterialMolecule &model)
{
    size_t L = model.getL(); size_t Nup = model.getNup(); size_t Ndn = model.getNdn();
    walker.resize(L, Nup, Ndn);

    model.setKpEigenValueAndVector();
    const TensorHao<double,2> &KpEigenVector = model.getKpEigenVector();

    size_t Nmax = max(Nup, Ndn);
    TensorHao<complex<double>,2> &wf = walker.wfRef();
    for(size_t i = 0; i < Nmax; ++i)
    {
        for(size_t j = 0; j < L; ++j) wf(j,i) = KpEigenVector(j,i);
    }
}