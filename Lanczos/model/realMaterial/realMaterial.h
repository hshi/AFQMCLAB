//
// Created by boruoshihao on 10/27/16.
//

#ifndef AFQMCLIB_REALMATERIAL_H
#define AFQMCLIB_REALMATERIAL_H

#include "../../interface/include/modelInterface.h"
#include "../../interface/include/LanczosBasisWf.h"
#include "../lanczosBasis/lanczosBasis.h"

//TODO:: Ask Mario for a realistic materials for exact soultion? To write a test code.
//TODO:: Test warning in Hurricane?
//TODO:: How to use my library?
//TODO:: Check which openmp is faster? Static or dynamic
//TODO:: Check " collapse(2) " faster or not?

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
    std::vector<TwoBody> upUp,upDn,dnDn;

    size_t NHilbert, NHilbertUp, NHilbertDn;
    tensor_hao::TensorHao< TableElement, 3 > tableUp, tableDn;
 public:
    RealMaterial(size_t L, size_t Nup, size_t Ndn);
    RealMaterial(const std::string &filename);

    size_t getL() const;
    size_t getNup() const;
    size_t getNdn() const;
    const std::vector<OneBody> &getUp() const;
    const std::vector<OneBody> &getDn() const;
    const std::vector<TwoBody> &getUpUp() const;
    const std::vector<TwoBody> &getUpDn() const;
    const std::vector<TwoBody> &getDnDn() const;
    virtual size_t getWfSize() const;
    size_t getNHilbertUp() const;
    size_t getNHilbertDn() const;

    void setUp(const std::vector<OneBody> &up);
    void setDn(const std::vector<OneBody> &dn);
    void setUpUp(const std::vector<TwoBody> &upUp);
    void setUpDn(const std::vector<TwoBody> &upDn);
    void setDnDn(const std::vector<TwoBody> &dnDn);

    void read(const std::string &filename);
    void write(const std::string &filename);

    virtual void applyHToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const;
    void applyKToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const;
    void applyVToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const;
    void applySiSjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const;
    void applySziSzjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const;
    void applySplusiSminusjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const;
    void applyNiNjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const;
    void applyDiDaggerDjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const;
    void applyCiupDaggerCjupToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const;
    void applyCidnDaggerCjdnToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const;
    void applyOperatorsToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew,
                            const std::vector<OneBody> &up, const std::vector<OneBody> &dn,
                            const std::vector<TwoBody> &upUp, const std::vector<TwoBody> &upDn,
                            const std::vector<TwoBody> &dnDn ) const;

 private:
    void setFromLNupNdn();
    void setNHilbertUpAndTableUp(LanczosBasis &lanBasisUp);
    void setNHilbertDnAndTableDn(LanczosBasis &lanBasisDn);
    void printMemoryInfo();

    RealMaterial(const RealMaterial& x);
    RealMaterial & operator  = (const RealMaterial& x);
};

#endif //AFQMCLIB_REALMATERIAL_H