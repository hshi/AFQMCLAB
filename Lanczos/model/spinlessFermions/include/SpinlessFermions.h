//
// Created by boruoshihao on 11/18/16.
//

#ifndef AFQMCLIB_SPINLESSFERMIONS_H
#define AFQMCLIB_SPINLESSFERMIONS_H

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

    size_t getL() const;
    size_t getN() const;
    const std::vector<LanOneBody> &getK() const;
    const std::vector<LanTwoBody> &getV() const;
    virtual size_t getWfSize() const;
    void setK(const std::vector<LanOneBody> &K);
    void setV(const std::vector<LanTwoBody> &V);

    void read(const std::string &filename);
    void write(const std::string &filename);

    void applyOperatorsToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew,
                            const std::vector<LanOneBody> &K,
                            const std::vector<LanTwoBody> &V) const;

 private:
    SpinlessFermions(const SpinlessFermions& x);
    SpinlessFermions & operator  = (const SpinlessFermions& x);
};

#endif //AFQMCLIB_SPINLESSFERMIONS_H