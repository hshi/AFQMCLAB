//
// Created by boruoshihao on 10/26/16.
//
#ifndef AFQMCLAB_SPARSEMATRIX_H
#define AFQMCLAB_SPARSEMATRIX_H

#include "../../../interface/include/modelInterface.h"
#include "../../../interface/include/LanczosBasisWf.h"

//Use Compressed Row Storage (CRS) for sparse matrix, see reference below.
//http://netlib.org/linalg/html_templates/node91.html
//http://www.netlib.org/utk/people/JackDongarra/etemplates/node382.html

class SparseMatrix : public ModelInterface
{
    tensor_hao::TensorHao<std::complex<double>, 1> values;
    tensor_hao::TensorHao<size_t, 1> columnIndex, rowPointer;
 public:
    SparseMatrix(const tensor_hao::TensorHao<std::complex<double>, 1> &values,
                 const tensor_hao::TensorHao<size_t, 1> &columnIndex,
                 const tensor_hao::TensorHao<size_t, 1> &rowPointer);
    SparseMatrix(tensor_hao::TensorHao<std::complex<double>, 1> &&values,
                 tensor_hao::TensorHao<size_t, 1> &&columnIndex,
                 tensor_hao::TensorHao<size_t, 1> &&rowPointer);
    SparseMatrix(const std::string & filename);

    const tensor_hao::TensorHao<std::complex<double>, 1> &getValues() const;
    const tensor_hao::TensorHao<size_t, 1> &getColumnIndex() const;
    const tensor_hao::TensorHao<size_t, 1> &getRowPointer() const;

    void read(const std::string &filename);
    void write(const std::string &filename) const;
    void check() const;

    virtual size_t getWfSize() const;
    virtual void applyHToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const;

 private:
    SparseMatrix(const SparseMatrix& x);
    SparseMatrix & operator  = (const SparseMatrix& x);
};

#endif //AFQMCLAB_SPARSEMATRIX_H