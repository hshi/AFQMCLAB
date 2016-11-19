//
// Created by boruoshihao on 11/19/16.
//

#ifndef AFQMCLIB_LANCZOSOPERATORS_H
#define AFQMCLIB_LANCZOSOPERATORS_H

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

#endif //AFQMCLIB_LANCZOSOPERATOR_H
