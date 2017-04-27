//
// Created by boruoshihao on 1/21/17.
//

#include "../../../../common/common.h"

using namespace std;
using namespace tensor_hao;

int main(int argc, char** argv)
{
    if( argc<4 ) { cout<<"Error!!!!! Need input/output file name, example: ./NumDenErrorAnalysis num.dat den.dat "
            "out.dat skipStep(Optional, zero by default)!"<<endl; exit(1); }
    string numFilename = argv[1];
    string denFilename = argv[2];
    string outFilename = argv[3];
    size_t skipStep(0);
    if( argc>4 )
    {
        skipStep = atoi(argv[4]);
        cout<<"Skip first "<<skipStep<<" steps."<<endl;
    }

    int numSampleSize = getFileLineSize(numFilename);
    int denSampleSize = getFileLineSize(denFilename);
    int sampleSize = (numSampleSize > denSampleSize) ? denSampleSize : numSampleSize;
    sampleSize -= skipStep;
    cout<<"Effective sample points is "<<sampleSize<<endl;

    //Read num and den data
    TensorHao<complex<double>, 1> num(sampleSize), den(sampleSize);
    readFile(num.size(), num.data(), numFilename, skipStep);
    readFile(den.size(), den.data(), denFilename, skipStep);

    //Get all factors of sampleSize
    vector<size_t> fact = getDivisors(sampleSize);

    //Open outFile
    ofstream outFile;
    outFile.open(outFilename, ios::out|ios::trunc);
    outFile<<setprecision(16)<<scientific;

    //Calculate mean and error bar
    TensorHao<complex<double>, 1> array(sampleSize);
    complex<double> mean, error;
    complex<double> numTmp, denTmp;
    complex<double> zero(0,0);
    for (int blockSize : fact)
    {
        int blockNumber = sampleSize / blockSize;

        for(int i=0; i<blockNumber; i++)
        {
            numTmp = zero;
            denTmp = zero;
            for(int j=0; j<blockSize; j++)
            {
                numTmp += num(j+i*blockSize);
                denTmp += den(j+i*blockSize);
            }
            array(i) = numTmp/denTmp;
        }
        tie(mean, error) = getMeanError( blockNumber, array.data() );
        outFile<<setw(26)<<blockSize<<setw(26)<<mean.real()<<setw(26)<<mean.imag()<<setw(26)<<error.real()<<"\n";
    }

    //Close file
    outFile.close();

    return 0;
}