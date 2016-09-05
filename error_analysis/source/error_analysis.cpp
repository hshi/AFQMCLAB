#include <math.h> 
#include <algorithm>
#include <iostream>
#include <complex>
#include <iomanip>
#include "../include/error_analysis.h"

using std::cout;
using std::cin;
using std::vector;
using std::complex;
using std::sort;

void get_factors(const size_t n, vector<size_t>& fact)
{
    if(!fact.empty()) fact.clear();
    for(size_t i=1; (i*i)<n; i++) {if((n%i)==0) {fact.push_back(i);fact.push_back(n/i);}}
    size_t sqrtn=lround(sqrt(static_cast<double>(n)));
    if((sqrtn*sqrtn)==n) fact.push_back(sqrtn);
    sort(fact.begin(),fact.end()); 
}