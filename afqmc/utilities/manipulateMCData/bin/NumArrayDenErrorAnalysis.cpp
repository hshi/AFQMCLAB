//
// Created by boruoshihao on 1/21/17.
//

#include "../../../../common/common.h"

using namespace std;
using namespace tensor_hao;

int main(int argc, char** argv)
{
    if( argc<6 )
    {
        cout<<"Error!!!!! Need input/output file name arraySize and blockSize!"<<endl;
        cout<<"Example: ./NumArrayDenErrorAnalysis num.dat den.dat out.dat arraySize blockSize skipStep(Optional, zero by default)!"<<endl;
        exit(1);
    }
    string numFilename = argv[1];
    string denFilename = argv[2];
    string outFilename = argv[3];
    int arraySize = atoi( argv[4] );
    int blockSize = atoi( argv[5] );
    int skipStep(0);
    if( argc>6 )
    {
        skipStep = atoi( argv[6] );
        cout<<"Skip first "<<skipStep<<" steps."<<endl;
    }

    int numSampleSize = getFileLineSize(numFilename) / arraySize;
    int denSampleSize = getFileLineSize(denFilename);
    int sampleSize = (numSampleSize > denSampleSize) ? denSampleSize : numSampleSize;
    sampleSize -= skipStep;
    cout<<"Effective sample points is "<<sampleSize<<endl;

    int blockNumber = sampleSize / blockSize;
    if( ( sampleSize-blockNumber*blockSize ) !=0 )
    {
        cout<<"ERROR!!!!! Effective sample size can not be devided by block size! "<<sampleSize<<" "<<blockSize<<endl;
        exit(1);
    }
    cout<<"Use reblock to calculate error bar, block number is "<<blockNumber<<endl;

    //Open files
    ifstream numFile;
    numFile.open(numFilename, ios::in);
    if ( ! numFile.is_open() ) {cout << "Error opening num file in NumArrayDenErrorAnalysis.cpp!!!"<<endl; exit(1);}
    ifstream denFile;
    denFile.open(denFilename, ios::in);
    if ( ! denFile.is_open() ) {cout << "Error opening den file in NumArrayDenErrorAnalysis.cpp!!!"<<endl; exit(1);}

    TensorHao<complex<double>, 1> numTmp(arraySize), numSum(arraySize);
    complex<double> denTmp, denSum, zero(0,0);
    TensorHao<complex<double>, 1> mean(arraySize), error(arraySize);

    //Skip
    for(int i=0; i<skipStep; i++)
    {
        readFile(numTmp.size(), numTmp.data(), numFile);
        readFile(denTmp, denFile);
    }

    //Calculate mean valule
    numSum = zero; denSum = zero;
    for(int i=0; i<sampleSize; i++)
    {
        readFile(numTmp.size(), numTmp.data(), numFile);
        readFile(denTmp, denFile);
        numSum += numTmp;
        denSum += denTmp;
    }
    mean= numSum / denSum;

    //Clear the file and calculate error bar
    if( blockNumber>1 )
    {
        numFile.clear();            denFile.clear();
        numFile.seekg(0, ios::beg); denFile.seekg(0, ios::beg);

        //Skip
        for(int i=0; i<skipStep; i++)
        {
            readFile(numTmp.size(), numTmp.data(), numFile);
            readFile(denTmp, denFile);
        }

        //Calculate Error bar
        for(int i=0; i<blockNumber; i++)
        {
            numSum = zero; denSum = zero;
            for(int j=0; j<blockSize; j++)
            {
                readFile(numTmp.size(), numTmp.data(), numFile);
                readFile(denTmp, denFile);
                numSum += numTmp;
                denSum += denTmp;
            }
            error += norm( numSum/denSum - mean );
        }
        error /= complex<double>( blockNumber*(blockNumber-1), 0.0 );
        error = sqrt(error);
    }
    else
    {
        error = zero;
    }

    //Close files
    numFile.close();
    denFile.close();

    //Write to output file
    ofstream outFile;
    outFile.open(outFilename, ios::out|ios::trunc);
    outFile<<setprecision(16)<<scientific;
    for (int i=0; i<arraySize; i++)
    {
        outFile<<setw(26)<<mean(i).real()<<setw(26)<<mean(i).imag()<<setw(26)<<error(i).real()<<"\n";
    }
    outFile.close();

    return 0;
}