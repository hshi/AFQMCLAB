//
// Created by boruoshihao on 10/27/16.
//

#ifndef AFQMCLIB_REALMATERIAL_H
#define AFQMCLIB_REALMATERIAL_H

#include "../../interface/include/modelInterface.h"
#include "../../interface/include/LanczosBasisWf.h"

struct OneBody
{
    size_t i;
    size_t j;
    std::complex<double> K;
};

struct TwoBody
{
    size_t i;
    size_t j;
    size_t k;
    size_t l;
    std::complex<double> V;
};

class RealMaterial : public ModelInterface
{
    size_t L, Nup, Ndn;
    std::vector<OneBody> up, dn;
    std::vector<TwoBody> upup,updn,dnup,dndn;
    tensor_hao::TensorHao< size_t, 2 > table;
 public:
    RealMaterial();
    RealMaterial(size_t L, size_t Nup, size_t Ndn);

    size_t getL() const;
    size_t getNup() const;
    size_t getNdn() const;
    const std::vector<OneBody> &getUp() const;
    const std::vector<OneBody> &getDn() const;
    const std::vector<TwoBody> &getUpup() const;
    const std::vector<TwoBody> &getUpdn() const;
    const std::vector<TwoBody> &getDnup() const;
    const std::vector<TwoBody> &getDndn() const;

    void setL(size_t L);
    void setNup(size_t Nup);
    void setNdn(size_t Ndn);
    void setUp(const std::vector<OneBody> &up);
    void setDn(const std::vector<OneBody> &dn);
    void setUpup(const std::vector<TwoBody> &upup);
    void setUpdn(const std::vector<TwoBody> &updn);
    void setDnup(const std::vector<TwoBody> &dnup);
    void setDndn(const std::vector<TwoBody> &dndn);

    void read(const std::string &filename);
    void write(const std::string &filename);
};

#endif //AFQMCLIB_REALMATERIAL_H