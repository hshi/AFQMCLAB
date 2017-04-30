//
// Created by boruoshihao on 4/30/17.
//

#include "../include/ghf.h"

using namespace std;
using namespace tensor_hao;

Ghf::Ghf() { }

Ghf::~Ghf() { }

void Ghf::run()
{
    initialParameters();
}

void Ghf::initialParameters()
{
    if( MPIRank()==0 ) method.read("ghf_param");
    MPIBcast(method);

    randomHaoInit(method.seed, 1);
    if( method.seed != -1 ) randomHaoSave();

    if( MPIRank()==0 ) model.read("model_param");
    MPIBcast(model);

    setH0();
}

void Ghf::setH0()
{
    H0 = model.getK();

    size_t L  = model.getL();
    const TensorHao< double, 1> &mu = model.getMu();
    const TensorHao< double, 1> &hx = model.getHx();
    const TensorHao< double, 1> &hy = model.getHy();
    const TensorHao< double, 1> &hz = model.getHz();

    for(size_t i = 0; i < L; ++i)
    {
        H0(i,   i  ) +=  ( -mu(i) + hz(i)*0.5 );
        H0(i+L, i+L) +=  ( -mu(i) - hz(i)*0.5 );
        H0(i,   i+L) +=  complex<double>( hx(i)*0.5, -hy(i)*0.5 );
        H0(i+L, i  ) +=  complex<double>( hx(i)*0.5,  hy(i)*0.5 ) ;
    }
}

void Ghf::setVariationalStateFromH0()
{
    meanFieldVectors = H0;
    BL_NAME(eigen)(meanFieldVectors, meanFieldValues);

    size_t L = model.getL();
    size_t N = model.getN();

    variationalState.resize(2*L, N);
    TensorHao<complex<double>,2> &wf = variationalState.wfRef();
    copy( meanFieldVectors.data(), meanFieldVectors.data()+2*L*N, wf.data() );
}

void Ghf::setOrderParameterFromVariationalState()
{
    SDSDOperation sdsdOperation(variationalState, variationalState);

    density = sdsdOperation.returnGreenDiagonal();
    spinOrbit = sdsdOperation.returnGreenOffDiagonal();
}

void Ghf::setMeanFieldVectorsValuesFromOrderParameter()
{
    meanFieldVectors = H0;

    size_t L = model.getL();
    const TensorHao< double, 1> &U = model.getU();
    for(size_t i = 0; i < L; ++i)
    {
        meanFieldVectors(i,  i  ) += U(i) * density(i+L);
        meanFieldVectors(i+L,i+L) += U(i) * density(i);
        meanFieldVectors(i,  i+L) += U(i) * spinOrbit(i+L);
        meanFieldVectors(i+L,i  ) += U(i) * spinOrbit(i);
    }

    BL_NAME(eigen)(meanFieldVectors, meanFieldValues);
}

void Ghf::setVariationalEnergyFromOrderParameterAndMeanFieldValues()
{
    variationalEnergy = 0.0;

    size_t L = model.getL();
    size_t N = model.getN();
    const TensorHao< double, 1> &U = model.getU();

    for(size_t i = 0; i < N; ++i) variationalEnergy += meanFieldValues(i);
    for(size_t i = 0; i < L; ++i) variationalEnergy += U(i) * ( -density(i)*density(i+L) + spinOrbit(i)*spinOrbit(i+L) ).real() ;
}

void Ghf::setVariationalStateFromMeanFieldVectors()
{
    size_t L = model.getL();
    size_t N = model.getN();

    variationalState.resize(2*L, N);
    TensorHao<complex<double>,2> &wf = variationalState.wfRef();
    copy( meanFieldVectors.data(), meanFieldVectors.data()+2*L*N, wf.data() );
}