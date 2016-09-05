#ifndef AFQMCLIB_THREAD_ERROR_ANALYSIS_H
#define AFQMCLIB_THREAD_ERROR_ANALYSIS_H

#include <iostream>
#include <vector>
#include <complex>
#include "../../mpi_hao/include/mpi_fun.h"

//Calculate mean value and error bar between different thread
//Send mean value to all the thread
//Only send error bar to main thread

void calculate_mean_err_between_thread(std::complex<double> value_thread, std::complex<double>& mean, double& err);

void calculate_mean_err_between_thread(int N, const std::complex<double>* value_thread, std::complex<double>* mean, double* err);

void calculate_mean_err_between_thread(const std::vector< std::complex<double> >& value_thread,
                                             std::vector< std::complex<double> >& mean, std::vector<double>& err);
#endif