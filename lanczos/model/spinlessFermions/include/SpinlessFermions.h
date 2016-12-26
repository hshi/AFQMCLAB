//
// Created by boruoshihao on 11/18/16.
//

#ifndef AFQMCLAB_SPINLESSFERMIONS_H
#define AFQMCLAB_SPINLESSFERMIONS_H

#include "../../../interface/include/modelInterface.h"
#include "../../../interface/include/LanczosBasisWf.h"
#include "../../lanczosBasis/include/lanczosBasis.h"

class SpinlessFermions : public ModelInterface
{
    size_t L, N;
    std::vector<LanOneBody> K;
    std::vector<LanTwoBody> V;
    size_t Nhilbert;
 public:
    SpinlessFermions(size_t L, size_t N);
    SpinlessFermions(const std::string &filename);
    SpinlessFermions(const SpinlessFermions& x);
    SpinlessFermions(SpinlessFermions && x);
    SpinlessFermions & operator  = (const SpinlessFermions& x);
    SpinlessFermions & operator  = (SpinlessFermions&& x);

    SpinlessFermions generateNewModel(size_t L, size_t N);

    size_t getL() const;
    size_t getN() const;
    const std::vector<LanOneBody> &getK() const;
    const std::vector<LanTwoBody> &getV() const;
    virtual size_t getWfSize() const;
    void setK(const std::vector<LanOneBody> &K);
    void setV(const std::vector<LanTwoBody> &V);

    void read(const std::string &filename);
    void write(const std::string &filename);

    virtual void applyHToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const;
    void applyKToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const;
    void applyVToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const;
    void applyNiNjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const;
    void applyCiDaggerCjToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew, size_t i, size_t j) const;

    void applyOperatorsToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew,
                            const std::vector<LanOneBody> &K,
                            const std::vector<LanTwoBody> &V) const;

    void applyCreationOperatorsToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew,
                                    const std::vector<LanOneOperator> &C) const;
    void applyAnnihilationOperatorsToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew,
                                    const std::vector<LanOneOperator> &C) const;


 private:
    void printMemoryInfo();
    void copy_deep(const SpinlessFermions& x);
    void move_deep(SpinlessFermions& x);
};

#endif //AFQMCLAB_SPINLESSFERMIONS_H