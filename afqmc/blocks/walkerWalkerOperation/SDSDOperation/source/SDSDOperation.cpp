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
    set(walkerLeft_, walkerRight_);
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

void SDSDOperation::set(const SD &walkerLeft_, const SD &walkerRight_)
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

void SDSDOperation::reSet()
{
    state = SDSDOperationState::VOID;
}

complex<double> SDSDOperation::returnLogOverlap()
{
    calculateLUOverlap();
    logOverlap = conj(walkerLeft->getLogw()) + walkerRight->getLogw() + logDeterminant(LUOverlap);
    return logOverlap;
}

const TensorHao<complex<double>, 2> &SDSDOperation::returnGreenMatrix()
{
    calculateLUOverlap();
    calculateTheta_T();

    size_t L = walkerLeft->getL();
    greenMatrix.resize(L,L);

    BL_NAME(gmm)( conj( walkerLeft->getWf() ), theta_T, greenMatrix );

    return greenMatrix;
}

const tensor_hao::TensorHao<std::complex<double>, 1> &SDSDOperation::returnGreenDiagonal()
{
    calculateLUOverlap();
    calculateTheta_T();

    size_t L = walkerLeft->getL(); size_t N = walkerLeft->getN();
    const TensorHao<complex<double>, 2> &wfLeft = walkerLeft->getWf();

    greenDiagonal.resize(L); greenDiagonal = complex<double>(0,0);
    for(size_t j = 0; j < N; ++j)
    {
        for(size_t i = 0; i < L; ++i)
        {
            greenDiagonal(i) += conj( wfLeft(i, j) ) * theta_T(j,i);
        }
    }

    return greenDiagonal;
}

const tensor_hao::TensorHao<std::complex<double>, 1> &SDSDOperation::returnGreenOffDiagonal()
{
    calculateLUOverlap();
    calculateTheta_T();

    size_t L = walkerLeft->getL(); size_t N = walkerLeft->getN();
    const TensorHao<complex<double>, 2> &wfLeft = walkerLeft->getWf();

    size_t halfL = L/2;
    if( L != halfL*2 ) { cout<<"Error!!! Green Matrix rank size is odd number! "<<L<<endl; exit(1); }

    greenOffDiagonal.resize(L); greenOffDiagonal = complex<double>(0,0);
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
    return 8.0*2+LUOverlap.A.getMemory()+LUOverlap.ipiv.getMemory()+theta_T.getMemory()
           +16.0+greenMatrix.getMemory()+greenDiagonal.getMemory()+greenOffDiagonal.getMemory();
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

void setWalkerFromPhiT(vector<SD> &walker, const SD &phiT)
{
    int walkerSizePerThread = walker.size();
    int walkerSize = walkerSizePerThread * MPISize();
    if( walkerSize < 1 ) { cout<<"Error!!! Total walkerSize is smaller than 1:  "<<walkerSize<<endl; exit(1); }

    for (size_t i = 0; i < walkerSizePerThread; ++i)
    {
        walker[i] = phiT;
    }
}