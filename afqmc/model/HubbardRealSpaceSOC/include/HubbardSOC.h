//
// Created by boruoshihao on 1/11/17.
//

#ifndef AFQMCLAB_HUBBARDREALSPACESOC_H
#define AFQMCLAB_HUBBARDREALSPACESOC_H

#include "../../../../common/tensorHao/include/tensor_all.h"
#include "../../../blocks/oneBodyOperator/hop/include/Hop.h"
#include "../../../blocks/twoBodyOperator/NiupNidn/include/NiupNidn.h"

class HubbardSOC
{
 private:
    size_t L, N;
    tensor_hao::TensorHao< std::complex<double>, 2 > K;
    tensor_hao::TensorHao< double, 1> mu, hx, hy, hz;
    tensor_hao::TensorHao< double, 1> U;

    bool KEigenStatus;
    tensor_hao::TensorHao< double, 1 > KEigenValue;
    tensor_hao::TensorHao< std::complex<double>, 2 > KEigenVector;

 public:
    HubbardSOC();
    HubbardSOC(const std::string &filename);
    ~HubbardSOC();

    size_t getL() const;
    size_t getN() const;
    const tensor_hao::TensorHao<std::complex<double>, 2> &getK() const;
    const tensor_hao::TensorHao<double, 1> &getMu() const;
    const tensor_hao::TensorHao<double, 1> &getHx() const;
    const tensor_hao::TensorHao<double, 1> &getHy() const;
    const tensor_hao::TensorHao<double, 1> &getHz() const;
    const tensor_hao::TensorHao<double, 1> &getU() const;
    bool getKEigenStatus() const;
    const tensor_hao::TensorHao<double, 1> &getKEigenValue() const;
    const tensor_hao::TensorHao<std::complex<double>, 2> &getKEigenVector() const;

    void read(const std::string &filename);
    void write(const std::string &filename) const;
    friend void MPIBcast(HubbardSOC &buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);

    Hop returnExpMinusAlphaK(double alpha);
    NiupNidn returnExpMinusAlphaV(double alpha, const std::string &decompType);

 private:
    HubbardSOC(const HubbardSOC& x);
    HubbardSOC & operator  = (const HubbardSOC& x);

    void setKEigenValueAndVector();
};

#endif //AFQMCLAB_HUBBARDREALSPACESOC_H