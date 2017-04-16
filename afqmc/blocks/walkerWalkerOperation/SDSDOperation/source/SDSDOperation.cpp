//
// Created by boruoshihao on 1/10/17.
//

#include "../include/SDSDOperation.h"

using namespace std;
using namespace tensor_hao;

SDSDOperation::SDSDOperation() : state(SDOperationState::VOID), walkerLeft(nullptr), walkerRight(nullptr)
{
}

SDSDOperation::SDSDOperation(const SD &walkerLeft_, const SD &walkerRight_)
{
    state = SDOperationState::VOID;
    walkerLeft  = &walkerLeft_;
    walkerRight = &walkerRight_;
}

SDSDOperation::~SDSDOperation() { }

SDOperationState SDSDOperation::getState() const { return state; }

const SD *SDSDOperation::getWalkerLeft() const { return walkerLeft; }

const SD *SDSDOperation::getWalkerRight() const { return walkerRight; }

const LUDecomp<complex<double>> &SDSDOperation::returnLUOverlap()
{
    calculateLUOverlap();
    return LUOverlap;
}

const TensorHao<complex<double>, 2> &SDSDOperation::returnWfLeftDagger()
{
    calculateWfLeftDagger();
    return wfLeftDagger;
}

void SDSDOperation::reSet()
{
    state = SDOperationState::VOID;
}

complex<double> SDSDOperation::returnLogOverlap()
{
    calculateLUOverlap();
    return conj( (*walkerLeft).getLogw() ) + (*walkerRight).getLogw() + logDeterminant( LUOverlap );
}

TensorHao<complex<double>, 2> SDSDOperation::returnGreenMatrix()
{
    calculateLUOverlap();
    calculateWfLeftDagger();

    size_t L = (*walkerLeft).getL();
    TensorHao<complex<double>, 2> greenMatrix(L,L);

    BL_NAME(gmm)( wfLeftDagger, (*walkerRight).getWf(), greenMatrix, 'T', 'T');

    return greenMatrix;
}

tensor_hao::TensorHao<std::complex<double>, 1> SDSDOperation::returnGreenDiagonal()
{
    calculateLUOverlap();
    calculateWfLeftDagger();

    size_t L = (*walkerLeft).getL();
    size_t N = (*walkerLeft).getN();
    const TensorHao<complex<double>, 2> &wfRight = (*walkerRight).getWf();

    TensorHao<complex<double>, 1> greenDiagonal(L);
    greenDiagonal = complex<double>(0,0);
    for(size_t j = 0; j < N; ++j)
    {
        for(size_t i = 0; i < L; ++i)
        {
            greenDiagonal(i) += wfRight(i, j) * wfLeftDagger(j,i);
        }
    }

    return greenDiagonal;
}

tensor_hao::TensorHao<std::complex<double>, 1> SDSDOperation::returnGreenOffDiagonal()
{
    calculateLUOverlap();
    calculateWfLeftDagger();

    size_t L = (*walkerLeft).getL();
    size_t N = (*walkerLeft).getN();
    const TensorHao<complex<double>, 2> &wfRight = (*walkerRight).getWf();

    size_t halfL = L/2;
    if( L != halfL*2 ) { cout<<"Error!!! Green Matrix rank size is odd number! "<<L<<endl; exit(1); }

    TensorHao<complex<double>, 1> greenOffDiagonal(L);
    greenOffDiagonal = complex<double>(0,0);
    for(size_t j = 0; j < N; ++j)
    {
        for(size_t i = 0; i < halfL; ++i)
        {
            greenOffDiagonal(i)       += wfRight(i+halfL, j) * wfLeftDagger(j, i); // C_i^\dagger C_{i+halfL}
            greenOffDiagonal(i+halfL) += wfRight(i, j) * wfLeftDagger(j, i+halfL); // C_{i+halfL}^\dagger C_i
        }
    }

    return greenOffDiagonal;
}

double SDSDOperation::getMemory() const
{
    return 8.0*2+LUOverlap.A.getMemory()+LUOverlap.ipiv.getMemory()+wfLeftDagger.getMemory();
}

SDSDOperation::SDSDOperation(const SDSDOperation &x) { }

SDSDOperation &SDSDOperation::operator=(const SDSDOperation &x) { return *this; }

void SDSDOperation::calculateLUOverlap()
{
    if( state >= SDOperationState::LUOVERLAP ) return;

    size_t N = (*walkerLeft).getN();
    TensorHao<complex<double>,2> overlapMatrix(N,N);
    BL_NAME(gmm)( (*walkerLeft).getWf(), (*walkerRight).getWf(), overlapMatrix, 'C' );
    LUOverlap = BL_NAME(LUconstruct)( move(overlapMatrix) );

    state = SDOperationState::LUOVERLAP;
}

void SDSDOperation::calculateWfLeftDagger()
{
    if( state >= SDOperationState::WFLEFTDAGGER ) return;

    wfLeftDagger =  BL_NAME(solve_lineq)( LUOverlap, conjtrans( (*walkerLeft).getWf() ) );

    state = SDOperationState::WFLEFTDAGGER;
}

void sampleWalkerFromPhiT(SD &walker, const SD &phiT)
{
    walker = phiT;
}
