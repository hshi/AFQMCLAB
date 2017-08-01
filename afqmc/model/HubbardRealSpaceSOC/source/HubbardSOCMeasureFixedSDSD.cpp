//
// Created by Hao Shi on 8/1/17.
//

#include "../include/HubbardSOCMeasureFixedSDSD.h"
#include "../../../utilities/manipulateMCData/include/writeThreadSum.h"

using namespace std;
using namespace tensor_hao;

HubbardSOCMeasureFixedSDSD::HubbardSOCMeasureFixedSDSD()
{
    initModelWalkerNullptr();
    reSet();
}

HubbardSOCMeasureFixedSDSD::HubbardSOCMeasureFixedSDSD(const HubbardSOC &hubbardSOC_, const SD &walkerLeft_)
{
    setModelWalker(hubbardSOC_, walkerLeft_);
    reSet();
}

HubbardSOCMeasureFixedSDSD::~HubbardSOCMeasureFixedSDSD()
{

}

void HubbardSOCMeasureFixedSDSD::initModelWalkerNullptr()
{
    hubbardSOC = nullptr;
    walkerLeft = nullptr;
}

void HubbardSOCMeasureFixedSDSD::setModelWalker(const HubbardSOC &hubbardSOC_, const SD &walkerLeft_)
{
    if( 2*hubbardSOC_.getL() != walkerLeft_.getL() ) {cout<<"Model L does not consistent with walker L!"<<endl; exit(1);}
    if( hubbardSOC_.getN() != walkerLeft_.getN() ) {cout<<"Model N does not consistent with walker N!"<<endl; exit(1);}

    hubbardSOC = &hubbardSOC_;
    walkerLeft = &walkerLeft_;
    initWfDaggerK();
}
void HubbardSOCMeasureFixedSDSD::reSet()
{
    complex<double> zero(0,0);

    den = zero;
    HNum = zero;
    KNum = zero;
    VNum = zero;
    RNum = zero;
}

complex<double> HubbardSOCMeasureFixedSDSD::returnEnergy()
{
    complex<double> Htot   = MPISum(HNum);
    complex<double> denTot = MPISum(den);
    complex<double> energy;
    if( MPIRank() == 0 ) energy = Htot/denTot;
    MPIBcast(energy);
    return energy;
}

void HubbardSOCMeasureFixedSDSD::addMeasurement(SDSDOperation &sdsdOperation, complex<double> denIncrement)
{
    checkWalkerLeft(sdsdOperation);

    den += denIncrement;

    const TensorHao<complex<double>, 2> &theta_T =  sdsdOperation.returnTheta_T();

    addEnergy(theta_T, denIncrement);
}

HubbardSOCMeasureFixedSDSD::HubbardSOCMeasureFixedSDSD(const HubbardSOCMeasureFixedSDSD &x)
{
}

HubbardSOCMeasureFixedSDSD & HubbardSOCMeasureFixedSDSD::operator=(const HubbardSOCMeasureFixedSDSD &x)
{
    return *this;
}

void HubbardSOCMeasureFixedSDSD::initWfDaggerK()
{
    size_t L = walkerLeft->getL(); size_t N = walkerLeft->getN();

    wfDaggerK.resize(N, L);

    BL_NAME(gmm)(walkerLeft->getWf(), hubbardSOC->getK(), wfDaggerK, 'C');
}

void HubbardSOCMeasureFixedSDSD::checkWalkerLeft(const SDSDOperation &sdsdOperation)
{
    if( walkerLeft != sdsdOperation.getWalkerLeft() )
    {
        cout<<"Error!!! HubbardSOCMeasureFixedSDSD only accept sdsdOperation with fixed SD!"<<endl;
        exit(1);
    }
}

void HubbardSOCMeasureFixedSDSD::addEnergy(const TensorHao<complex<double>, 2> &theta_T, complex<double> denIncrement)
{
    size_t L  = (*hubbardSOC).getL(); size_t L2 = L*2;  size_t N = walkerLeft->getN();

    complex<double> Kenergy(0,0);
    for(size_t i = 0; i < L2; ++i)
    {
        for(size_t j = 0; j < N; ++j) Kenergy += wfDaggerK(j,i) * theta_T(j,i);
    }

}

