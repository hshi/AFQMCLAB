#include "../include/errorAnalysis.h"
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char** argv)
{
    if( argc<3 ) {cout<<"Error!!!!! Need input/output file name! Example: ./double_error_analysis input output skipStep(Optional, zero by default)"<<endl;}
    string in_filename  = argv[1];
    string out_filename = argv[2];
    size_t skipStep(0);
    if( argc>3 )
    {
        skipStep = atoi(argv[3]);
        cout<<"Skip first "<<skipStep<<" steps."<<endl;
    }

    vector<double> vec;
    vector<size_t> fact;
    vector<double> mean, err;

    //read data to vec
    ifstream input_file;
    input_file.open(in_filename, ios::in);
    if ( ! input_file.is_open() ) {cout << "Error opening input file in double_error_analysis.cpp!!!"; exit(1);}
    double data;
    for(size_t i = 0; i < skipStep; ++i) input_file >> data;
    while (input_file >> data) vec.push_back(data);
    input_file.close();

    cout<<"Effective sample points is "<<vec.size()<<endl;

    //data analysis
    tie( fact,mean,err ) = getAllBlockMeanError(vec);

    //write data to output
    ofstream output_file;
    output_file.open(out_filename, ios::out|ios::trunc);
    if( !output_file.is_open() ) {cout << "Error opening output file in double_error_analysis.cpp!!! "<<endl; exit(1);}
    output_file<<setprecision(16)<<scientific;
    for(size_t i=0; i<fact.size(); i++) output_file<<setw(26)<<fact[i]<<setw(26)<<mean[i]<<setw(26)<<err[i]<<"\n";
    output_file.close();

    return 0;
}