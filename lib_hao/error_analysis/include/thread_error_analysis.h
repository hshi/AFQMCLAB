#ifndef AFQMCLIB_THREAD_ERROR_ANALYSIS_H
#define AFQMCLIB_THREAD_ERROR_ANALYSIS_H

#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
#include "../../../utilities/mpi_hao/include/mpi_fun.h"

//Calculate mean value and error bar between different thread
//Send mean value to all the thread
//Only send error bar to main thread

std::complex<double> calculateMeanBetweenThreads(std::complex<double> valueEachThread);
std::complex<double> calculateVarianceBetweenThreads(std::complex<double> valueEachThread, std::complex<double> mean);
std::complex<double> calculateErrorBetweenThreads(std::complex<double> valueEachThread, std::complex<double> mean);
std::tuple< std::complex<double>, std::complex<double> > calculateMeanErrorBetweenThreads(std::complex<double> valueEachThread);


std::vector< std::complex<double> > calculateMeanBetweenThreads(int N, const std::complex<double> *valueEachThread);
std::vector< std::complex<double> > calculateVarianceBetweenThreads(int N, const std::complex<double> *valueEachThread,
                                                                    const std::complex<double> * mean);
std::vector< std::complex<double> > calculateErrorBetweenThreads(int N, const std::complex<double> *valueEachThread,
                                                                 const std::complex<double> * mean);
std::tuple<  std::vector< std::complex<double> >, std::vector< std::complex<double> >  >
calculateMeanErrorBetweenThreads(int N, const std::complex<double> *valueEachThread);


std::vector< std::complex<double> > calculateMeanBetweenThreads(const std::vector<std::complex<double> > &valueEachThread);
std::vector< std::complex<double> > calculateVarianceBetweenThreads(const std::vector<std::complex<double> > &valueEachThread,
                                                                    const std::vector<std::complex<double> > &mean);
std::vector< std::complex<double> > calculateErrorBetweenThreads(const std::vector<std::complex<double> > &valueEachThread,
                                                                 const std::vector<std::complex<double> > &mean);
std::tuple<  std::vector< std::complex<double> >, std::vector< std::complex<double> >  >
calculateMeanErrorBetweenThreads(const std::vector<std::complex<double> > &valueEachThread);

#endif