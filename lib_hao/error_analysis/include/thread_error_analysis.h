#ifndef AFQMCLIB_THREAD_ERROR_ANALYSIS_H
#define AFQMCLIB_THREAD_ERROR_ANALYSIS_H

#include <iostream>
#include <vector>
#include <complex>
#include "../../../utilities/mpi_hao/include/mpi_fun.h"

//Calculate mean value and error bar between different thread
//Send mean value to all the thread
//Only send error bar to main thread

void calculateMeanErrorBetweenThread(std::complex<double> value_thread, std::complex<double> &mean, double &err);

void calculateMeanErrorBetweenThread(int N, const std::complex<double> *value_thread, std::complex<double> *mean, double *err);

void calculateMeanErrorBetweenThread(const std::vector<std::complex<double> > &value_thread,
                                     std::vector<std::complex<double> > &mean, std::vector<double> &err);
#endif