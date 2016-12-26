//
// Created by boruoshihao on 12/25/16.
//

#ifndef AFQMCLAB_SINGLEDETERMINANT_H
#define AFQMCLAB_SINGLEDETERMINANT_H

#include "../../../../common/tensorHao/include/tensor_all.h"

class SingleDeterminant
{
 private:
    std::complex<double> logw;
    tensor_hao::TensorHao<std::complex<double>,2> wf;

 public:
    SingleDeterminant();
    SingleDeterminant(size_t L, size_t N);
    SingleDeterminant(const SingleDeterminant& x);
    SingleDeterminant(SingleDeterminant&& x);
    ~SingleDeterminant();

    SingleDeterminant & operator  = (const SingleDeterminant& x);
    SingleDeterminant & operator  = (SingleDeterminant&& x);

    const std::complex<double> &getLogw() const;
    const tensor_hao::TensorHao<std::complex<double>, 2> &getWf() const;
    std::complex<double> &logwRef();
    tensor_hao::TensorHao<std::complex<double>, 2> &wfRef();
    size_t getL() const;
    size_t getN() const;

    void stabilize();
    std::complex<double> normalize();
    void randomFill();

//    void read(const std::string& filename, int flag=0);  // flag: 0, read each thread;  1, read main thread and bcast
//    void write(const std::string& filename,int flag=0) const; // flag: 0, write each thread; 1, write main thread.


 private:
    void copy_deep(const SingleDeterminant &x);
    void move_deep(SingleDeterminant &x);
};

#endif //AFQMCLAB_SINGLEDETERMINANT_H
