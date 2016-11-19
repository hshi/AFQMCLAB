//
// Created by boruoshihao on 11/18/16.
//

#include <iostream>

#ifdef USE_OPENMP
#include <omp.h>
#endif

using namespace std;

int main()
{
    for (size_t Nhilbert = 1; Nhilbert<100; Nhilbert++ )
    {
        size_t counter = 0;
        #pragma omp parallel
        {
            #ifdef USE_OPENMP
            size_t threadRank = omp_get_thread_num();
            size_t threadSize = omp_get_num_threads();
            #else
            size_t threadRank = 0;
            size_t threadSize = 1;
            #endif

            size_t sizeEachThread = ( Nhilbert - 1 ) / threadSize + 1;
            size_t initIndex = sizeEachThread * threadRank;
            size_t endIndex = sizeEachThread * (threadRank + 1);

            if( initIndex > Nhilbert) initIndex = Nhilbert;
            if( endIndex > Nhilbert ) endIndex = Nhilbert;

            #pragma omp atomic
            counter += endIndex - initIndex;
        }

        cout<<counter - Nhilbert <<endl;
    }
    return 0;
}