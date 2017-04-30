//
// Created by boruoshihao on 4/30/17.
//

#ifndef AFQMCLAB_GHF_H
#define AFQMCLAB_GHF_H

#include "afqmclab.h"
#include "ghfMethod.h"

class Ghf
{
 private:
    GhfMethod method;
    HubbardSOC model;

    double variationalEnergy;
    SD variationalState;
    tensor_hao::TensorHao<std::complex<double>, 1> density, spinOrbit;
    tensor_hao::TensorHao<std::complex<double>, 2> H0, meanFieldVectors;
    tensor_hao::TensorHao<double, 1> meanFieldValues;

 public:
    Ghf();
    ~Ghf();

    void run();
    void initialParameters();

 private:
    void setH0();
    void setVariationalStateFromH0();
    void setOrderParameterFromVariationalState();
    void setMeanFieldVectorsValuesFromOrderParameter();
    void setVariationalEnergyFromOrderParameterAndMeanFieldValues();
    void setVariationalStateFromMeanFieldVectors();
};

#endif //AFQMCLAB_GHF_H