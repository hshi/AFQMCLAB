//
// Created by boruoshihao on 10/25/16.
//

#ifndef AFQMCLAB_FULLMATRIX_H
#define AFQMCLAB_FULLMATRIX_H

#include "../../../interface/include/modelInterface.h"
#include "../../../interface/include/LanczosBasisWf.h"

class FullMatrix : public ModelInterface
{
    tensor_hao::TensorHao<std::complex<double>, 2> Hm;
 public:
    FullMatrix(const tensor_hao::TensorHao<std::complex<double>, 2> &HmIn);
    FullMatrix(tensor_hao::TensorHao<std::complex<double>, 2> &&HmIn);
    FullMatrix(const std::string &filename);

    const tensor_hao::TensorHao<std::complex<double>, 2> &getHm() const;
    void read(const std::string &filename);
    void write(const std::string &filename) const;

    virtual size_t getWfSize() const;
    virtual void applyHToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const;

 private:
    FullMatrix(const FullMatrix& x);
    FullMatrix & operator  = (const FullMatrix& x);
};

#endif //AFQMCLAB_FULLMATRIX_H