//
// Created by boruoshihao on 10/25/16.
//

#ifndef AFQMCLIB_FULLMATRIX_H
#define AFQMCLIB_FULLMATRIX_H

#include "../../interface/include/modelInterface.h"
#include "../../interface/include/LanczosBasisWf.h"

class FullMatrix : public ModelInterface
{
    tensor_hao::TensorHao<std::complex<double>, 2> Hm;
 public:
    FullMatrix();
    FullMatrix(const tensor_hao::TensorHao<std::complex<double>, 2> &HmIn);
    FullMatrix(tensor_hao::TensorHao<std::complex<double>, 2> &&HmIn);

    const tensor_hao::TensorHao<std::complex<double>, 2> &getHm() const;
    void read(const std::string &filename);
    void write(const std::string &filename) const;

    virtual size_t getWfSize() const;
    virtual void applyHToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const;

 private:
    FullMatrix(const FullMatrix& x);
    FullMatrix & operator  = (const FullMatrix& x);
};

#endif //AFQMCLIB_FULLMATRIX_H