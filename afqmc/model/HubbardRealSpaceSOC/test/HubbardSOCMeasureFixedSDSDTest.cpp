//
// Created by Hao Shi on 8/2/17.
//

#include "../include/HubbardSOCMeasureFixedSDSD.h"
#include "createZeroUInputFile.h"

using namespace std;
using namespace tensor_hao;

TEST(HubbardSOCMeasureFixedSDSDTest, energy)
{
    string filename = "hubbard.dat";

    if( MPIRank() == 0 ) createZeroUInputFile(filename);
    MPIBarrier();

    HubbardSOC hubbard(filename);

    size_t L  = hubbard.getL();
    size_t N  = hubbard.getN();
    const TensorHao< complex<double>, 2 > &K = hubbard.getK();
    const TensorHao< double, 1> &mu = hubbard.getMu();
    const TensorHao< double, 1> &hx = hubbard.getHx();
    const TensorHao< double, 1> &hy = hubbard.getHy();
    const TensorHao< double, 1> &hz = hubbard.getHz();

    TensorHao< complex<double>, 2 > EigenVector(K);
    TensorHao< double, 1 > EigenValue(2*L);

    for(size_t i = 0; i < L; ++i)
    {
        EigenVector(i,i)     += ( -mu(i) + hz(i)*0.5 );
        EigenVector(i+L,i+L) += ( -mu(i) - hz(i)*0.5 );
        EigenVector(i,i+L)   += complex<double>( hx(i)*0.5,  -hy(i)*0.5 );
        EigenVector(i+L,i)   += complex<double>( hx(i)*0.5,   hy(i)*0.5 );
    }
    eigen_cpu(EigenVector, EigenValue);

    SD sdLeft( 2*L, N );
    for(size_t j = 0; j < N; ++j)
    {
        for(size_t i = 0; i < 2*L ; ++i)
        {
            sdLeft.wfRef()(i,j) = EigenVector(i,j);
        }
    }
    SD sdRight( 2*L, N); sdRight.randomFill();

    SDSDOperation sdsdOperation(sdLeft, sdRight);

    HubbardSOCMeasureFixedSDSD hubbardSOCMeasureFixedSDSD(hubbard, sdLeft);
    hubbardSOCMeasureFixedSDSD.addMeasurement( sdsdOperation, 1.0 );
    complex<double> Henergy = hubbardSOCMeasureFixedSDSD.returnEnergy();

    double HenergyExact(0);
    for(size_t i = 0; i < N ; ++i) HenergyExact += EigenValue(i);

    EXPECT_NEAR( Henergy.real(), HenergyExact, 1e-12);
    EXPECT_NEAR( Henergy.imag(), 0.0, 1e-12);

    removeFile("*.dat");
}
