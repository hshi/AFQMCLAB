//
// Created by boruoshihao on 1/13/17.
//

#include "../include/HubbardSOCSDSDMeasure.h"
#include "../../../utilities/manipulateMCData/include/writeThreadSum.h"

using namespace std;
using namespace tensor_hao;

HubbardSOCSDSDMeasure::HubbardSOCSDSDMeasure()
{
    hubbardSOC = nullptr;
    reSet();
}

HubbardSOCSDSDMeasure::HubbardSOCSDSDMeasure(const HubbardSOC &hubbardSOC_)
{
    setModel(hubbardSOC_);
    reSet();
}

HubbardSOCSDSDMeasure::~HubbardSOCSDSDMeasure()
{

}

void HubbardSOCSDSDMeasure::setModel(const HubbardSOC &hubbardSOC_)
{
    hubbardSOC = &hubbardSOC_;
}

void HubbardSOCSDSDMeasure::reSet()
{
    complex<double> zero(0,0);
    den = zero;
    HNum = zero;
    KNum = zero;
    VNum = zero;
    RNum = zero;
    greenMatrixNum = zero;
    densityDensityNum = zero;
    splusSminusNum = zero;
    sminusSplusNum = zero;
    spairSpairNum = zero;
}

void HubbardSOCSDSDMeasure::addMeasurement(SDSDOperation &sdsdOperation, complex<double> denIncrement)
{
    den += denIncrement;

    TensorHao< complex<double>, 2 > greenMatrix = sdsdOperation.returnGreenMatrix();

    addEnergy(greenMatrix, denIncrement);
    addGreenMatrix(greenMatrix, denIncrement);
    addDensityDensity(greenMatrix, denIncrement);
    addSplusSminus(greenMatrix, denIncrement);
    addSminusSplus(greenMatrix, denIncrement);
    addSpairSpair(greenMatrix, denIncrement);
}

void HubbardSOCSDSDMeasure::write()
{
    writeThreadSum(den, "den.dat", ios::app);
    writeThreadSum(HNum, "HNum.dat", ios::app);
    writeThreadSum(KNum, "KNum.dat", ios::app);
    writeThreadSum(VNum, "VNum.dat", ios::app);
    writeThreadSum(RNum, "RNum.dat", ios::app);
    writeThreadSum(greenMatrixNum.size(), greenMatrixNum.data(), "greenMatrixNum.dat", ios::app);
    writeThreadSum(densityDensityNum.size(), densityDensityNum.data(), "densityDensityNum.dat", ios::app);
    writeThreadSum(splusSminusNum.size(), splusSminusNum.data(), "splusSminusNum.dat", ios::app);
    writeThreadSum(sminusSplusNum.size(), sminusSplusNum.data(), "sminusSplusNum.dat", ios::app);
    writeThreadSum(spairSpairNum.size(), spairSpairNum.data(), "spairSpairNum.dat", ios::app);
}

void HubbardSOCSDSDMeasure::addEnergy(const TensorHao<complex<double>, 2> &greenMatrix, complex<double> denIncrement)
{
    complex<double> Kenergy(0,0), Venergy(0,0), Renergy(0,0);

    size_t L  = (*hubbardSOC).getL(); size_t L2 = L*2;

    //Add K
    const TensorHao< complex<double>, 2 > &K = (*hubbardSOC).getK();
    for(size_t i = 0; i < L2; ++i)
    {
        for(size_t j = 0; j < L2; ++j)
        {
            Kenergy += K(j,i) * greenMatrix(j,i);
        }
    }

    //Add U
    const TensorHao< double, 1> &U = (*hubbardSOC).getU();
    for(size_t i = 0; i < L; ++i)
    {
        Venergy += U(i) * ( greenMatrix(i,i)*greenMatrix(i+L,i+L) - greenMatrix(i, i+L)*greenMatrix(i+L, i) );
    }

    //Add mu and pinning field
    const TensorHao< double, 1> &mu = (*hubbardSOC).getMu();
    const TensorHao< double, 1> &hx = (*hubbardSOC).getHx();
    const TensorHao< double, 1> &hy = (*hubbardSOC).getHy();
    const TensorHao< double, 1> &hz = (*hubbardSOC).getHz();
    for(size_t i = 0; i < L; ++i)
    {
        Renergy += ( -mu(i) + hz(i)*0.5 ) * greenMatrix(i,i);
        Renergy += ( -mu(i) - hz(i)*0.5 ) * greenMatrix(i+L,i+L);
        Renergy += complex<double>( hx(i)*0.5, -hy(i)*0.5 ) * greenMatrix(i, i+L);
        Renergy += complex<double>( hx(i)*0.5,  hy(i)*0.5 ) * greenMatrix(i+L, i);
    }

    HNum += ( ( Kenergy + Venergy + Renergy ) * denIncrement );
    KNum += ( Kenergy * denIncrement );
    VNum += ( Venergy * denIncrement );
    RNum += ( Renergy * denIncrement );
}

void HubbardSOCSDSDMeasure::addGreenMatrix(const TensorHao<complex<double>, 2> &greenMatrix, complex<double> denIncrement)
{
    size_t L2  = (*hubbardSOC).getL() * 2;
    if( greenMatrixNum.rank(0) != L2 ) greenMatrixNum.resize(L2, L2);

    greenMatrixNum += ( greenMatrix * denIncrement );
}

void HubbardSOCSDSDMeasure::addDensityDensity(const TensorHao<complex<double>, 2> &greenMatrix, complex<double> denIncrement)
{
    size_t L2  = (*hubbardSOC).getL() * 2;
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

void HubbardSOCSDSDMeasure::addSplusSminus(const TensorHao<complex<double>, 2> &greenMatrix, complex<double> denIncrement)
{
    size_t L   = (*hubbardSOC).getL();
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

void HubbardSOCSDSDMeasure::addSminusSplus(const TensorHao<complex<double>, 2> &greenMatrix, complex<double> denIncrement)
{
    size_t L   = (*hubbardSOC).getL();
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

void HubbardSOCSDSDMeasure::addSpairSpair(const TensorHao<complex<double>, 2> &greenMatrix, complex<double> denIncrement)
{
    size_t L   = (*hubbardSOC).getL();
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

HubbardSOCSDSDMeasure::HubbardSOCSDSDMeasure(const HubbardSOCSDSDMeasure &x)
{

}

HubbardSOCSDSDMeasure &HubbardSOCSDSDMeasure::operator=(const HubbardSOCSDSDMeasure &x)
{
    return *this;
}