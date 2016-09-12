#ifndef SORT_FUN_H
#define SORT_FUN_H

#include <iostream>
#include <vector>
#include <complex>
#include <algorithm> 
#include <cmath>

 
/********************************/
/*Find the index during the sort*/
/********************************/
template<typename T> class CompareIndicesByAnotherVectorValues
{
    const std::vector<T>* values;
    public:
    CompareIndicesByAnotherVectorValues(const std::vector<T>* val) : values(val) {}
    bool operator() (const size_t & a, const size_t & b) const { return (*values)[a] < (*values)[b]; }
};

template <typename T> 
std::vector<size_t> sort_indexes(const std::vector<T> &v) 
{
    // initialize original index locations
    std::vector<size_t> idx(v.size());
    for (size_t i = 0; i != idx.size(); ++i) idx[i] = i;
   
    CompareIndicesByAnotherVectorValues<T> idex_comp(&v);
    // sort indexes based on comparing values in v
    std::sort(idx.begin(), idx.end(), idex_comp);
   
    return idx;
}

#endif
