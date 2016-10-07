#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include "../include/tensor_all.h"

using namespace std;
using namespace tensor_hao;

int main()
{
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
    eigen_cpu(hermitM, W);

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

    return 0;
}

