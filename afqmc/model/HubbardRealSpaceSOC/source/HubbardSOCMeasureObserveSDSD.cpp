//
// Created by boruoshihao on 1/13/17.
//

#include "../include/HubbardSOCMeasureObserveSDSD.h"
#include "../../../utilities/manipulateMCData/include/writeThreadSum.h"

using namespace std;
using namespace tensor_hao;

HubbardSOCMeasureObserveSDSD::HubbardSOCMeasureObserveSDSD()
{
    initModelNullptr();
    reSet();
}

HubbardSOCMeasureObserveSDSD::HubbardSOCMeasureObserveSDSD(const HubbardSOC &hubbardSOC_)
{
    setModel( hubbardSOC_ );
    reSet();
}

HubbardSOCMeasureObserveSDSD::~HubbardSOCMeasureObserveSDSD()
{

}

void HubbardSOCMeasureObserveSDSD::reSet()
{
    HubbardSOCMeasureCommuteSDSD::reSet();

    complex<double> zero(0,0);
    greenMatrixNum = zero;
    densityDensityNum = zero;
    splusSminusNum = zero;
    sminusSplusNum = zero;
    spairSpairNum = zero;
}

void HubbardSOCMeasureObserveSDSD::addMeasurement(SDSDOperation &sdsdOperation, complex<double> denIncrement)
{
    HubbardSOCMeasureCommuteSDSD::addMeasurement(sdsdOperation, denIncrement);

    addGreenMatrix(sdsdOperation, denIncrement);
    addDensityDensity(sdsdOperation, denIncrement);
    addSplusSminus(sdsdOperation, denIncrement);
    addSminusSplus(sdsdOperation, denIncrement);
    addSpairSpair(sdsdOperation, denIncrement);
}

void HubbardSOCMeasureObserveSDSD::write() const
{
    HubbardSOCMeasureCommuteSDSD::write();
    writeKNumVumRum();
    writeThreadSum(greenMatrixNum.size(), greenMatrixNum.data(), "greenMatrixNum.dat", ios::app);
    writeThreadSum(densityDensityNum.size(), densityDensityNum.data(), "densityDensityNum.dat", ios::app);
    writeThreadSum(splusSminusNum.size(), splusSminusNum.data(), "splusSminusNum.dat", ios::app);
    writeThreadSum(sminusSplusNum.size(), sminusSplusNum.data(), "sminusSplusNum.dat", ios::app);
    writeThreadSum(spairSpairNum.size(), spairSpairNum.data(), "spairSpairNum.dat", ios::app);
}

double HubbardSOCMeasureObserveSDSD::getMemory() const
{
    double mem(0.0);
    mem += HubbardSOCMeasureCommuteSDSD::getMemory();
    mem += greenMatrixNum.getMemory();
    mem += densityDensityNum.getMemory();
    mem += splusSminusNum.getMemory();
    mem += sminusSplusNum.getMemory();
    mem += spairSpairNum.getMemory();

    return mem;
}

void HubbardSOCMeasureObserveSDSD::addGreenMatrix(SDSDOperation &sdsdOperation, complex<double> denIncrement)
{
    const TensorHao< complex<double>, 2 > &greenMatrix = sdsdOperation.returnGreenMatrix();

    size_t L2 = getHubbardSOC()->getL() * 2;

    if( greenMatrixNum.rank(0) != L2 ) { greenMatrixNum.resize(L2, L2); greenMatrixNum = complex<double>(0,0); }

    greenMatrixNum += ( greenMatrix * denIncrement );
}

void HubbardSOCMeasureObserveSDSD::addDensityDensity(SDSDOperation &sdsdOperation, complex<double> denIncrement)
{
    const TensorHao< complex<double>, 2 > &greenMatrix = sdsdOperation.returnGreenMatrix();

    size_t L2 = getHubbardSOC()->getL() * 2;

    if( densityDensityNum.rank(0) != L2 ) { densityDensityNum.resize(L2, L2); densityDensityNum = complex<double>(0,0); }

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

void HubbardSOCMeasureObserveSDSD::addSplusSminus(SDSDOperation &sdsdOperation, complex<double> denIncrement)
{
    const TensorHao< complex<double>, 2 > &greenMatrix = sdsdOperation.returnGreenMatrix();

    size_t L = getHubbardSOC()->getL();

    if( splusSminusNum.rank(0) != L ) { splusSminusNum.resize(L, L); splusSminusNum = complex<double>(0,0); }

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

void HubbardSOCMeasureObserveSDSD::addSminusSplus(SDSDOperation &sdsdOperation, complex<double> denIncrement)
{
    const TensorHao< complex<double>, 2 > &greenMatrix = sdsdOperation.returnGreenMatrix();

    size_t L = getHubbardSOC()->getL();

    if( sminusSplusNum.rank(0) != L ) { sminusSplusNum.resize(L, L); sminusSplusNum = complex<double>(0,0); }

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

void HubbardSOCMeasureObserveSDSD::addSpairSpair(SDSDOperation &sdsdOperation, complex<double> denIncrement)
{
    const TensorHao< complex<double>, 2 > &greenMatrix = sdsdOperation.returnGreenMatrix();

    size_t L = getHubbardSOC()->getL();

    if( spairSpairNum.rank(0) != L ) { spairSpairNum.resize(L, L); spairSpairNum = complex<double>(0,0); }

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

HubbardSOCMeasureObserveSDSD::HubbardSOCMeasureObserveSDSD(const HubbardSOCMeasureObserveSDSD &x)
{

}

HubbardSOCMeasureObserveSDSD &HubbardSOCMeasureObserveSDSD::operator=(const HubbardSOCMeasureObserveSDSD &x)
{
    return *this;
}