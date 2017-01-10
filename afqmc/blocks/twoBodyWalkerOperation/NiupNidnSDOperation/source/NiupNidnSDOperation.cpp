//
// Created by boruoshihao on 1/10/17.
//

#include "../include/NiupNidnSDOperation.h"

using namespace std;
using namespace tensor_hao;

void applyTwoBodySampleToRightWalker(const SD &walker, SD &walkerNew, const NiupNidnSample &twoBodySample)
{
    size_t L = walker.getL(); size_t N = walker.getN(); size_t halfL = twoBodySample.getL();

    if( L != halfL*2 ) { cout<<"Error!!! NiupNidnSample size is not consistent with walker!"<<endl; exit(1); }
    if( walkerNew.getL() != L  ||  walkerNew.getN() != N ) walkerNew.wfRef().resize( L, N );

    const TensorHao<complex<double>,2> &wf = walker.getWf();
    TensorHao<complex<double>,2> &wfNew = walkerNew.wfRef();

    const TensorHao<complex<double>,1> &diag00 = twoBodySample.diag00;
    const TensorHao<complex<double>,1> &diag10 = twoBodySample.diag10;
    const TensorHao<complex<double>,1> &diag01 = twoBodySample.diag01;
    const TensorHao<complex<double>,1> &diag11 = twoBodySample.diag11;

    for(size_t j = 0; j < N; ++j)
    {
        for(size_t i = 0; i < halfL; ++i)
        {
            wfNew(i,j)        = diag00(i) * wf(i,j) + diag01(i)*wf(i+halfL, j);
            wfNew(i+halfL, j) = diag10(i) * wf(i,j) + diag11(i)*wf(i+halfL, j);
        }
    }

    walkerNew.logwRef() = twoBodySample.logw + walker.getLogw();
}

void applyTwoBodySampleToLeftWalker(const SD &walker, SD &walkerNew, const NiupNidnSample &twoBodySample)
{
    size_t L = walker.getL(); size_t N = walker.getN(); size_t halfL = twoBodySample.getL();

    if( L != halfL*2 ) { cout<<"Error!!! NiupNidnSample size is not consistent with walker!"<<endl; exit(1); }
    if( walkerNew.getL() != L  ||  walkerNew.getN() != N ) walkerNew.wfRef().resize( L, N );

    const TensorHao<complex<double>,2> &wf = walker.getWf();
    TensorHao<complex<double>,2> &wfNew = walkerNew.wfRef();

    const TensorHao<complex<double>,1> diag00 = conj( twoBodySample.diag00 );
    const TensorHao<complex<double>,1> diag10 = conj( twoBodySample.diag01 );
    const TensorHao<complex<double>,1> diag01 = conj( twoBodySample.diag10 );
    const TensorHao<complex<double>,1> diag11 = conj( twoBodySample.diag11 );

    for(size_t j = 0; j < N; ++j)
    {
        for(size_t i = 0; i < halfL; ++i)
        {
            wfNew(i,j)        = diag00(i) * wf(i,j) + diag01(i)*wf(i+halfL, j);
            wfNew(i+halfL, j) = diag10(i) * wf(i,j) + diag11(i)*wf(i+halfL, j);
        }
    }

    walkerNew.logwRef() = conj( twoBodySample.logw ) + walker.getLogw();
}