#include <math.h> 
#include <algorithm>
#include <iostream>
#include <complex>
#include <iomanip>
#include "../include/error_analysis.h"

using namespace std;

vector<size_t> getDivisor(const size_t n)
{
    vector<size_t > fact;
    for(size_t i=1; (i*i)<n; i++) {if((n%i)==0) {fact.push_back(i);fact.push_back(n/i);}}
    size_t sqrtn=lround(sqrt(static_cast<double>(n)));
    if((sqrtn*sqrtn)==n) fact.push_back(sqrtn);
    sort(fact.begin(),fact.end());
    return fact;
}