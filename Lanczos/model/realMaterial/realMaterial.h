//
// Created by boruoshihao on 10/27/16.
//

#ifndef AFQMCLIB_REALMATERIAL_H
#define AFQMCLIB_REALMATERIAL_H

#include "../../interface/include/modelInterface.h"
#include "../../interface/include/LanczosBasisWf.h"
#include "../lanczosBasis/lanczosBasis.h"

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
    std::vector<TwoBody> upUp,upDn,dnUp,dnDn;

    size_t NHilbert, NHilbertUp, NHilbertDn;
    tensor_hao::TensorHao< TableElement, 3 > tableUp, tableDn;
 public:
    RealMaterial();
    RealMaterial(size_t L, size_t Nup, size_t Ndn);
    RealMaterial(const std::string &filename);

    size_t getL() const;
    size_t getNup() const;
    size_t getNdn() const;
    const std::vector<OneBody> &getUp() const;
    const std::vector<OneBody> &getDn() const;
    const std::vector<TwoBody> &getUpup() const;
    const std::vector<TwoBody> &getUpdn() const;
    const std::vector<TwoBody> &getDnup() const;
    const std::vector<TwoBody> &getDndn() const;
    virtual size_t getWfSize() const;
    size_t getNHilbertUp() const;
    size_t getNHilbertDn() const;

    void setUp(const std::vector<OneBody> &up);
    void setDn(const std::vector<OneBody> &dn);
    void setUpup(const std::vector<TwoBody> &upup);
    void setUpdn(const std::vector<TwoBody> &updn);
    void setDnup(const std::vector<TwoBody> &dnup);
    void setDndn(const std::vector<TwoBody> &dndn);

    void read(const std::string &filename);
    void write(const std::string &filename);

    virtual void applyHToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const;

 private:
    void setFromLNupNdn();
    void setNHilbertUpAndTableUp(LanczosBasis &lanBasisUp);
    void setNHilbertDnAndTableDn(LanczosBasis &lanBasisDn);
    void printMemoryInfo();

    RealMaterial(const RealMaterial& x);
    RealMaterial & operator  = (const RealMaterial& x);
};

#endif //AFQMCLIB_REALMATERIAL_H