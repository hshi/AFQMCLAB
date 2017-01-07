//
// Created by boruoshihao on 12/8/16.
//

#ifndef AFQMCLAB_MEASUREBASEDONLANMATRIX_H
#define AFQMCLAB_MEASUREBASEDONLANMATRIX_H

#include "LanczosInterface.h"

class MeasureBasedOnLanMatrix
{
    //Lan is used to build Lanczos matrix, it should not contain any eigenstates!
    Lanczos lan;
    double wfNorm;
 public:
    MeasureBasedOnLanMatrix(const ModelInterface &modelInterface, std::string prefixName="measureLanMatrix");
    MeasureBasedOnLanMatrix(const ModelInterface &modelInterface, LanczosBasisWf &wf);

    tensor_hao::TensorHao<double, 1> returnLogExpMinusTauModel(const tensor_hao::TensorHao<double, 1> &tau, size_t L,
                                                               double accuracy = 1e-10, double litForProjection = 0.01, char wfFlag = 'F');

    tensor_hao::TensorHao<std::complex<double>, 1> returnGreenFunction(const tensor_hao::TensorHao<std::complex<double>, 1> &omega, size_t L,
                                                                       double accuracy = 1e-10, double litForProjection = 0.01, char wfFlag = 'F');

    double getWfNorm() const;

    std::tuple<const std::vector<double> &, const std::vector<double> &> getLanElements() const;
    void read(std::string prefixName="measureLanMatrix");
    void write(std::string prefixName="measureLanMatrix") const;
 private:
    MeasureBasedOnLanMatrix(const MeasureBasedOnLanMatrix& x);
    MeasureBasedOnLanMatrix & operator  = (const MeasureBasedOnLanMatrix& x);
};

#endif //AFQMCLAB_MEASUREBASEDONLANMATRIX_H