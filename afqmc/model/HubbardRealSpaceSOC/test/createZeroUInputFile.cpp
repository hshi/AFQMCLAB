//
// Created by Hao Shi on 8/2/17.
//

#include "../include/HubbardSOC.h"

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
