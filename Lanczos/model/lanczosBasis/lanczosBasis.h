//
// Created by boruoshihao on 10/28/16.
//

#ifndef AFQMCLIB_LANCZOSBASIS_H
#define AFQMCLIB_LANCZOSBASIS_H

#include <cstddef>
#include <vector>

struct TableElement
{
    size_t index;
    int coefficient;
};

class LanczosBasis
{
    const static size_t maxParticleInStack =32;
    const static size_t maxBinomialInStack=800;

    size_t sizeOfBasis, numberOfParticle, index;
    size_t *positionOfParticle, *emptyPositionForParticle, *tempPositionOfParticle, *binomialTable;

    size_t positionOfParticleStack[maxParticleInStack], emptyPositionForParticleStack[maxParticleInStack];
    size_t tempPositionOfParticleStack[maxParticleInStack], binomialTableStack[maxBinomialInStack];
    std::vector<size_t> positionOfParticleHeap, emptyPositionForParticleHeap;
    std::vector<size_t> tempPositionOfParticleHeap, binomialTableHeap;

 public:
    LanczosBasis(size_t L, size_t N);

    size_t getSizeOfBasis() const;
    size_t getNumberOfParticle() const;
    const size_t * getPositionOfParticle() const;
    inline size_t  binomial(size_t n, size_t k) const { return binomialTable[ k + n * (numberOfParticle +1 ) ]; }
    inline size_t &binomial(size_t n, size_t k)       { return binomialTable[ k + n * (numberOfParticle +1 ) ]; }
    void init();
    int next();
    size_t getIndexFromPosition(const size_t *position);

    TableElement getInfoByCiDaggerCj(size_t i, size_t j);

 private:
    void linkStackOrHeap();
    void setBinomialTable();

    LanczosBasis(const LanczosBasis& x);
    LanczosBasis & operator  = (const LanczosBasis& x);
};

#endif //AFQMCLIB_LANCZOSBASIS_H