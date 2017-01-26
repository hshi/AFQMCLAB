//
// Created by boruoshihao on 1/13/17.
//

#include "../include/HubbardSOCSDSDMeasureObserve.h"
#include "../../../utilities/manipulateMCData/include/writeThreadSum.h"

using namespace std;
using namespace tensor_hao;

HubbardSOCSDSDMeasureObserve::HubbardSOCSDSDMeasureObserve()
{
    initModelNullptr();
    reSet();
}

HubbardSOCSDSDMeasureObserve::HubbardSOCSDSDMeasureObserve(const HubbardSOC &hubbardSOC_)
{
    setModel( hubbardSOC_ );
    reSet();
}

HubbardSOCSDSDMeasureObserve::~HubbardSOCSDSDMeasureObserve()
{

}

void HubbardSOCSDSDMeasureObserve::reSet()
{
    HubbardSOCSDSDMeasureCommute::reSet();

    complex<double> zero(0,0);
    greenMatrixNum = zero;
    densityDensityNum = zero;
    splusSminusNum = zero;
    sminusSplusNum = zero;
    spairSpairNum = zero;
}

TensorHao< complex<double>, 2 > HubbardSOCSDSDMeasureObserve::addMeasurement(SDSDOperation &sdsdOperation, complex<double> denIncrement)
{
    TensorHao< complex<double>, 2 > greenMatrix = HubbardSOCSDSDMeasureCommute::addMeasurement(sdsdOperation, denIncrement);

    addGreenMatrix(greenMatrix, denIncrement);
    addDensityDensity(greenMatrix, denIncrement);
    addSplusSminus(greenMatrix, denIncrement);
    addSminusSplus(greenMatrix, denIncrement);
    addSpairSpair(greenMatrix, denIncrement);

    return greenMatrix;
}

void HubbardSOCSDSDMeasureObserve::write()
{
    HubbardSOCSDSDMeasureCommute::write();
    writeKNumVumRum();
    writeThreadSum(greenMatrixNum.size(), greenMatrixNum.data(), "greenMatrixNum.dat", ios::app);
    writeThreadSum(densityDensityNum.size(), densityDensityNum.data(), "densityDensityNum.dat", ios::app);
    writeThreadSum(splusSminusNum.size(), splusSminusNum.data(), "splusSminusNum.dat", ios::app);
    writeThreadSum(sminusSplusNum.size(), sminusSplusNum.data(), "sminusSplusNum.dat", ios::app);
    writeThreadSum(spairSpairNum.size(), spairSpairNum.data(), "spairSpairNum.dat", ios::app);
}

void HubbardSOCSDSDMeasureObserve::addGreenMatrix(const TensorHao<complex<double>, 2> &greenMatrix, complex<double> denIncrement)
{
    size_t L2  = ( *getHubbardSOC() ).getL() * 2;
    if( greenMatrixNum.rank(0) != L2 ) greenMatrixNum.resize(L2, L2);

    greenMatrixNum += ( greenMatrix * denIncrement );
}

void HubbardSOCSDSDMeasureObserve::addDensityDensity(const TensorHao<complex<double>, 2> &greenMatrix, complex<double> denIncrement)
{
    size_t L2  = ( *getHubbardSOC() ).getL() * 2;
    if( densityDensityNum.rank(0) != L2 ) densityDensityNum.resize(L2, L2);

    complex<double> temp;
    for(size_t j = 0; j < L2; ++j)
    {
        for(size_t i = 0; i < L2; ++i)
        {
            if( i==j ) temp = greenMatrix(i,i);
            else temp = greenMatrix(i,i) * greenMatrix(j,j) - greenMatrix(i,j)*greenMatrix(j,i);
            densityDensityNum(i, j) += ( temp * denIncrement );
        }
    }
}

void HubbardSOCSDSDMeasureObserve::addSplusSminus(const TensorHao<complex<double>, 2> &greenMatrix, complex<double> denIncrement)
{
    size_t L   = ( *getHubbardSOC() ).getL();
    if( splusSminusNum.rank(0) != L ) splusSminusNum.resize(L, L);

    complex<double> temp;
    for(size_t j = 0; j < L; ++j)
    {
        for(size_t i = 0; i < L; ++i)
        {
            if( i==j )
            {
                temp  = greenMatrix(i,i);
                temp -= ( greenMatrix(i,i)*greenMatrix(i+L,i+L)-greenMatrix(i,i+L)*greenMatrix(i+L,i) );
            }
            else
            {
                temp = -greenMatrix(i,j)*greenMatrix(j+L,i+L)+greenMatrix(i,i+L)*greenMatrix(j+L, j);
            }
            splusSminusNum(i,j) += ( temp * denIncrement );
        }
    }
}

void HubbardSOCSDSDMeasureObserve::addSminusSplus(const TensorHao<complex<double>, 2> &greenMatrix, complex<double> denIncrement)
{
    size_t L   = ( *getHubbardSOC() ).getL();
    if( sminusSplusNum.rank(0) != L ) sminusSplusNum.resize(L, L);

    complex<double> temp;
    for(size_t j = 0; j < L; ++j)
    {
        for(size_t i = 0; i < L; ++i)
        {
            if( i==j )
            {
                temp  = greenMatrix(i+L, i+L);
                temp -= ( greenMatrix(i,i)*greenMatrix(i+L,i+L)-greenMatrix(i,i+L)*greenMatrix(i+L,i) );
            }
            else
            {
                temp = -greenMatrix(i+L,j+L)*greenMatrix(j,i)+greenMatrix(i+L,i)*greenMatrix(j, j+L);
            }
            sminusSplusNum(i,j) += ( temp * denIncrement );
        }
    }
}

void HubbardSOCSDSDMeasureObserve::addSpairSpair(const TensorHao<complex<double>, 2> &greenMatrix, complex<double> denIncrement)
{
    size_t L   = ( *getHubbardSOC() ).getL();
    if( spairSpairNum.rank(0) != L ) spairSpairNum.resize(L, L);

    complex<double> temp;
    for(size_t j=0; j<L; j++)
    {
        for(size_t i=0; i<L; i++)
        {
            temp = greenMatrix(i,j)*greenMatrix(i+L,j+L)-greenMatrix(i,j+L)*greenMatrix(i+L,j);
            spairSpairNum(i,j) += ( temp * denIncrement );
        }
    }
}

HubbardSOCSDSDMeasureObserve::HubbardSOCSDSDMeasureObserve(const HubbardSOCSDSDMeasureObserve &x)
{

}

HubbardSOCSDSDMeasureObserve &HubbardSOCSDSDMeasureObserve::operator=(const HubbardSOCSDSDMeasureObserve &x)
{
    return *this;
}