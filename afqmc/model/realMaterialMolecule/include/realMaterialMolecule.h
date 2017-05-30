//
// Created by boruoshihao on 5/30/17.
//

#ifndef AFQMCLAB_REALMATERIALMOLECULE_H
#define AFQMCLAB_REALMATERIALMOLECULE_H

#include "../../../../common/common.h"

class RealMaterialMolecule
{
 private:
    size_t L, Nup, Ndn;
    size_t choleskyNumber;
    tensor_hao::TensorHao<double,2> K;
    tensor_hao::TensorHao<double,3> choleskyVecs;
    tensor_hao::TensorHao<double,1> choleskyBg;

 public:
    RealMaterialMolecule();
    RealMaterialMolecule(const std::string &filename);
    ~RealMaterialMolecule();

    void read(const std::string &filename);
    void write(const std::string &filename) const;
};


#endif //AFQMCLAB_REALMATERIALMOLECULE_H
