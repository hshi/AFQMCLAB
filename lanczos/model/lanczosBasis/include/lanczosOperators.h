//
// Created by boruoshihao on 11/19/16.
//

#ifndef AFQMCLAB_LANCZOSOPERATORS_H
#define AFQMCLAB_LANCZOSOPERATORS_H

struct LanOneBody
{
    size_t i;
    size_t j;
    std::complex<double> K;
};

struct LanTwoBody
{
    size_t i;
    size_t j;
    size_t k;
    size_t l;
    std::complex<double> V;
};

struct LanOneOperator
{
    size_t i;
    std::complex<double> C;
};

#endif //AFQMCLAB_LANCZOSOPERATOR_H
