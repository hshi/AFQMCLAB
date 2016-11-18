#include <iostream>
#include "../include/fftw_hao.h"
#include "../../testHao/gtest_custom.h"

using namespace std;

TEST (FFTServer, void_construction)
{
    int dimen=1;
    vector<int> n={1};
    int L=1;
    FFTServer fft;

    EXPECT_EQ (dimen, fft.getDimen() );
    EXPECT_EQ (n, fft.getN() );
    EXPECT_EQ (L, fft.getSize() );
}


TEST (FFTServer, param_construction)
{
    int dimen=3;
    vector<int> n={2,3,6};
    int L=36;
    FFTServer fft(dimen,n,'R');

    EXPECT_EQ (dimen, fft.getDimen() );
    EXPECT_EQ (n, fft.getN() );
    EXPECT_EQ (L, fft.getSize() );
}


TEST (FFTServer, equal_construction)
{
    int dimen=3;
    vector<int> n={2,3,6};
    int L=36;
    FFTServer fft_tmp(dimen,n,'R');
    FFTServer fft(fft_tmp);

    EXPECT_EQ (dimen, fft.getDimen() );
    EXPECT_EQ (n, fft.getN() );
    EXPECT_EQ (L, fft.getSize() );
}

TEST (FFTServer, equal_assignment)
{
    int dimen=3;
    vector<int> n={2,3,6};
    int L=36;
    FFTServer fft_tmp(dimen,n, 'R');
    FFTServer fft; fft=fft_tmp;

    EXPECT_EQ (dimen, fft.getDimen() );
    EXPECT_EQ (n, fft.getN() );
    EXPECT_EQ (L, fft.getSize() );
}

TEST (FFTServer, four_1D)
{
    int dimen=1;
    vector<int> n={3};
    FFTServer fft(dimen,n, 'R');
    complex<double> a[3]={{1,2},{2,3},{3,4}};
    const complex<double>* b;
    complex<double> bforw_exact[3]={{6.,9.},{-2.366025403784438,-0.6339745962155598},{-0.6339745962155603,-2.366025403784437}};
    complex<double> bback_exact[3]={{6.,9.},{-0.6339745962155603,-2.366025403784437},{-2.366025403784438,-0.6339745962155598}};

    b=fft.fourier_forw(a);
    EXPECT_POINTER_COMPLEXDOUBLE_EQ (3, bforw_exact, b);

    b=fft.fourier_back(a);
    EXPECT_POINTER_COMPLEXDOUBLE_EQ (3, bback_exact, b);
}

TEST (FFTServer, four_2D)
{
    int dimen=2;
    vector<int> n={2,3};
    FFTServer fft(dimen,n, 'R');
    complex<double> a[6]={{1,2},{2,3},{3,4},{2,2},{1,3},{3,2}};
    const complex<double>* b;
    complex<double> bforw_exact[6]={{12.,16.},{-1.4999999999999987, 0.5980762113533187},{-1.4999999999999982,-4.598076211353313}, 
                                    {0., 2. },{-3.2320508075688763,-1.8660254037844366},{0.23205080756887897,-0.1339745962155594}};
    complex<double> bback_exact[6]={{12.,16.},{-1.4999999999999982,-4.598076211353313}, {-1.4999999999999987, 0.5980762113533187},
                                    {0., 2. },{0.23205080756887897,-0.1339745962155594},{-3.2320508075688763,-1.8660254037844366}};

    b=fft.fourier_forw(a);
    EXPECT_POINTER_COMPLEXDOUBLE_EQ (3, bforw_exact, b);

    b=fft.fourier_back(a);
    EXPECT_POINTER_COMPLEXDOUBLE_EQ (3, bback_exact, b);
}
