//
// Created by boruoshihao on 5/30/17.
//

#ifndef AFQMCLAB_REALMATERIALMOLECULE_H
#define AFQMCLAB_REALMATERIALMOLECULE_H

#include "../../../../common/common.h"
#include "../../../blocks/oneBodyOperator/hop2is/include/hop2is.h"
#include "../../../blocks/oneBodyOperator/logHop2is/include/logHop2is.h"
#include "../../../blocks/twoBodyOperator/choleskyReal/include/choleskyReal.h"

//Details about t, K, Kp are in my note.
//t is the non-interacting matrix.
//K is t - choleskyVecs*choleskyVecs.
//Kp is K + choleskyBg*choleskyVecs.

#ifdef MPI_HAO
class RealMaterialMolecule;
void MPIBcast(RealMaterialMolecule &buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
#endif

class RealMaterialMolecule
{
 private:
    size_t L, Nup, Ndn;
    size_t choleskyNumber;
    tensor_hao::TensorHao<double,2> t, K;
    tensor_hao::TensorHao<double,3> choleskyVecs;
    tensor_hao::TensorHao<double,1> choleskyBg;

    size_t KpEigenStatus; //0: void, 1: calculated Kp, 2: calculated Kp Eigens.
    tensor_hao::TensorHao<double,2> Kp;
    tensor_hao::TensorHao<double,1> KpEigenValue;
    tensor_hao::TensorHao<double,2> KpEigenVector;

 public:
    RealMaterialMolecule();
    RealMaterialMolecule(const std::string &filename);
    ~RealMaterialMolecule();

    size_t getL() const;
    size_t getNup() const;
    size_t getNdn() const;
    size_t getCholeskyNumber() const;
    const tensor_hao::TensorHao<double,2> &getT() const;
    const tensor_hao::TensorHao<double,2> &getK() const;
    const tensor_hao::TensorHao<double,3> &getCholeskyVecs() const;
    const tensor_hao::TensorHao<double,1> &getCholeskyBg() const;
    size_t getKpEigenStatus() const;
    const tensor_hao::TensorHao<double,2> &getKp() const;
    const tensor_hao::TensorHao<double,1> &getKpEigenValue() const;
    const tensor_hao::TensorHao<double,2> &getKpEigenVector() const;

    void read(const std::string &filename);
    void write(const std::string &filename) const;
#ifdef MPI_HAO
    friend void MPIBcast(RealMaterialMolecule &buffer, int root,  const MPI_Comm& comm);
#endif

    void writeBackGround(const std::string &filename) const;
    void updateBackGround(const tensor_hao::TensorHao<double,1> &background);
    void updateBackGround(tensor_hao::TensorHao<double,1> &&background);

    Hop2is returnExpMinusAlphaK(double alpha);
    LogHop2is returnLogExpMinusAlphaK(double alpha);
    CholeskyReal returnExpMinusAlphaV(double alpha);

    void setKp();
    void setKpEigenValueAndVector();

    double getMemory() const;

 private:
    RealMaterialMolecule(const RealMaterialMolecule& x);
    RealMaterialMolecule & operator  = (const RealMaterialMolecule& x);
};

#endif //AFQMCLAB_REALMATERIALMOLECULE_H