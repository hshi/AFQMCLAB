//
// Created by boruoshihao on 5/22/17.
//

#include "../include/SD2sSD2isOperation.h"

using namespace std;
using namespace tensor_hao;

SD2sSD2isOperation::SD2sSD2isOperation():state(SD2sSD2isOperationState::VOID), walkerLeft(nullptr), walkerRight(nullptr)
{
}

SD2sSD2isOperation::SD2sSD2isOperation(const SD2s &walkerLeft_, const SD2is &walkerRight_)
{
    set(walkerLeft_, walkerRight_);
}

SD2sSD2isOperation::~SD2sSD2isOperation() { }

SD2sSD2isOperationState SD2sSD2isOperation::getState() const { return state; }

const SD2s *SD2sSD2isOperation::getWalkerLeft() const { return walkerLeft; }

const SD2is *SD2sSD2isOperation::getWalkerRight() const { return walkerRight; }

const LUDecomp<complex<double>> &SD2sSD2isOperation::returnLUOverlapUp()
{
    calculateLUOverlap();
    return LUOverlapUp;
}

const LUDecomp<complex<double>> &SD2sSD2isOperation::returnLUOverlapDn()
{
    calculateLUOverlap();
    return LUOverlapDn;
}

const TensorHao<complex<double>, 2> &SD2sSD2isOperation::returnThetaUp_T()
{
    calculateLUOverlap();
    calculateTheta_T();
    return thetaUp_T;
}

const TensorHao<complex<double>, 2> &SD2sSD2isOperation::returnThetaDn_T()
{
    calculateLUOverlap();
    calculateTheta_T();
    return thetaDn_T;
}

void SD2sSD2isOperation::set(const SD2s &walkerLeft_, const SD2is &walkerRight_)
{
    state = SD2sSD2isOperationState::VOID;
    walkerLeft  = &walkerLeft_;
    walkerRight = &walkerRight_;

    size_t L = walkerLeft->getL(); size_t Nup = walkerLeft->getNup(); size_t Ndn = walkerLeft->getNdn();
    if( L != walkerRight->getL() || Nup != walkerRight->getNup() || Ndn != walkerRight->getNdn() )
    {
        cout<<"Error!!! Find Inconsistency between walkerLeft and walkerRight!"<<endl;
        exit(1);
    }

    wfRightUp=TensorHaoRef<complex<double>, 2>(L, Nup);
    wfRightDn=TensorHaoRef<complex<double>, 2>(L, Ndn);
    wfRightUp.point( const_cast<complex<double>*> ( walkerRight->getWf().data() ) );
    wfRightDn.point( const_cast<complex<double>*> ( walkerRight->getWf().data() ) );
}

void SD2sSD2isOperation::reSet()
{
    state = SD2sSD2isOperationState::VOID;
}

complex<double> SD2sSD2isOperation::returnLogOverlap()
{
    calculateLUOverlap();
    logOverlap =conj(walkerLeft->getLogw())+walkerRight->getLogw()+logDeterminant(LUOverlapUp)+logDeterminant(LUOverlapDn);
    return logOverlap;
}

const TensorHao<complex<double>, 2> &SD2sSD2isOperation::returnGreenMatrixUp()
{
    calculateLUOverlap();
    calculateTheta_T();

    size_t L = walkerLeft->getL();
    greenMatrixUp.resize(L,L);
    BL_NAME(gmm)( conj( walkerLeft->getWfUp() ), thetaUp_T, greenMatrixUp );

    return greenMatrixUp;
}

const TensorHao<complex<double>, 2> &SD2sSD2isOperation::returnGreenMatrixDn()
{
    calculateLUOverlap();
    calculateTheta_T();

    size_t L = walkerLeft->getL();
    greenMatrixDn.resize(L,L);
    BL_NAME(gmm)( conj( walkerLeft->getWfDn() ), thetaDn_T, greenMatrixDn );

    return greenMatrixDn;
}

const TensorHao<complex<double>, 1> &SD2sSD2isOperation::returnGreenDiagonalUp()
{
    calculateLUOverlap();
    calculateTheta_T();

    size_t L = walkerLeft->getL(); size_t Nup = walkerLeft->getNup();
    const TensorHao<complex<double>, 2> &wfLeftUp = walkerLeft->getWfUp();
    greenDiagonalUp.resize(L); greenDiagonalUp = complex<double>(0,0);
    for(size_t j = 0; j < Nup; ++j)
    {
        for(size_t i = 0; i < L; ++i)
        {
            greenDiagonalUp(i) += conj( wfLeftUp(i, j) ) * thetaUp_T(j,i);
        }
    }
    return greenDiagonalUp;
}

const TensorHao<complex<double>, 1> &SD2sSD2isOperation::returnGreenDiagonalDn()
{
    calculateLUOverlap();
    calculateTheta_T();

    size_t L = walkerLeft->getL(); size_t Ndn = walkerLeft->getNdn();
    const TensorHao<complex<double>, 2> &wfLeftDn = walkerLeft->getWfDn();
    greenDiagonalDn.resize(L); greenDiagonalDn = complex<double>(0,0);
    for(size_t j = 0; j < Ndn; ++j)
    {
        for(size_t i = 0; i < L; ++i)
        {
            greenDiagonalDn(i) += conj( wfLeftDn(i, j) ) * thetaDn_T(j,i);
        }
    }
    return greenDiagonalDn;
}

double SD2sSD2isOperation::getMemory() const
{
    return 8.0*2+LUOverlapUp.A.getMemory()+LUOverlapUp.ipiv.getMemory()
                +LUOverlapDn.A.getMemory()+LUOverlapDn.ipiv.getMemory()
                +thetaUp_T.getMemory()+thetaDn_T.getMemory()
                +16.0+greenMatrixUp.getMemory()+greenMatrixDn.getMemory()
                +greenDiagonalUp.getMemory()+greenDiagonalDn.getMemory();
}

SD2sSD2isOperation::SD2sSD2isOperation(const SD2sSD2isOperation &x) { }

SD2sSD2isOperation &SD2sSD2isOperation::operator=(const SD2sSD2isOperation &x) { return *this; }

void SD2sSD2isOperation::calculateLUOverlap()
{
    if( state >= SD2sSD2isOperationState ::LUOVERLAP ) return;

    size_t Nup = walkerLeft->getNup(); size_t Ndn = walkerLeft->getNdn();

    TensorHao<complex<double>,2> overlapMatrixUp(Nup, Nup), overlapMatrixDn(Ndn, Ndn);
    BL_NAME(gmm)( walkerLeft->getWfUp(), wfRightUp, overlapMatrixUp, 'C' );
    BL_NAME(gmm)( walkerLeft->getWfDn(), wfRightDn, overlapMatrixDn, 'C' );

    LUOverlapUp = BL_NAME(LUconstruct)( move(overlapMatrixUp) );
    LUOverlapDn = BL_NAME(LUconstruct)( move(overlapMatrixDn) );

    state = SD2sSD2isOperationState ::LUOVERLAP;
}

void SD2sSD2isOperation::calculateTheta_T()
{
    if( state >= SD2sSD2isOperationState ::THETA_T ) return;

    thetaUp_T =  BL_NAME(solve_lineq)( LUOverlapUp, trans(wfRightUp), 'T' );
    thetaDn_T =  BL_NAME(solve_lineq)( LUOverlapDn, trans(wfRightDn), 'T' );

    state = SD2sSD2isOperationState ::THETA_T;
}

void setWalkerFromPhiT(vector<SD2is> &walker, const SD2s &phiT)
{
    if( MPIRank()==0 ) cout<<"Warning!!! Set SD2is walker from SD2S phiT, only pick one spin component!"<<endl;

    int walkerSizePerThread = walker.size();
    int walkerSize = walkerSizePerThread * MPISize();
    if( walkerSize < 1 ) { cout<<"Error!!! Total walkerSize is smaller than 1:  "<<walkerSize<<endl; exit(1); }

    size_t L = phiT.getL(); size_t Nup = phiT.getNup(); size_t Ndn = phiT.getNdn();
    for(int i = 0; i < walkerSizePerThread; ++i)
    {
        walker[i].resize(L, Nup, Ndn);
        walker[i].logwRef() = phiT.getLogw();
        if( Nup >= Ndn )  walker[i].wfRef() = phiT.getWfUp();
        else walker[i].wfRef() = phiT.getWfDn();
    }
}