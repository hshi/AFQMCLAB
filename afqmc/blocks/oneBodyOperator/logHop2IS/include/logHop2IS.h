//
// Created by boruoshihao on 5/18/17.
//

#ifndef AFQMCLAB_LOGHOP2IS_H
#define AFQMCLAB_LOGHOP2IS_H

#include "../../../../../common/tensorHao/include/tensor_all.h"

//One body operator: two identical spin species.
//The operator is exp( M ) = 1 + M + 1/(2!) M^2 + 1/(3!) M^3 + ...
//M matrix is stored in LogHop2IS class.

class LogHop2IS
{
 public:
    std::complex<double> logw;
    tensor_hao::TensorHao<std::complex<double>,2> matrix;

    LogHop2IS();
    LogHop2IS(size_t L);
    LogHop2IS(const LogHop2IS& x);
    LogHop2IS(LogHop2IS&& x);
    ~LogHop2IS();

    LogHop2IS & operator  = (const LogHop2IS& x);
    LogHop2IS & operator  = (LogHop2IS&& x);

    size_t getL() const;
    double getMemory() const;

 private:
    void copy_deep(const LogHop2IS &x);
    void move_deep(LogHop2IS &x);
};

#endif //AFQMCLAB_LOGHOP2IS_H