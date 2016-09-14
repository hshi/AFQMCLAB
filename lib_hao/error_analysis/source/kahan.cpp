#include "../include/kahan.h"

template<class T>
KahanData<T> KahanData<T>::operator += (const T& add)
{
    //We can not use it because "volatile std::complex" does not support well
    //volatile T  y = add-c;        // volatile here is to avoid complier's agressive optimazation
    //volatile T  t = sum+y;        // otherwise, compiler might set c to zero directly

    T  y = add-accumulateError;
    T  t = sum+y;
    accumulateError    = (t-sum)-y;
    sum  = t;
    return *this;
}

using namespace std;

template KahanData<float> KahanData<float>::operator += (const float& add);
template KahanData<double> KahanData<double>::operator += (const double& add);
template KahanData<complex<float>> KahanData<complex<float>>::operator += (const complex<float>& add);
template KahanData<complex<double>> KahanData<complex<double>>::operator += (const complex<double>& add);
