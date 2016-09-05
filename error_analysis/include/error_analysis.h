#ifndef AFQMCLIB_ERROR_ANALYSIS_H
#define AFQMCLIB_ERROR_ANALYSIS_H

#include <iostream>
#include <vector>
#include <complex>
#include <typeinfo>
#include "kahan.h"

void get_factors(const size_t n, std::vector<size_t>& fact);

//================================================================================================
//For pointer: get_average, get_error, error_analysis, error_analysis_blk, error_analysis_blk_loop
//================================================================================================
template<class T> void get_average(const size_t L, const T* array, T& mean)
{
    KahanData<T> ksum;
    for(size_t i=0; i<L; i++) ksum+=array[i];
    mean=ksum.sum/static_cast<T>(L);
}

template<class T> void get_err(const size_t L, const T* array, const T& mean, T& err)
{
    if(typeid(T)==typeid(std::complex<float>)) std::cout<<"Warning!!!!!! complex data should not call this routine!\n";
    if(typeid(T)==typeid(std::complex<double>)) std::cout<<"Warning!!!!!! complex data should not call this routine!\n";
   
    if(L==1) {err=0;return;}
    KahanData<T> ksum;
    for(size_t i=0; i<L; i++) ksum+=(array[i]-mean)*(array[i]-mean);
    err=ksum.sum/static_cast<T>(L);    //get variance
    err=sqrt(err/static_cast<T>(L-1)); //get standard diviation of mean(QMC error bar)
}

template<class T> void get_err(const size_t L, const std::complex<T>* array, const std::complex<T>& mean, T& err)
{
    if(L==1) {err=0;return;}
    KahanData<T> ksum;
    for(size_t i=0; i<L; i++) ksum+=std::norm(array[i]-mean);
    err=ksum.sum/static_cast<T>(L);    //get variance
    err=sqrt(err/static_cast<T>(L-1)); //get standard diviation of mean(QMC error bar)
}

 //when T=P, call get_err(size_t, T*, T&, T&)
 //when T=complex<P> call get_err(size_t, complex<P>*, complex<P>&, P&) 
 //Other case will not working
template<class T, class P> void error_analysis(const size_t L, const T* array, T& mean, P& err)
{
    get_average(L,array,mean);
    get_err(L,array,mean,err);
}

 //Only works for T=P, T=complex<P>
template<class T, class P> void error_analysis_blk(const size_t L, const size_t blk_size, T* array, T& mean, P& err)
{
    if(L%blk_size!=0) std::cout<<"Warning!!!!!! L can not be divided by blk_size!\n";
   
    size_t blk_num=L/blk_size;
    T* pt_blk_size=array;
    T* pt_blk_num=new T[blk_num];
   
    for(size_t i=0; i<blk_num; i++)
    {
        get_average(blk_size,pt_blk_size,mean);
        pt_blk_num[i]=mean;
        pt_blk_size+=blk_size;  
    }
    
    error_analysis(blk_num,pt_blk_num,mean,err);
    delete[] pt_blk_num;
}

 //Only works for T=P, T=complex<P>
template<class T, class P> void error_analysis_blk_loop
(const size_t L, T* array, std::vector<size_t>& fact, std::vector<T>& mean, std::vector<P>& err)
{
    get_factors(L,fact);
    mean.resize(fact.size());
    err.resize(fact.size());
    for(size_t i=0; i<fact.size(); i++) error_analysis_blk(L,fact[i], array,mean[i], err[i]);
}


//===============================================================================================
//For vector: get_average, get_error, error_analysis, error_analysis_blk, error_analysis_blk_loop
//===============================================================================================
template<class T> void get_average(const std::vector<T>& vec, T& mean)
{
    size_t  L=vec.size();
    get_average(L,vec.data(),mean);
}

 //Only works for T=P, T=complex<P> 
template<class T, class P> void get_err(const std::vector<T>& vec, const T& mean, P& err)
{
    size_t  L=vec.size();
    get_err(L,vec.data(),mean,err);
}


 //Only works for T=P, T=complex<P> 
template<class T, class P> void error_analysis(const std::vector<T>& vec, T& mean, P& err)
{
    size_t  L=vec.size();
    error_analysis(L,vec.data(),mean,err);
}

 //Only works for T=P, T=complex<P> 
template<class T, class P> void error_analysis_blk(const size_t blk_size, std::vector<T>& vec, T& mean, P& err)
{
    size_t  L=vec.size();
    error_analysis_blk(L,blk_size,vec.data(),mean,err);
}

 //Only works for T=P, T=complex<P> 
template<class T, class P> void error_analysis_blk_loop
(std::vector<T>& vec, std::vector<size_t>& fact, std::vector<T>& mean, std::vector<P>& err)
{
    size_t L=vec.size();
    error_analysis_blk_loop(L,vec.data(),fact,mean,err);
}


#endif
