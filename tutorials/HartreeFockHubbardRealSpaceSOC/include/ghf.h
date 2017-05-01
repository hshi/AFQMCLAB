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
    tensor_hao::TensorHao<std::complex<double>, 2> H0;

    double variationalEnergy;
    SD variationalState;
    tensor_hao::TensorHao<std::complex<double>, 1> density, spinOrbit, densityBefore, spinOrbitBefore;
    tensor_hao::TensorHao<std::complex<double>, 2> meanFieldVectors;
    tensor_hao::TensorHao<double, 1> meanFieldValues;

    double convergeValue;
    double minimumEnergy;
    SD minimumState;

 public:
    Ghf();
    ~Ghf();

    void run();
    void initialParameters();
    void selfConsistentLoop();
    void oneSelfConsistentStep();
    void prepareStop();

 private:
    void setH0();
    void initialHartreeFockEssential();
    void setMeanFieldVectorsValuesFromOrderParameter();
    void setVariationalStateFromMeanFieldVectors();
    void backupAndUpdateOrderParameterFromVariationalState();
    void setVariationalEnergyFromOrderParameterAndMeanFieldValues();
    void relaxOrderParameter();
    void annealOrderParameter(double anneal);
};
#endif //AFQMCLAB_GHF_H