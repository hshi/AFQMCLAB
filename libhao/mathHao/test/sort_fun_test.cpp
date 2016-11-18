#include "../include/sort_fun.h"
#include "../../testHao/gtest_custom.h"


using namespace std;

TEST (sort_fun, sort_indexes)
{
    vector<double> v={2.0,1.1,3.0,4.0,0.0,1.1};
    vector<size_t> idx=sort_indexes(v);

    size_t flag=0;
    for(size_t i=0; i<(idx.size()-1); i++) 
    {
        if(v[idx[i]]>v[idx[i+1]]) flag++;
    }

    EXPECT_FALSE (flag);
}