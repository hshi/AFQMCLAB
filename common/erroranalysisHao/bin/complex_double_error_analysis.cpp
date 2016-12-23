#include "../include/errorAnalysis.h"
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char** argv)
{
    if( argc<3 ) {cout<<"Error!!!!! Need input/output file name! Example: ./complex_double_error_analysis input output"<<endl;}
    string in_filename  = argv[1];
    string out_filename = argv[2];

    vector<complex<double>> vec;
    vector<size_t> fact;
    vector<complex<double>> mean, err;

    //read data to vec
    ifstream input_file;
    input_file.open(in_filename, ios::in);
    if ( ! input_file.is_open() ) {cout << "Error opening input file in complex_double_error_analysis.cpp!!!"; exit(1);}
    double re, im;
    while (input_file >> re >> im) vec.push_back( complex<double>(re, im) );
    input_file.close();

    //data analysis
    tie( fact,mean,err ) = getAllBlockMeanError(vec);

    //write data to output
    ofstream output_file;
    output_file.open(out_filename, ios::out|ios::trunc);
    if( !output_file.is_open() ) {cout << "Error opening output file in complex_double_error_analysis.cpp!!! "<<endl; exit(1);}
    output_file<<setprecision(16)<<scientific;
    for(size_t i=0; i<fact.size(); i++) output_file<<setw(26)<<fact[i]
                                                   <<setw(26)<<mean[i].real()<<setw(26)<<mean[i].imag()
                                                   <<setw(26)<<err[i].real()<<"\n";
    output_file.close();

    return 0;
}
