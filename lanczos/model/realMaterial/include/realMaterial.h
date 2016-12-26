//
// Created by boruoshihao on 10/27/16.
//

#ifndef AFQMCLAB_REALMATERIAL_H
#define AFQMCLAB_REALMATERIAL_H

#include "../../../interface/include/modelInterface.h"
#include "../../../interface/include/LanczosBasisWf.h"
#include "../../lanczosBasis/include/lanczosBasis.h"

class RealMaterial : public ModelInterface
{
    size_t L, Nup, Ndn;
    std::vector<LanOneBody> up, dn;
    std::vector<LanTwoBody> upUp,upDn,dnDn;

    size_t NHilbert, NHilbertUp, NHilbertDn;
    tensor_hao::TensorHao< TableElement, 3 > tableUp, tableDn;
 public:
    RealMaterial(size_t L, size_t Nup, size_t Ndn);
    RealMaterial(const std::string &filename);
    RealMaterial(const RealMaterial& x);
    RealMaterial(RealMaterial &&x);
    RealMaterial & operator  = (const RealMaterial& x);
    RealMaterial & operator  = (RealMaterial &&x);

    RealMaterial generateNewModel(size_t L, size_t Nup, size_t Ndn);

    size_t getL() const;
    size_t getNup() const;
    size_t getNdn() const;
    const std::vector<LanOneBody> &getUp() const;
    const std::vector<LanOneBody> &getDn() const;
    const std::vector<LanTwoBody> &getUpUp() const;
    const std::vector<LanTwoBody> &getUpDn() const;
    const std::vector<LanTwoBody> &getDnDn() const;
    virtual size_t getWfSize() const;
    size_t getNHilbertUp() const;
    size_t getNHilbertDn() const;

    void setUp(const std::vector<LanOneBody> &up);
    void setDn(const std::vector<LanOneBody> &dn);
    void setUpUp(const std::vector<LanTwoBody> &upUp);
    void setUpDn(const std::vector<LanTwoBody> &upDn);
    void setDnDn(const std::vector<LanTwoBody> &dnDn);

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
    void applyCupiDaggerCupjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const;
    void applyCdniDaggerCdnjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const;
    void applyOperatorsToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew,
                            const std::vector<LanOneBody> &up, const std::vector<LanOneBody> &dn,
                            const std::vector<LanTwoBody> &upUp, const std::vector<LanTwoBody> &upDn,
                            const std::vector<LanTwoBody> &dnDn ) const;

    void applyCupToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, const std::vector<LanOneOperator> &Cup) const;
    void applyCdnToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, const std::vector<LanOneOperator> &Cdn) const;
    void applyCupDaggerToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew,
                            const std::vector<LanOneOperator> &Cup) const;
    void applyCdnDaggerToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew,
                            const std::vector<LanOneOperator> &Cdn) const;
 private:
    void setFromLNupNdn();
    void setNHilbertUpAndTableUp(LanczosBasis &lanBasisUp);
    void setNHilbertDnAndTableDn(LanczosBasis &lanBasisDn);
    void printMemoryInfo();

    void copy_deep(const RealMaterial& x);
    void move_deep(RealMaterial& x);
};

#endif //AFQMCLAB_REALMATERIAL_H