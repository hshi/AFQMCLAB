//
// Created by boruoshihao on 4/28/17.
// Formula can be found: http://www.personal.psu.edu/jhm/f90/lectures/lsq2.html
// Sample code: http://www.bragitoff.com/2015/09/c-program-for-polynomial-fit-least-squares/
//

#ifndef AFQMCLAB_POLYNOMIALFIT_H
#define AFQMCLAB_POLYNOMIALFIT_H

#include "../../tensorHao/include/tensor_all.h"

class PolynomialFit
{
    const tensor_hao::TensorHao<double, 1> *x, *y;
    size_t polynomialOrder;
    tensor_hao::TensorHao<double, 1> coefficient;
 public:
    PolynomialFit(const tensor_hao::TensorHao<double, 1> &x_in,
                  const tensor_hao::TensorHao<double, 1> &y_in,
                  std::size_t polynomialOrder_in);

    const tensor_hao::TensorHao<double, 1> &getCoefficient() const;
    const tensor_hao::TensorHao<double, 1> returnFittedY() const;

 private:
    void analysis() const;
    void fitLinearFunction();
    void fitBySolvingLinearEquation();
};

#endif //AFQMCLAB_POLYNOMIALFIT_H