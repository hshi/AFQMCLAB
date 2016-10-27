//
// Created by boruoshihao on 10/26/16.
//

#ifndef AFQMCLIB_SPARSEMATRIX_H
#define AFQMCLIB_SPARSEMATRIX_H

#include "../../interface/include/modelInterface.h"
#include "../../interface/include/LanczosBasisWf.h"

struct SparseElement
{
    size_t i;
    size_t j;
    std::complex<double> h;
};

class SparseMatrix : public ModelInterface
{
    size_t matrixRank;
    std::vector<SparseElement> Hm;
 public:
    //TODO: ADD READ CONSTRUCTION
    SparseMatrix();
    SparseMatrix(size_t  L, const std::vector<SparseElement> &HmIn);
    SparseMatrix(size_t  L, std::vector<SparseElement> &&HmIn);

    const std::vector<SparseElement> &getHm() const;
    void read(const std::string &filename);
    void write(const std::string &filename) const;

    virtual size_t getWfSize() const;
    virtual void applyHToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const;

 private:
    SparseMatrix(const SparseMatrix& x);
    SparseMatrix & operator  = (const SparseMatrix& x);
};

#endif //AFQMCLIB_SPARSEMATRIX_H