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
    KNum = zero; VNum = zero; RNum = zero; HNum = zero;
    NupNum = zero; NdnNum = zero; SplusNum = zero; SminusNum = zero;
    NupTotNum = zero; NdnTotNum = zero; SplusTotNum = zero; SminusTotNum = zero;
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

    addEnergy(sdsdOperation, denIncrement);
    addNupNdn(sdsdOperation, denIncrement);
    addSplusSminus(sdsdOperation, denIncrement);
}

NiupNidnForce HubbardSOCMeasureFixedSDSD::getForce(const NiupNidn &niupNidn, SDSDOperation &sdsdOperation, double cap)
{
    checkWalkerLeft(sdsdOperation);

    size_t halfL = niupNidn.getL(); const string &decompType = niupNidn.getDecompType();

    TensorHao< complex<double>, 1 > backGround(halfL);
    if( decompType == "densityCharge" )
    {
        const TensorHao< complex<double>, 1 > &greenDiagonal = sdsdOperation.returnGreenDiagonal();
        for(size_t i = 0; i < halfL; ++i) backGround(i) = greenDiagonal(i) + greenDiagonal(i+halfL) -1.0;
    }
    else if( decompType == "densitySpin" )
    {
        const TensorHao< complex<double>, 1 > &greenDiagonal = sdsdOperation.returnGreenDiagonal();
        for(size_t i = 0; i < halfL; ++i) backGround(i) = greenDiagonal(i) - greenDiagonal(i+halfL);
    }
    else if( decompType == "hopCharge" )
    {
        const TensorHao< complex<double>, 1 > &greenOffDiagonal = sdsdOperation.returnGreenOffDiagonal();
        for(size_t i = 0; i < halfL; ++i) backGround(i) = greenOffDiagonal(i) + greenOffDiagonal(i+halfL);
    }
    else if( decompType == "hopSpin" )
    {
        const TensorHao< complex<double>, 1 > &greenOffDiagonal = sdsdOperation.returnGreenOffDiagonal();
        for(size_t i = 0; i < halfL; ++i) backGround(i) = greenOffDiagonal(i) - greenOffDiagonal(i+halfL);
    }
    else
    {
        cout<<"Error! Can not find the matched decompType! "<<decompType<<endl;
        exit(1);
    }

    NiupNidnForce force(halfL);
    const TensorHao<complex<double>, 1> &gamma = niupNidn.getGamma();
    for (size_t i = 0; i < halfL; ++i)
    {
        force(i) = ( gamma(i) * backGround(i) ).real();
        if( force(i) >  cap ) force(i) =  cap;
        if( force(i) < -cap ) force(i) = -cap;
    }

    return force;
}

void HubbardSOCMeasureFixedSDSD::write() const
{
    writeThreadSum(den, "den.dat", ios::app);

    writeThreadSum(KNum, "KNum.dat", ios::app);
    writeThreadSum(VNum, "VNum.dat", ios::app);
    writeThreadSum(RNum, "RNum.dat", ios::app);
    writeThreadSum(HNum, "HNum.dat", ios::app);

    writeThreadSum(NupNum.size(),    NupNum.data(),    "NupNum.dat",    ios::app);
    writeThreadSum(NdnNum.size(),    NdnNum.data(),    "NdnNum.dat",    ios::app);
    writeThreadSum(SplusNum.size(),  SplusNum.data(),  "SplusNum.dat",  ios::app);
    writeThreadSum(SminusNum.size(), SminusNum.data(), "SminusNum.dat", ios::app);

    writeThreadSum(NupTotNum,   "NupTotNum.dat",   ios::app);
    writeThreadSum(NdnTotNum,   "NdnTotNum.dat",   ios::app);
    writeThreadSum(SplusTotNum, "SplusTotNum.dat", ios::app);
    writeThreadSum(SminusTotNum, "SminusTotNum.dat", ios::app);
}

double HubbardSOCMeasureFixedSDSD::getMemory() const
{
    double mem(0.0);
    mem += 8.0;
    mem += 8.0;
    mem += 16.0;
    mem += 16.0*4;
    mem += NupNum.getMemory()+NdnNum.getMemory()+SplusNum.getMemory()+SminusNum.getMemory();
    mem += 16.0*4;
    mem += wfDaggerK.getMemory();
    return mem;
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

void HubbardSOCMeasureFixedSDSD::addEnergy(SDSDOperation &sdsdOperation, complex<double> denIncrement)
{
    size_t L = hubbardSOC->getL(); size_t L2 = L*2;  size_t N = walkerLeft->getN();

    const TensorHao<complex<double>, 2> &theta_T = sdsdOperation.returnTheta_T();
    const TensorHao<complex<double>, 1> &greenDiagonal = sdsdOperation.returnGreenDiagonal();
    const TensorHao<complex<double>, 1> &greenOffDiagonal = sdsdOperation.returnGreenOffDiagonal();

    complex<double> Kenergy(0,0), Venergy(0,0), Renergy(0,0);

    //Add K
    for(size_t i = 0; i < L2; ++i)
    {
        for(size_t j = 0; j < N; ++j) Kenergy += wfDaggerK(j,i) * theta_T(j,i);
    }

    //Add U
    const TensorHao< double, 1> &U = hubbardSOC->getU();
    for(size_t i = 0; i < L; ++i)
    {
        Venergy += U(i) * ( greenDiagonal(i)*greenDiagonal(i+L) - greenOffDiagonal(i)*greenOffDiagonal(i+L) );
    }

    //Add mu and pinning field
    const TensorHao< double, 1> &mu = hubbardSOC->getMu();
    const TensorHao< double, 1> &hx = hubbardSOC->getHx();
    const TensorHao< double, 1> &hy = hubbardSOC->getHy();
    const TensorHao< double, 1> &hz = hubbardSOC->getHz();
    for(size_t i = 0; i < L; ++i)
    {
        Renergy += ( -mu(i) + hz(i)*0.5 ) * greenDiagonal(i);
        Renergy += ( -mu(i) - hz(i)*0.5 ) * greenDiagonal(i+L);
        Renergy += complex<double>( hx(i)*0.5, -hy(i)*0.5 ) * greenOffDiagonal(i);
        Renergy += complex<double>( hx(i)*0.5,  hy(i)*0.5 ) * greenOffDiagonal(i+L);
    }

    KNum += ( Kenergy * denIncrement );
    VNum += ( Venergy * denIncrement );
    RNum += ( Renergy * denIncrement );
    HNum += ( ( Kenergy + Venergy + Renergy ) * denIncrement );
}

void HubbardSOCMeasureFixedSDSD::addNupNdn(SDSDOperation &sdsdOperation, complex<double> denIncrement)
{
    size_t L = hubbardSOC->getL();
    const TensorHao<complex<double>, 1> &greenDiagonal = sdsdOperation.returnGreenDiagonal();

    if( NupNum.rank(0) != L ) { NupNum.resize(L); NupNum = complex<double>(0,0); }
    if( NdnNum.rank(0) != L ) { NdnNum.resize(L); NdnNum = complex<double>(0,0); }

    for (size_t i = 0; i < L; ++i)
    {
        NupNum(i) += greenDiagonal(i) * denIncrement;
        NdnNum(i) += greenDiagonal(i+L) * denIncrement;
    }

    NupTotNum += greenDiagonal.sum(0,   L) * denIncrement;
    NdnTotNum += greenDiagonal.sum(L, 2*L) * denIncrement;
}

void HubbardSOCMeasureFixedSDSD::addSplusSminus(SDSDOperation &sdsdOperation, complex<double> denIncrement)
{
    size_t L = hubbardSOC->getL();
    const TensorHao<complex<double>, 1> &greenOffDiagonal = sdsdOperation.returnGreenOffDiagonal();

    if( SplusNum.rank(0) != L )  { SplusNum.resize(L);  SplusNum = complex<double>(0,0); }
    if( SminusNum.rank(0) != L ) { SminusNum.resize(L); SminusNum = complex<double>(0,0); }

    for (size_t i = 0; i < L; ++i)
    {
        SplusNum(i)  += greenOffDiagonal(i)   * denIncrement;
        SminusNum(i) += greenOffDiagonal(i+L) * denIncrement;
    }

    SplusTotNum  += greenOffDiagonal.sum(0,   L) * denIncrement;
    SminusTotNum += greenOffDiagonal.sum(L, 2*L) * denIncrement;
}

