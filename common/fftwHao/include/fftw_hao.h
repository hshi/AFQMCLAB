#ifndef AFQMCLAB_FFTW_HAO_H
#define AFQMCLAB_FFTW_HAO_H

#include <complex>
#include "fftw3.h"
#include <vector>

class FFTServer
{
 private:
    int dimen;
    std::vector<int> n;
    int size;
    std::complex<double>* inforw;
    std::complex<double>* outforw;
    std::complex<double>* inback;
    std::complex<double>* outback;
    fftw_plan planforw;
    fftw_plan planback;

 public:
    FFTServer();
    FFTServer(int dimenInput, const std::vector<int>& nInput, char format); //'C' Column-major: fortran style;
                                                                            // 'R' Row-major: c style
    FFTServer(const FFTServer& x);
    ~FFTServer();
   
    FFTServer& operator  = (const FFTServer& x);

    const std::complex<double> * fourier_forw(const std::complex<double> *inarray);
    const std::complex<double> * fourier_back(const std::complex<double> *inarray);

    int getDimen() const;
    const std::vector<int >& getN() const;
    int getSize() const;

 private:
    void setDimenNSizeFromInput(int dimenInput, const std::vector<int> &nInput, char format);
    void allocateInOutSpace();
    void createPlans();
    void deallocateInOutSpace();
    void destroyPlans();
};

#endif
