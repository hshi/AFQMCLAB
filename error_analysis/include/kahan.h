#ifndef AFQMCLIB_KAHAN_H
#define AFQMCLIB_KAHAN_H
#include <iostream>
#include <complex>

template<class T> class KahanData
{
 public:
    T sum,c;
    /*********************/
    /*PART I: CONSTRUCTOR*/
    /*********************/
    //Void constructor:
      KahanData(void):sum(0),c(0){}
    //Sum value constructor
      KahanData(const T& x):sum(x),c(0){}
    //Copy constructor:
      KahanData(const KahanData<T>& x):sum(x.sum),c(x.c){}
   
    /*********************/
    /*PART II: DESTRUCTOR*/
    /*********************/
    //Destructor
      ~KahanData(){}
   
    //copy-assigment
    KahanData<T> operator  = (const T & x) {sum=x; c=0; return *this;}
    KahanData<T> operator  = (const KahanData<T> & x) {sum=x.sum;c=x.c;return *this;}
   
    //+=
    KahanData<T> operator += (const T& add);

    //Declare operator += in kahan.cpp, this will avoid agressive optimazation
    //We can also change CMAKELIST.TXT, to only reduce optimazation flag for this library
    //If we put in the header, we can not only optimaze this library!!!
    //KahanData<T> operator += (const T& add) 
    //{
    //    //We can not use it because "volatile std::complex" does not support well
    //    //volatile T  y = add-c;        // volatile here is to avoid complier's agressive optimazation
    //    //volatile T  t = sum+y;        // otherwise, compiler might set c to zero directly
    //               T  y = add-c;
    //               T  t = sum+y; 
    //                c = (t-sum)-y;
    //              sum = t;
    //    return *this;
    //}
   
};

//cout
template <class T>
std::ostream& operator<< (std::ostream &out, const KahanData<T> &x)
{
    out<<x.sum<<" "<<x.c;
    return out;
}

#endif
