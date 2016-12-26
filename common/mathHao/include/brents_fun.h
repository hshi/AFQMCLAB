#ifndef AFQMCLAB_BRENTS_FUN_H
#define AFQMCLAB_BRENTS_FUN_H

#include <iostream>
#include <cmath>
#include <algorithm>
#include <functional>

//f is the function, solution is the solution lower and upper is the bound, tol is the tolerance condition
//int returns the iterated step
//0:            Fail.   Signs of f(lower_bound) and f(upper_bound) must be opposites.
//max_iter:     Fail.   The solution does not converge or iterations are not sufficient.
//1~max_iter-1: Sucess. Return the number of iteration.
unsigned int brentRootFinding(std::function<double(double)> f, double &solution, double lower = -100.0, double upper = 100.0,
                              double tol = 0.0001, unsigned int max_iter = 1000);

#endif
