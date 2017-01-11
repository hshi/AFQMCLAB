//
// Created by boruoshihao on 1/11/17.
//

#ifndef AFQMCLAB_HUBBARDREALSPACESOC_H
#define AFQMCLAB_HUBBARDREALSPACESOC_H

#include "../../../../common/tensorHao/include/tensor_all.h"

class HubbardRealSpaceSOC
{
 private:
    size_t L, N;
    tensor_hao::TensorHao< std::complex<double>, 2 > K;
    tensor_hao::TensorHao< double, 1> mu, hx, hy, hz;
    tensor_hao::TensorHao< double, 1> U;

 public:
    HubbardRealSpaceSOC();
    HubbardRealSpaceSOC(const std::string &filename);
    ~HubbardRealSpaceSOC();

    size_t getL() const;
    size_t getN() const;
    const tensor_hao::TensorHao<std::complex<double>, 2> &getK() const;
    const tensor_hao::TensorHao<double, 1> &getMu() const;
    const tensor_hao::TensorHao<double, 1> &getHx() const;
    const tensor_hao::TensorHao<double, 1> &getHy() const;
    const tensor_hao::TensorHao<double, 1> &getHz() const;
    const tensor_hao::TensorHao<double, 1> &getU() const;

    void read(const std::string &filename);
    void write(const std::string &filename) const;
    friend void MPIBcast(HubbardRealSpaceSOC &buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
};

#endif //AFQMCLAB_HUBBARDREALSPACESOC_H