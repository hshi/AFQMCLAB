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

SD2sSD2isOperation::~SD2sSD2isOperation()
{
}

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

void SD2sSD2isOperation::reSet()
{
    state = SD2sSD2isOperationState::VOID;
}

complex<double> SD2sSD2isOperation::returnLogOverlap()
{
    calculateLUOverlap();
    return conj(walkerLeft->getLogw())+walkerRight->getLogw()+logDeterminant(LUOverlapUp)+logDeterminant(LUOverlapDn);
}

TensorHao<complex<double>, 2> SD2sSD2isOperation::returnGreenMatrixUp()
{
    calculateLUOverlap();
    calculateTheta_T();

    size_t L = walkerLeft->getL();
    TensorHao<complex<double>, 2> greenMatrixUp(L,L);
    BL_NAME(gmm)( conj( walkerLeft->getWfUp() ), thetaUp_T, greenMatrixUp );

    return greenMatrixUp;
}

TensorHao<complex<double>, 2> SD2sSD2isOperation::returnGreenMatrixDn()
{
    calculateLUOverlap();
    calculateTheta_T();

    size_t L = walkerLeft->getL();
    TensorHao<complex<double>, 2> greenMatrixDn(L,L);
    BL_NAME(gmm)( conj( walkerLeft->getWfDn() ), thetaDn_T, greenMatrixDn );

    return greenMatrixDn;
}

TensorHao<complex<double>, 1> SD2sSD2isOperation::returnGreenDiagonalUp()
{
    calculateLUOverlap();
    calculateTheta_T();

    size_t L = walkerLeft->getL(); size_t Nup = walkerLeft->getNup();
    const TensorHao<complex<double>, 2> &wfLeftUp = walkerLeft->getWfUp();
    TensorHao<complex<double>, 1> greenDiagonalUp(L);
    greenDiagonalUp = complex<double>(0,0);
    for(size_t j = 0; j < Nup; ++j)
    {
        for(size_t i = 0; i < L; ++i)
        {
            greenDiagonalUp(i) += conj( wfLeftUp(i, j) ) * thetaUp_T(j,i);
        }
    }
    return greenDiagonalUp;
}

TensorHao<complex<double>, 1> SD2sSD2isOperation::returnGreenDiagonalDn()
{
    calculateLUOverlap();
    calculateTheta_T();

    size_t L = walkerLeft->getL(); size_t Ndn = walkerLeft->getNdn();
    const TensorHao<complex<double>, 2> &wfLeftDn = walkerLeft->getWfDn();
    TensorHao<complex<double>, 1> greenDiagonalDn(L);
    greenDiagonalDn = complex<double>(0,0);
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
    return 8.0*2 +LUOverlapUp.A.getMemory()+LUOverlapUp.ipiv.getMemory()
                 +LUOverlapDn.A.getMemory()+LUOverlapDn.ipiv.getMemory()
                 +thetaUp_T.getMemory()+thetaDn_T.getMemory();
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

void sampleWalkerFromPhiT(SD2is &walker, const SD2s &phiT)
{
    cout<<"Error!!! We can not sample SD2s walker to get SD2is walker!"<<endl;
    exit(1);
}