#include <iostream>
#include <algorithm>
#include "../include/fftw_hao.h"

using namespace std;

FFTServer::FFTServer()
{
    dimen=1; n.push_back(1); size=1;

    allocateInOutSpace();

    createPlans();
}

FFTServer::FFTServer(int dimenInput, const vector<int> & nInput, char format)
{
    setDimenNSizeFromInput(dimenInput, nInput, format);

    allocateInOutSpace();

    createPlans();
}


FFTServer::FFTServer(const FFTServer& x)
{
    dimen=x.dimen; n=x.n; size=x.size;

    allocateInOutSpace();

    createPlans();
}


FFTServer::~FFTServer()
{
    deallocateInOutSpace();
    destroyPlans();
}


FFTServer& FFTServer::operator  = (const FFTServer& x)
{
    deallocateInOutSpace();
    destroyPlans();

    dimen=x.dimen; n=x.n; size=x.size;
    allocateInOutSpace();
    createPlans();

    return *this;
}

const complex<double> * FFTServer::fourier_forw(const complex<double> *inarray)
{
    std::copy(inarray,inarray+size,inforw);
    fftw_execute(planforw);
    return outforw;
}

const complex<double> * FFTServer::fourier_back(const complex<double> *inarray)
{
    std::copy(inarray,inarray+size,inback);
    fftw_execute(planback);
    return outback;
}

int FFTServer::getDimen() const { return dimen; }

const std::vector<int>& FFTServer::getN() const { return n; }

int FFTServer::getSize() const { return size;}

void FFTServer::setDimenNSizeFromInput(int dimenInput, const vector<int> &nInput, char format)
{
    dimen =dimenInput;

    if(format=='C')      n = vector<int>(nInput.rbegin(), nInput.rend()); //Column-major: fortran style
    else if(format=='R') n = nInput;                                         //Row-major: c style
    else {cout<<"Do not know the format!!!! "<<format<<endl; exit(1); }

    size =1;
    for(int i=0; i < dimen; i++) size *= n[i];
}

void FFTServer::allocateInOutSpace()
{
    inforw =new complex<double>[size];
    outforw =new complex<double>[size];
    inback =new complex<double>[size];
    outback =new complex<double>[size];
}

void FFTServer::deallocateInOutSpace()
{
    if(inforw)  delete[] inforw;
    if(outforw) delete[] outforw;
    if(inback)  delete[] inback;
    if(outback) delete[] outback;
}

void FFTServer::createPlans()
{
    planforw =fftw_plan_dft(dimen, n.data(), reinterpret_cast<fftw_complex*>(inforw), reinterpret_cast<fftw_complex*>
                            (outforw), FFTW_FORWARD, FFTW_MEASURE);
    planback =fftw_plan_dft(dimen, n.data(), reinterpret_cast<fftw_complex*>(inback), reinterpret_cast<fftw_complex*>
                            (outback), FFTW_BACKWARD, FFTW_MEASURE);
}

void FFTServer::destroyPlans()
{
    fftw_destroy_plan(planforw);
    fftw_destroy_plan(planback);
}
