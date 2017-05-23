//
// Created by boruoshihao on 1/10/17.
//

#include "../include/SDSDOperation.h"

using namespace std;
using namespace tensor_hao;

SDSDOperation::SDSDOperation() : state(SDSDOperationState::VOID), walkerLeft(nullptr), walkerRight(nullptr)
{
}

SDSDOperation::SDSDOperation(const SD &walkerLeft_, const SD &walkerRight_)
{
    state = SDSDOperationState::VOID;
    walkerLeft  = &walkerLeft_;
    walkerRight = &walkerRight_;

    size_t L = walkerLeft->getL(); size_t N = walkerLeft->getN();
    if( L != walkerRight->getL() || N != walkerRight->getN() )
    {
        cout<<"Error!!! Find Inconsistency between walkerLeft and walkerRight!"<<endl;
        exit(1);
    }
}

SDSDOperation::~SDSDOperation() { }

SDSDOperationState SDSDOperation::getState() const { return state; }

const SD *SDSDOperation::getWalkerLeft() const { return walkerLeft; }

const SD *SDSDOperation::getWalkerRight() const { return walkerRight; }

const LUDecomp<complex<double>> &SDSDOperation::returnLUOverlap()
{
    calculateLUOverlap();
    return LUOverlap;
}

const TensorHao<complex<double>, 2> &SDSDOperation::returnTheta_T()
{
    calculateLUOverlap();
    calculateTheta_T();
    return theta_T;
}

void SDSDOperation::reSet()
{
    state = SDSDOperationState::VOID;
}

complex<double> SDSDOperation::returnLogOverlap()
{
    calculateLUOverlap();
    return conj(walkerLeft->getLogw()) + walkerRight->getLogw() + logDeterminant(LUOverlap);
}

TensorHao<complex<double>, 2> SDSDOperation::returnGreenMatrix()
{
    calculateLUOverlap();
    calculateTheta_T();

    size_t L = walkerLeft->getL();
    TensorHao<complex<double>, 2> greenMatrix(L,L);

    BL_NAME(gmm)( conj( walkerLeft->getWf() ), theta_T, greenMatrix );

    return greenMatrix;
}

tensor_hao::TensorHao<std::complex<double>, 1> SDSDOperation::returnGreenDiagonal()
{
    calculateLUOverlap();
    calculateTheta_T();

    size_t L = walkerLeft->getL(); size_t N = walkerLeft->getN();
    const TensorHao<complex<double>, 2> &wfLeft = walkerLeft->getWf();

    TensorHao<complex<double>, 1> greenDiagonal(L);
    greenDiagonal = complex<double>(0,0);
    for(size_t j = 0; j < N; ++j)
    {
        for(size_t i = 0; i < L; ++i)
        {
            greenDiagonal(i) += conj( wfLeft(i, j) ) * theta_T(j,i);
        }
    }

    return greenDiagonal;
}

tensor_hao::TensorHao<std::complex<double>, 1> SDSDOperation::returnGreenOffDiagonal()
{
    calculateLUOverlap();
    calculateTheta_T();

    size_t L = walkerLeft->getL(); size_t N = walkerLeft->getN();
    const TensorHao<complex<double>, 2> &wfLeft = walkerLeft->getWf();

    size_t halfL = L/2;
    if( L != halfL*2 ) { cout<<"Error!!! Green Matrix rank size is odd number! "<<L<<endl; exit(1); }

    TensorHao<complex<double>, 1> greenOffDiagonal(L);
    greenOffDiagonal = complex<double>(0,0);
    for(size_t j = 0; j < N; ++j)
    {
        for(size_t i = 0; i < halfL; ++i)
        {
            greenOffDiagonal(i)       += conj( wfLeft(i,       j) ) * theta_T(j, i+halfL); // C_i^\dagger C_{i+halfL}
            greenOffDiagonal(i+halfL) += conj( wfLeft(i+halfL, j) ) * theta_T(j, i      ); // C_{i+halfL}^\dagger C_i
        }
    }

    return greenOffDiagonal;
}

double SDSDOperation::getMemory() const
{
    return 8.0*2+LUOverlap.A.getMemory()+LUOverlap.ipiv.getMemory()+theta_T.getMemory();
}

SDSDOperation::SDSDOperation(const SDSDOperation &x) { }

SDSDOperation &SDSDOperation::operator=(const SDSDOperation &x) { return *this; }

void SDSDOperation::calculateLUOverlap()
{
    if( state >= SDSDOperationState::LUOVERLAP ) return;

    size_t N = walkerLeft->getN();
    TensorHao<complex<double>,2> overlapMatrix(N,N);
    BL_NAME(gmm)( walkerLeft->getWf(), walkerRight->getWf(), overlapMatrix, 'C' );
    LUOverlap = BL_NAME(LUconstruct)( move(overlapMatrix) );

    state = SDSDOperationState::LUOVERLAP;
}

void SDSDOperation::calculateTheta_T()
{
    if( state >= SDSDOperationState::THETA_T ) return;

    theta_T =  BL_NAME(solve_lineq)( LUOverlap, trans( walkerRight->getWf() ), 'T' );

    state = SDSDOperationState::THETA_T;
}

void sampleWalkerFromPhiT(SD &walker, const SD &phiT)
{
    walker = phiT;
}