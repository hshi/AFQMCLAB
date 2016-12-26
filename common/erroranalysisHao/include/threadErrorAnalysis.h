#ifndef AFQMCLAB_THREAD_ERROR_ANALYSIS_H
#define AFQMCLAB_THREAD_ERROR_ANALYSIS_H

#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
#include "../../mpiHao/include/mpi_fun.h"

//Calculate mean value and error bar between different thread
//Send mean value to all the thread
//Only send error bar to main thread

std::complex<double> calculateMeanBetweenThreads(std::complex<double> valueEachThread);
std::complex<double> calculateVarianceBetweenThreads(std::complex<double> valueEachThread, std::complex<double> mean);
std::complex<double> calculateErrorBetweenThreads(std::complex<double> valueEachThread, std::complex<double> mean);
std::tuple< std::complex<double>, std::complex<double> > calculateMeanErrorBetweenThreads(std::complex<double> valueEachThread);


std::vector< std::complex<double> > calculateMeanBetweenThreads(size_t N, const std::complex<double> *valueEachThread);
std::vector< std::complex<double> > calculateVarianceBetweenThreads(size_t N, const std::complex<double> *valueEachThread,
                                                                    const std::complex<double> * mean);
std::vector< std::complex<double> > calculateErrorBetweenThreads(size_t N, const std::complex<double> *valueEachThread,
                                                                 const std::complex<double> * mean);
std::tuple<  std::vector< std::complex<double> >, std::vector< std::complex<double> >  >
calculateMeanErrorBetweenThreads(size_t N, const std::complex<double> *valueEachThread);


std::vector< std::complex<double> > calculateMeanBetweenThreads(const std::vector<std::complex<double> > &valueEachThread);
std::vector< std::complex<double> > calculateVarianceBetweenThreads(const std::vector<std::complex<double> > &valueEachThread,
                                                                    const std::vector<std::complex<double> > &mean);
std::vector< std::complex<double> > calculateErrorBetweenThreads(const std::vector<std::complex<double> > &valueEachThread,
                                                                 const std::vector<std::complex<double> > &mean);
std::tuple<  std::vector< std::complex<double> >, std::vector< std::complex<double> >  >
calculateMeanErrorBetweenThreads(const std::vector<std::complex<double> > &valueEachThread);

#endif