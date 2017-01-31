//
// Created by boruoshihao on 1/22/17.
//

#include "../../../../common/common.h"

using namespace std;
using namespace tensor_hao;

void writeSzSzNtotNtotSpinSpin(const TensorHao<complex<double>, 2> &densityDensityNum,
                               const TensorHao<complex<double>, 2> &splusSminusNum,
                               const TensorHao<complex<double>, 2> &sminusSplusNum)
{
    size_t L = densityDensityNum.rank(0) / 2;

    TensorHao<complex<double>, 2> SzSzNum(L,L), NTotNTotNum(L,L), spinSpinNum(L,L);

    for(size_t j=0; j<L; j++)
    {
        for(size_t i=0; i<L; i++)
        {
            SzSzNum(i,j) = ( densityDensityNum(i,j) + densityDensityNum(i+L,j+L) - densityDensityNum(i+L,j) - densityDensityNum(i,j+L) ) * 0.25;
            NTotNTotNum(i,j)  = densityDensityNum(i,j) + densityDensityNum(i+L,j+L) + densityDensityNum(i+L,j) + densityDensityNum(i,j+L);
            spinSpinNum(i,j) = SzSzNum(i,j) + ( splusSminusNum(i,j) + sminusSplusNum(i,j) ) * 0.5;
        }
    }

    writeFile(SzSzNum.size(), SzSzNum.data(), "SzSzNum.dat", ios::app);
    writeFile(NTotNTotNum.size(), NTotNTotNum.data(), "NTotNTotNum.dat", ios::app);
    writeFile(spinSpinNum.size(), spinSpinNum.data(), "spinSpinNum.dat", ios::app);
}

void writeSxSySplusSminus(const TensorHao<complex<double>, 2> &greenMatrixNum)
{
    size_t L = greenMatrixNum.rank(0) / 2;

    TensorHao<complex<double>, 1> SxNum(L), SyNum(L), SplusNum(L), SminusNum(L);

    for(size_t i=0; i<L; i++)
    {
        SplusNum(i)  = greenMatrixNum(i,   i+L );
        SminusNum(i) = greenMatrixNum(i+L, i   );
        SxNum(i)  =  ( greenMatrixNum(i,   i+L ) + greenMatrixNum(i+L, i   ) ) * 0.5;
        SyNum(i)   = ( greenMatrixNum(i,   i+L ) - greenMatrixNum(i+L, i   ) ) * 0.5 * complex<double>(0,-1);
    }

    writeFile(L, SplusNum.data(), "SplusNum.dat", ios::app);
    writeFile(L, SminusNum.data(), "SminusNum.dat", ios::app);
    writeFile(L, SxNum.data(), "SxNum.dat", ios::app);
    writeFile(L, SyNum.data(), "SyNum.dat", ios::app);

    writeFile(SplusNum.sum(), "SplusTotNum.dat", ios::app);
    writeFile(SminusNum.sum(), "SminusTotNum.dat", ios::app);
    writeFile(SxNum.sum(), "SxTotNum.dat", ios::app);
    writeFile(SyNum.sum(), "SyTotNum.dat", ios::app);
}

void writeSzNNupNdn(const TensorHao<complex<double>, 2> &greenMatrixNum)
{
    size_t L = greenMatrixNum.rank(0) / 2;

    TensorHao<complex<double>, 1> SzNum(L), NNum(L), NupNum(L), NdnNum(L);

    for(size_t i = 0; i < L; ++i)
    {
        NupNum(i) = greenMatrixNum(i,   i  );
        NdnNum(i) = greenMatrixNum(i+L, i+L);
        SzNum(i)  = ( greenMatrixNum(i,   i  ) - greenMatrixNum(i+L, i+L) ) * 0.5;
        NNum(i)   = ( greenMatrixNum(i,   i  ) + greenMatrixNum(i+L, i+L) );
    }

    writeFile(L, NupNum.data(), "NupNum.dat", ios::app);
    writeFile(L, NdnNum.data(), "NdnNum.dat", ios::app);
    writeFile(L, SzNum.data(), "SzNum.dat", ios::app);
    writeFile(L, NNum.data(), "NNum.dat", ios::app);

    writeFile(NupNum.sum(), "NupTotNum.dat", ios::app);
    writeFile(NdnNum.sum(), "NdnTotNum.dat", ios::app);
    writeFile(SzNum.sum(), "SzTotNum.dat", ios::app);
    writeFile(NNum.sum(), "NTotNum.dat", ios::app);
}

void generateDensitySpinCorrelation(size_t L)
{
    TensorHao<complex<double>, 2> densityDensityNum(2*L, 2*L);
    TensorHao<complex<double>, 2> splusSminusNum(L, L);
    TensorHao<complex<double>, 2> sminusSplusNum(L, L);

    size_t densityDensitySize = getFileLineSize("densityDensityNum.dat") / (4*L*L);
    size_t splusSminusSize = getFileLineSize("splusSminusNum.dat") / (L*L);
    size_t sminusSplusSize = getFileLineSize("sminusSplusNum.dat") / (L*L);
    size_t sampleSize = min( densityDensitySize, min( splusSminusSize, sminusSplusSize ) );
    cout<<"Effective sample points is "<<sampleSize<<endl;

    removeFile("SzSzNum.dat"); removeFile("NTotNTotNum.dat"); removeFile("spinSpinNum.dat");

    ifstream densityDensityFile, splusSminusFile, sminusSplusFile;
    densityDensityFile.open("densityDensityNum.dat", ios::in);
    splusSminusFile.open("splusSminusNum.dat", ios::in);
    sminusSplusFile.open("sminusSplusNum.dat", ios::in);

    if ( ! densityDensityFile.is_open() ) {cout << "Error opening file in dataManipulateHubbardSOC.cpp!!!"<<endl; exit(1);}
    if ( ! splusSminusFile.is_open() ) {cout << "Error opening file in dataManipulateHubbardSOC.cpp!!!"<<endl; exit(1);}
    if ( ! sminusSplusFile.is_open() ) {cout << "Error opening file in dataManipulateHubbardSOC.cpp!!!"<<endl; exit(1);}

    for(size_t i=0; i<sampleSize; i++)
    {
        readFile(densityDensityNum.size(), densityDensityNum.data(), densityDensityFile);
        readFile(splusSminusNum.size(), splusSminusNum.data(), splusSminusFile);
        readFile(sminusSplusNum.size(), sminusSplusNum.data(), sminusSplusFile);
        writeSzSzNtotNtotSpinSpin(densityDensityNum, splusSminusNum, sminusSplusNum);
    }

    densityDensityFile.close();
    splusSminusFile.close();
    sminusSplusFile.close();
}

void generateOneBody(size_t L)
{
    TensorHao<complex<double>, 2> greenMatrixNum(2*L, 2*L);
    size_t sampleSize = getFileLineSize("greenMatrixNum.dat") / (4*L*L);

    removeFile("SzNum.dat"); removeFile("NNum.dat"); removeFile("NupNum.dat"); removeFile("NdnNum.dat");
    removeFile("SzTotNum.dat"); removeFile("NTotNum.dat"); removeFile("NupTotNum.dat"); removeFile("NdnTotNum.dat");
    removeFile("SxNum.dat"); removeFile("SyNum.dat"); removeFile("SplusNum.dat"); removeFile("SminusNum.dat");
    removeFile("SxTotNum.dat"); removeFile("SyTotNum.dat"); removeFile("SplusTotNum.dat"); removeFile("SminusTotNum.dat");

    ifstream file;
    file.open("greenMatrixNum.dat", ios::in);
    if ( ! file.is_open() ) {cout << "Error opening greenMatrix file in dataManipulateHubbardSOC.cpp!!!"<<endl; exit(1);}
    for(size_t i=0; i<sampleSize; i++)
    {
        readFile(greenMatrixNum.size(), greenMatrixNum.data(), file);
        writeSzNNupNdn(greenMatrixNum);
        writeSxSySplusSminus(greenMatrixNum);
    }
    file.close();
}

int main(int argc, char** argv)
{
    MPIInit(argc,argv);

    if( argc<2 )
    {
        cout<<"Error!!! Need input file name, example: ./generateNumeratorHubbardSOC model_param !"<<endl;
        exit(1);
    }
    string modelFilename = argv[1];

    size_t L;
    readFile(L, modelFilename);

    generateOneBody(L);
    generateDensitySpinCorrelation(L);

    MPIFinalize();
    return 0;
}