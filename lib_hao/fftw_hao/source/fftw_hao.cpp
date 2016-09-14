#include <iostream>
#include <algorithm>
#include "../include/fftw_hao.h"

using namespace std;

FFTServer::FFTServer()
{
    dimen=1;
    n=new int[1]; n[0]=1;
    L=1;
    inforw =new complex<double>[1];
    outforw=new complex<double>[1];
    inback =new complex<double>[1];
    outback=new complex<double>[1];
    planforw=fftw_plan_dft(dimen,n,reinterpret_cast<fftw_complex*>(inforw),reinterpret_cast<fftw_complex*>(outforw),
                           FFTW_FORWARD, FFTW_MEASURE);
    planback=fftw_plan_dft(dimen,n,reinterpret_cast<fftw_complex*>(inback),reinterpret_cast<fftw_complex*>(outback),
                           FFTW_BACKWARD,FFTW_MEASURE);
}

FFTServer::FFTServer(int Dc, const int* Nc, char format)
{
    dimen=Dc;
    n=new int[dimen];
    if(format=='C') std::reverse_copy(Nc,Nc+dimen,n);  //Column-major: fortran style
    else if(format=='R') std::copy(Nc,Nc+dimen,n); //Row-major: c style
    else {cout<<"Do not know the format!!!! "<<format<<endl; exit(1); }

    L=1; for(int i=0; i<dimen; i++) L*=n[i];
   
    inforw =new complex<double>[L];
    outforw=new complex<double>[L];
    inback =new complex<double>[L];
    outback=new complex<double>[L];
   
    planforw=fftw_plan_dft(dimen,n,reinterpret_cast<fftw_complex*>(inforw),reinterpret_cast<fftw_complex*>(outforw),
                           FFTW_FORWARD, FFTW_MEASURE);
    planback=fftw_plan_dft(dimen,n,reinterpret_cast<fftw_complex*>(inback),reinterpret_cast<fftw_complex*>(outback),
                           FFTW_BACKWARD,FFTW_MEASURE);
}


FFTServer::FFTServer(const FFTServer& x) 
{
    dimen=x.dimen;
    n=new int[dimen]; std::copy(x.n,x.n+dimen,n);
    L=x.L;
    inforw =new complex<double>[L];
    outforw=new complex<double>[L];
    inback =new complex<double>[L];
    outback=new complex<double>[L];
    planforw=fftw_plan_dft(dimen,n,reinterpret_cast<fftw_complex*>(inforw),reinterpret_cast<fftw_complex*>(outforw),
                           FFTW_FORWARD, FFTW_MEASURE);
    planback=fftw_plan_dft(dimen,n,reinterpret_cast<fftw_complex*>(inback),reinterpret_cast<fftw_complex*>(outback),
                           FFTW_BACKWARD,FFTW_MEASURE);
}


FFTServer::~FFTServer()
{
    if(n)       delete[] n;
    if(inforw)  delete[] inforw;
    if(outforw) delete[] outforw;
    if(inback)  delete[] inback;
    if(outback) delete[] outback; 
    fftw_destroy_plan(planforw);
    fftw_destroy_plan(planback);
}


FFTServer& FFTServer::operator  = (const FFTServer& x)
{
    dimen=x.dimen;
    if(n) delete[] n; n=new int[dimen]; std::copy(x.n,x.n+dimen,n);
    L=x.L;
    if(inforw)  delete[] inforw;  inforw =new complex<double>[L];
    if(outforw) delete[] outforw; outforw=new complex<double>[L];
    if(inback)  delete[] inback;  inback =new complex<double>[L];
    if(outback) delete[] outback; outback=new complex<double>[L];
   
    fftw_destroy_plan(planforw);
    planforw=fftw_plan_dft(dimen,n,reinterpret_cast<fftw_complex*>(inforw),reinterpret_cast<fftw_complex*>(outforw),
                           FFTW_FORWARD, FFTW_MEASURE);
   
    fftw_destroy_plan(planback);
    planback=fftw_plan_dft(dimen,n,reinterpret_cast<fftw_complex*>(inback),reinterpret_cast<fftw_complex*>(outback),
                           FFTW_BACKWARD,FFTW_MEASURE);
   
    return *this;
}

complex<double>* FFTServer::fourier_forw(const complex<double>* inarray)
{
    std::copy(inarray,inarray+L,inforw);
    fftw_execute(planforw);
    return outforw;
}

complex<double>* FFTServer::fourier_back(const complex<double>* inarray)
{
    std::copy(inarray,inarray+L,inback);
    fftw_execute(planback);
    return outback;
}

int FFTServer::returnDimen() const { return dimen; }

const int* FFTServer::returnN() const { return n; }

int FFTServer::returnSize() const { return L;}