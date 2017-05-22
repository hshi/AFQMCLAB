//
// Created by boruoshihao on 5/18/17.
//

#ifndef AFQMCLAB_LOGHOP2IS_H
#define AFQMCLAB_LOGHOP2IS_H

#include "../../../../../common/tensorHao/include/tensor_all.h"

//One body operator: two identical spin species.
//The operator is exp( M ) = 1 + M + 1/(2!) M^2 + 1/(3!) M^3 + ...
//M matrix is stored in LogHop2is class.

class LogHop2is
{
 public:
    std::complex<double> logw;
    tensor_hao::TensorHao<std::complex<double>,2> matrix;

    LogHop2is();
    LogHop2is(size_t L);
    LogHop2is(const LogHop2is& x);
    LogHop2is(LogHop2is&& x);
    ~LogHop2is();

    LogHop2is & operator  = (const LogHop2is& x);
    LogHop2is & operator  = (LogHop2is&& x);

    size_t getL() const;
    double getMemory() const;

 private:
    void copy_deep(const LogHop2is &x);
    void move_deep(LogHop2is &x);
};

#endif //AFQMCLAB_LOGHOP2IS_H