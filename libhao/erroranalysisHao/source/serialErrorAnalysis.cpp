#include <math.h> 
#include <algorithm>
#include <complex>
#include "../include/serialErrorAnalysis.h"

using namespace std;

vector<size_t> getDivisors(const size_t n)
{
    vector<size_t > divisors;
    for(size_t i=1; (i*i)<n; i++)
    {
        if( (n%i)==0 )
        {
            divisors.push_back(i);
            divisors.push_back(n/i);
        }
    }

    size_t sqrtn=lround( sqrt( static_cast<double>(n) ) );

    if( (sqrtn*sqrtn)==n ) divisors.push_back(sqrtn);

    sort(divisors.begin(),divisors.end());

    return divisors;
}