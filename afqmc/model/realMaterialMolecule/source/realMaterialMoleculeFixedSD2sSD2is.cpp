//
// Created by boruoshihao on 6/5/17.
//

#include "../include/realMaterialMoleculeFixedSD2sSD2is.h"
#include "../../../utilities/manipulateMCData/include/writeThreadSum.h"

using namespace std;
using namespace tensor_hao;

RealMaterialMoleculeFixedSD2sSD2is::RealMaterialMoleculeFixedSD2sSD2is()
{
    initModelWalkerNullptr();
    reSet();
}

RealMaterialMoleculeFixedSD2sSD2is::RealMaterialMoleculeFixedSD2sSD2is(const RealMaterialMolecule &realMaterialMolecule_,
                                                                       const SD2s &walkerLeft_)
{
    setModelWalker(realMaterialMolecule_, walkerLeft_);
    reSet();
}

RealMaterialMoleculeFixedSD2sSD2is::~RealMaterialMoleculeFixedSD2sSD2is()
{

}

void RealMaterialMoleculeFixedSD2sSD2is::initModelWalkerNullptr()
{
    realMaterialMolecule = nullptr;
    walkerLeft = nullptr;
}

void RealMaterialMoleculeFixedSD2sSD2is::setModelWalker(const RealMaterialMolecule &realMaterialMolecule_, const SD2s &walkerLeft_)
{
    if( realMaterialMolecule_.getL() != walkerLeft_.getL() ) {cout<<"Model L does not consistent with walker L!"<<endl; exit(1);}
    if( realMaterialMolecule_.getNup() != walkerLeft_.getNup() ) {cout<<"Model Nup does not consistent with walker Nup!"<<endl; exit(1);}
    if( realMaterialMolecule_.getNdn() != walkerLeft_.getNdn() ) {cout<<"Model Ndn does not consistent with walker Ndn!"<<endl; exit(1);}

    realMaterialMolecule = &realMaterialMolecule_;
    walkerLeft = &walkerLeft_;
    initWfDaggerT();
    initWfDaggerCholeskyVecs();
}

void RealMaterialMoleculeFixedSD2sSD2is::reSet()
{
    complex<double> zero(0,0);

    den = zero;
    TNum = zero;
    choleskyBgNum = zero;
    choleskyExNum = zero;
    HNum = zero;
}

complex<double> RealMaterialMoleculeFixedSD2sSD2is::returnEnergy()
{
    complex<double> Htot   = MPISum(HNum);
    complex<double> denTot = MPISum(den);
    complex<double> energy;
    if( MPIRank() == 0 ) energy = Htot/denTot;
    MPIBcast(energy);
    return energy;
}

TensorHao<double,1> RealMaterialMoleculeFixedSD2sSD2is::returnCholeskyBg()
{
    size_t choleskyNumber = realMaterialMolecule->getCholeskyNumber();

    TensorHao<complex<double>, 1> choleskyBgTot( choleskyNumber );
    MPISum( choleskyNumber, choleskyBgNum.data(), choleskyBgTot.data() );

    complex<double> denTot = MPISum(den);

    TensorHao<double,1> choleskyBg( choleskyNumber );
    for(size_t i = 0; i < choleskyNumber; ++i) choleskyBg(i) = ( choleskyBgTot(i)/denTot ).real();
    MPIBcast(choleskyBg);

    return choleskyBg;
}

void RealMaterialMoleculeFixedSD2sSD2is::addMeasurement(SD2sSD2isOperation &sd2sSD2isOperation, complex<double> denIncrement)
{
    checkWalkerLeft(sd2sSD2isOperation);

    den += denIncrement;

    const TensorHao<complex<double>, 2> &thetaUp_T =  sd2sSD2isOperation.returnThetaUp_T();
    const TensorHao<complex<double>, 2> &thetaDn_T =  sd2sSD2isOperation.returnThetaDn_T();

    addEnergy(thetaUp_T, thetaDn_T, denIncrement);
}

void RealMaterialMoleculeFixedSD2sSD2is::write() const
{
    writeThreadSum(den, "den.dat", ios::app);
    writeThreadSum(TNum, "TNum.dat", ios::app);
    writeThreadSum(choleskyBgNum.size(), choleskyBgNum.data(), "choleskyBgNum.dat", ios::app);
    writeThreadSum(choleskyExNum.size(), choleskyExNum.data(), "choleskyExNum.dat", ios::app);
    writeThreadSum(HNum, "HNum.dat", ios::app);
}

double RealMaterialMoleculeFixedSD2sSD2is::getMemory() const
{
    double mem(0.0);
    mem += 8.0*2;
    mem += 16.0*3; //den, TNum, HNum
    mem += choleskyBgNum.getMemory()+choleskyExNum.getMemory();
    mem += wfUpDaggerT.getMemory() + wfDnDaggerT.getMemory();
    mem += wfUpDaggerCholeskyVecs.getMemory() + wfDnDaggerCholeskyVecs.getMemory();
    return mem;
}

RealMaterialMoleculeFixedSD2sSD2is::RealMaterialMoleculeFixedSD2sSD2is(const RealMaterialMoleculeFixedSD2sSD2is &x)
{

}

RealMaterialMoleculeFixedSD2sSD2is & RealMaterialMoleculeFixedSD2sSD2is::operator=(const RealMaterialMoleculeFixedSD2sSD2is &x)
{
    return *this;
}

void RealMaterialMoleculeFixedSD2sSD2is::initWfDaggerT()
{
    size_t L = walkerLeft->getL(); size_t Nup = walkerLeft->getNup(); size_t Ndn = walkerLeft->getNdn();

    wfUpDaggerT.resize(Nup, L); wfDnDaggerT.resize(Ndn, L);

    const TensorHao<double,2> & t = realMaterialMolecule->getT();
    TensorHao<complex<double>, 2> tComplex(L,L);
    for(size_t i = 0; i < L; ++i)
    {
        for(size_t j = 0; j < L; ++j) tComplex(j,i) = t(j,i);
    }

    BL_NAME(gmm)(walkerLeft->getWfUp(), tComplex, wfUpDaggerT, 'C');
    BL_NAME(gmm)(walkerLeft->getWfDn(), tComplex, wfDnDaggerT, 'C');
}

void RealMaterialMoleculeFixedSD2sSD2is::initWfDaggerCholeskyVecs()
{
    size_t L = walkerLeft->getL(); size_t Nup = walkerLeft->getNup(); size_t Ndn = walkerLeft->getNdn();
    size_t choleskyNumber = realMaterialMolecule->getCholeskyNumber();

    wfUpDaggerCholeskyVecs.resize(Nup, L, choleskyNumber); wfDnDaggerCholeskyVecs.resize(Ndn, L, choleskyNumber);

    const TensorHao<double,3> & choleskyVecs = realMaterialMolecule->getCholeskyVecs();
    TensorHao<complex<double>, 2> choleskyVecComplex(L,L);
    TensorHaoRef<complex<double>, 2> wfDaggerCholeskyVec;
    for(size_t k = 0; k < choleskyNumber ; ++k)
    {
        for(size_t i = 0; i < L; ++i)
        {
            for(size_t j = 0; j < L; ++j) choleskyVecComplex(j,i) = choleskyVecs(j,i,k);
        }
        wfDaggerCholeskyVec=wfUpDaggerCholeskyVecs[k];
        BL_NAME(gmm)(walkerLeft->getWfUp(), choleskyVecComplex, wfDaggerCholeskyVec, 'C');
        wfDaggerCholeskyVec=wfDnDaggerCholeskyVecs[k];
        BL_NAME(gmm)(walkerLeft->getWfDn(), choleskyVecComplex, wfDaggerCholeskyVec, 'C');
    }
}

void RealMaterialMoleculeFixedSD2sSD2is::checkWalkerLeft(const SD2sSD2isOperation &sd2sSD2isOperation)
{
    if( walkerLeft != sd2sSD2isOperation.getWalkerLeft() )
    {
        cout<<"Error!!! RealMaterialMoleculeFixedSD2sSD2is only accept SD2sSD2isOperation with fixed SD2s!"<<endl;
        exit(1);
    }
}

void RealMaterialMoleculeFixedSD2sSD2is::addEnergy(const TensorHao<complex<double>, 2> &thetaUp_T,
                                                   const TensorHao<complex<double>, 2> &thetaDn_T,
                                                   complex<double> denIncrement)
{
    size_t choleskyNumber = realMaterialMolecule->getCholeskyNumber();

    if( choleskyBgNum.rank(0) != choleskyNumber ) { choleskyBgNum.resize(choleskyNumber); choleskyBgNum = complex<double>(0,0); }
    if( choleskyExNum.rank(0) != choleskyNumber ) { choleskyExNum.resize(choleskyNumber); choleskyExNum = complex<double>(0,0); }

    complex<double> Tenergy=calculateTenergy(thetaUp_T, thetaDn_T);
    TensorHao<complex<double>, 1> choleskyBg = calculateCholeskyBg(thetaUp_T, thetaDn_T);
    TensorHao<complex<double>, 1> choleskyEx = calculateCholeskyEx(thetaUp_T, thetaDn_T);

    complex<double> Henergy(0.0);
    for(size_t i = 0; i < choleskyNumber; ++i)
    {
        Henergy += ( choleskyBg(i)*choleskyBg(i) -choleskyEx(i) );
    }
    Henergy *= 0.5;
    Henergy += Tenergy;

    TNum += ( Tenergy * denIncrement );
    choleskyBgNum += ( choleskyBg * denIncrement );
    choleskyExNum += ( choleskyEx * denIncrement );
    HNum += ( Henergy * denIncrement );
}

complex<double> RealMaterialMoleculeFixedSD2sSD2is::calculateTenergy(const TensorHao<complex<double>, 2> &thetaUp_T,
                                                                     const TensorHao<complex<double>, 2> &thetaDn_T)
{
    size_t L = walkerLeft->getL(); size_t Nup = walkerLeft->getNup(); size_t Ndn = walkerLeft->getNdn();

    complex<double> Tenergy(0,0);
    for(size_t i = 0; i < L; ++i)
    {
        for(size_t j = 0; j < Nup; ++j) Tenergy += wfUpDaggerT(j,i) * thetaUp_T(j,i);
        for(size_t j = 0; j < Ndn; ++j) Tenergy += wfDnDaggerT(j,i) * thetaDn_T(j,i);
    }
    return Tenergy;
}

TensorHao<complex<double>, 1> RealMaterialMoleculeFixedSD2sSD2is::calculateCholeskyBg(const TensorHao<complex<double>, 2> &thetaUp_T,
                                                                                      const TensorHao<complex<double>, 2> &thetaDn_T)
{
    size_t L = walkerLeft->getL(); size_t Nup = walkerLeft->getNup(); size_t Ndn = walkerLeft->getNdn();
    size_t choleskyNumber = realMaterialMolecule->getCholeskyNumber();

    TensorHaoRef<complex<double>, 2> leftUp(L*Nup, choleskyNumber), leftDn(L*Ndn, choleskyNumber);
    TensorHaoRef<complex<double>, 1> rightUp(L*Nup), rightDn(L*Ndn);
    leftUp.point( wfUpDaggerCholeskyVecs.data() );
    leftDn.point( wfDnDaggerCholeskyVecs.data() );
    rightUp.point( const_cast<complex<double>*>( thetaUp_T.data() ) );
    rightDn.point( const_cast<complex<double>*>( thetaDn_T.data() ) );

    TensorHao<complex<double>, 1> choleskyBg(choleskyNumber);
    BL_NAME(gemv)(leftUp, rightUp, choleskyBg, 'T' );
    BL_NAME(gemv)(leftDn, rightDn, choleskyBg, 'T', 1.0, 1.0 );

    return choleskyBg;
}

TensorHao<complex<double>, 1> RealMaterialMoleculeFixedSD2sSD2is::calculateCholeskyEx(const TensorHao<complex<double>, 2> &thetaUp_T,
                                                                                      const TensorHao<complex<double>, 2> &thetaDn_T)
{
    size_t Nup = walkerLeft->getNup(); size_t Ndn = walkerLeft->getNdn();
    size_t choleskyNumber = realMaterialMolecule->getCholeskyNumber();

    TensorHao<complex<double>, 2> densityUp(Nup, Nup), densityDn(Ndn, Ndn);
    TensorHaoRef<complex<double>, 2> wfDaggerCholeskyVec;
    TensorHao<complex<double>, 1> choleskyEx(choleskyNumber);

    TensorHao<complex<double>, 2> thetaUp, thetaDn;
    thetaUp = trans(thetaUp_T); thetaDn = trans(thetaDn_T);
    for(size_t k = 0; k < choleskyNumber; ++k)
    {
        wfDaggerCholeskyVec = wfUpDaggerCholeskyVecs[k];
        BL_NAME(gmm)( wfDaggerCholeskyVec, thetaUp, densityUp);
        wfDaggerCholeskyVec = wfDnDaggerCholeskyVecs[k];
        BL_NAME(gmm)( wfDaggerCholeskyVec, thetaDn, densityDn);

        choleskyEx(k)=0.0;
        for(size_t i = 0; i < Nup; ++i) { for(size_t j = 0; j < Nup; ++j) choleskyEx(k) += densityUp(j,i) * densityUp(i,j); }
        for(size_t i = 0; i < Ndn; ++i) { for(size_t j = 0; j < Ndn; ++j) choleskyEx(k) += densityDn(j,i) * densityDn(i,j); }
    }

    return choleskyEx;
}