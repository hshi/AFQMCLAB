//
// Created by boruoshihao on 12/8/16.
//

#ifndef AFQMCLIB_MEASUREBASEDONLANMATRIX_H
#define AFQMCLIB_MEASUREBASEDONLANMATRIX_H

#include "LanczosInterface.h"

class MeasureBasedOnLanMatrix
{
    //Lan is used to build Lanczos matrix, it should not contain any eigenstates!
    Lanczos lan;
    double wfNorm;
 public:
    MeasureBasedOnLanMatrix(const ModelInterface &modelInterface, LanczosBasisWf &wf);

    tensor_hao::TensorHao<double, 1> returnExpMinusTauModel(const tensor_hao::TensorHao<double,1> &tau, size_t L,
                                                            double accuracy = 1e-10, double litForProjection = 0.01, char wfFlag = 'F');

    tensor_hao::TensorHao<double, 1> returnSpectralFunction(const tensor_hao::TensorHao<double,1> &omega, size_t L,
                                                            double accuracy = 1e-10, double litForProjection = 0.01, char wfFlag = 'F');

    double getWfNorm() const;

    std::tuple<const std::vector<double> &, const std::vector<double> &> getLanElements() const;
 private:
    MeasureBasedOnLanMatrix(const MeasureBasedOnLanMatrix& x);
    MeasureBasedOnLanMatrix & operator  = (const MeasureBasedOnLanMatrix& x);
};

#endif //AFQMCLIB_MEASUREBASEDONLANMATRIX_H