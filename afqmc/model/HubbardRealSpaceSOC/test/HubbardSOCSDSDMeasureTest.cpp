//
// Created by boruoshihao on 1/13/17.
//

#include "../include/HubbardSOCSDSDMeasure.h"
#include "../../../../common/testHao/gtest_custom.h"
#include "../../../../common/readWriteHao/include/readWriteHao.h"

using namespace std;
using namespace tensor_hao;

void createZeroUInputFile(const string &filename)
{
    size_t L(10), N(5);
    TensorHao< complex<double>, 2 > K(2*L,2*L);
    TensorHao< double, 1> mu(L), hx(L), hy(L), hz(L), U(L);
    randomFill(K);  K+=conjtrans(K);
    randomFill(mu); randomFill(hx);
    randomFill(hy); randomFill(hz);
    U = 0.0;

    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    file<<setprecision(16)<<scientific;
    writeFile(L,file);
    writeFile(N,file);
    writeFile( 4*L*L, K.data(), file );
    writeFile( L, mu.data(), file );
    writeFile( L, hx.data(), file );
    writeFile( L, hy.data(), file );
    writeFile( L, hz.data(), file );
    writeFile( L, U.data(), file );
    file.close();
}


TEST(HubbardSOCSDSDMeasureTest, energy)
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

    HubbardSOCSDSDMeasure hubbardSOCSDSDMeasure(hubbard);
    hubbardSOCSDSDMeasure.addMeasurement( sdsdOperation, 1.0 );
    hubbardSOCSDSDMeasure.write();

    double HenergyExact(0);
    for(size_t i = 0; i < N ; ++i) HenergyExact += EigenValue(i);

    complex<double> den, HNum;
    MPIBarrier();
    readFile( den, "den.dat");
    readFile( HNum, "HNum.dat");
    complex<double> Henergy = HNum/den;

    EXPECT_NEAR( Henergy.real(), HenergyExact, 1e-12);
    EXPECT_NEAR( Henergy.imag(), 0.0, 1e-12);

    removeFile("*.dat");
}