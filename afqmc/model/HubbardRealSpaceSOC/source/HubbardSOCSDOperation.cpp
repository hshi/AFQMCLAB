//
// Created by boruoshihao on 1/17/17.
//

#include "../include/HubbardSOCSDOperation.h"

using namespace std;
using namespace tensor_hao;

void fillWalkerRandomly(SD &walker, const HubbardSOC &model)
{
    size_t L = model.getL();
    size_t N = model.getN();
    walker.resize(2*L, N);

    walker.randomFill();
}

void fillWalkerFromModel(SD &walker, HubbardSOC &model)
{
    size_t L = model.getL();
    size_t N = model.getN();
    walker.resize(2*L, N);

    model.setKEigenValueAndVector();
    const TensorHao< complex<double>, 2 > &KEigenVector = model.getKEigenVector();
    TensorHao<complex<double>,2> &wf = walker.wfRef();

    copy( KEigenVector.data(), KEigenVector.data()+2*L*N, wf.data() );
}

void fillWalkerFromModelIncludePinningField(SD &walker, HubbardSOC &model)
{
    size_t L = model.getL();
    size_t N = model.getN();
    walker.resize(2*L, N);

    TensorHao< complex<double>, 2 > H0Vector = model.getK();

    const TensorHao< double, 1> &mu = model.getMu();
    const TensorHao< double, 1> &hx = model.getHx();
    const TensorHao< double, 1> &hy = model.getHy();
    const TensorHao< double, 1> &hz = model.getHz();

    for(size_t i = 0; i < L; ++i)
    {
        H0Vector(i,i)     += ( -mu(i) + hz(i)*0.5 );
        H0Vector(i+L,i+L) += ( -mu(i) - hz(i)*0.5 );
        H0Vector(i, i+L)  += complex<double>( hx(i)*0.5, -hy(i)*0.5 );
        H0Vector(i+L, i)  += complex<double>( hx(i)*0.5,  hy(i)*0.5 );
    }

    TensorHao< double, 1> H0Value(2*L);
    BL_NAME(eigen)(H0Vector, H0Value);

    TensorHao<complex<double>,2> &wf = walker.wfRef();
    copy( H0Vector.data(), H0Vector.data()+2*L*N, wf.data() );
}