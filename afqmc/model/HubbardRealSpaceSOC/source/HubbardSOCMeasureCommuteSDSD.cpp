//
// Created by boruoshihao on 1/13/17.
//

#include "../include/HubbardSOCMeasureCommuteSDSD.h"
#include "../../../utilities/manipulateMCData/include/writeThreadSum.h"

using namespace std;
using namespace tensor_hao;

HubbardSOCMeasureCommuteSDSD::HubbardSOCMeasureCommuteSDSD()
{
    initModelNullptr();
    reSet();
}

HubbardSOCMeasureCommuteSDSD::HubbardSOCMeasureCommuteSDSD(const HubbardSOC &hubbardSOC_)
{
    setModel(hubbardSOC_);
    reSet();
}

HubbardSOCMeasureCommuteSDSD::~HubbardSOCMeasureCommuteSDSD()
{

}

const HubbardSOC *HubbardSOCMeasureCommuteSDSD::getHubbardSOC() const
{
    return hubbardSOC;
}

void HubbardSOCMeasureCommuteSDSD::initModelNullptr()
{
    hubbardSOC = nullptr;
}

void HubbardSOCMeasureCommuteSDSD::setModel(const HubbardSOC &hubbardSOC_)
{
    hubbardSOC = &hubbardSOC_;
}

void HubbardSOCMeasureCommuteSDSD::reSet()
{
    complex<double> zero(0,0);
    den = zero;
    HNum = zero;
    KNum = zero;
    VNum = zero;
    RNum = zero;
}

complex<double> HubbardSOCMeasureCommuteSDSD::returnEnergy()
{
    complex<double> Htot   = MPISum(HNum);
    complex<double> denTot = MPISum(den);
    complex<double> energy;
    if( MPIRank() == 0 ) energy = Htot/denTot;
    MPIBcast(energy);
    return energy;
}

TensorHao< complex<double>, 2 >  HubbardSOCMeasureCommuteSDSD::addMeasurement(SDSDOperation &sdsdOperation, complex<double> denIncrement)
{
    den += denIncrement;

    TensorHao< complex<double>, 2 > greenMatrix = sdsdOperation.returnGreenMatrix();

    addEnergy(greenMatrix, denIncrement);

    return greenMatrix;
}

void HubbardSOCMeasureCommuteSDSD::write() const
{
    writeThreadSum(den, "den.dat", ios::app);
    writeThreadSum(HNum, "HNum.dat", ios::app);
}

void HubbardSOCMeasureCommuteSDSD::writeKNumVumRum() const
{
    writeThreadSum(KNum, "KNum.dat", ios::app);
    writeThreadSum(VNum, "VNum.dat", ios::app);
    writeThreadSum(RNum, "RNum.dat", ios::app);
}

void HubbardSOCMeasureCommuteSDSD::addEnergy(const TensorHao<complex<double>, 2> &greenMatrix, complex<double> denIncrement)
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

double HubbardSOCMeasureCommuteSDSD::getMemory() const
{
    return 8.0+16.0*5;
}

HubbardSOCMeasureCommuteSDSD::HubbardSOCMeasureCommuteSDSD(const HubbardSOCMeasureCommuteSDSD &x)
{

}

HubbardSOCMeasureCommuteSDSD &HubbardSOCMeasureCommuteSDSD::operator=(const HubbardSOCMeasureCommuteSDSD &x)
{
    return *this;
}