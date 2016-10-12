#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include "../include/tensor_all.h"

#ifdef USE_MAGMA
#include "magma.h"
#endif


using namespace std;
using namespace tensor_hao;

int main()
{
    #ifndef USE_MAGMA
    cout<<"ERROR!!! USE_MAGMA IS NOT DEFINED!"<<endl;
    exit(1);
    #endif

    #ifdef USE_MAGMA
    magma_init();
    #endif

    //read data to vec
    vector<complex<double>> vec;
    double re,im;
    while (cin >> re >> im) vec.push_back( complex<double>(re,im) );

    //check the square
    size_t L_square=vec.size();
    size_t L=sqrt(L_square);
    if(L*L!=L_square) {cout<<"The matrix is not square! "<<L_square<<" "<<L<<endl; exit(1);}

    //Point to the vector, write the trace
    TensorHaoRef<complex<double>,2> hermitM(L,L); hermitM.point(vec);
    checkHermitian(hermitM);
    cout<<setprecision(16);
    complex<double> TR(0,0); for(size_t i=0; i<L; i++) TR+=hermitM(i,i); cout<<"Trace matrix is: "<<TR<<endl;

    //Diagonal matrix
    TensorHao<double,1> W(L);
    #ifdef USE_MAGMA
    eigen_magma(hermitM, W);
    #endif

    //Write to file
    ofstream file;

    file.open("eigenvalues.dat", ios::out|ios::trunc);
    file<<setprecision(16)<<scientific;
    for(size_t i=0; i<L; i++) file<<setw(26)<<W(i)<<"\n";
    file.close();

    file.open("eigenvectors.dat", ios::out|ios::trunc);
    file<<setprecision(16)<<scientific;
    for(size_t i=0; i<L_square; i++) file<<setw(26)<<vec[i].real()
                                      <<setw(26)<<vec[i].imag()<<"\n";
    file.close();

    #ifdef USE_MAGMA
    magma_finalize();
    #endif

    return 0;
}
