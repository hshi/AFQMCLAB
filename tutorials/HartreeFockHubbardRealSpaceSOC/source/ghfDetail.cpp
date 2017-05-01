//
// Created by boruoshihao on 4/30/17.
//
#include "../include/ghf.h"

using namespace std;
using namespace tensor_hao;

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

void Ghf::initialHartreeFockEssential()
{
    if( method.initialType == "setFromModel" )
    {
        size_t L = model.getL();
        density.resize(2*L);   density   = complex<double>(0,0);
        spinOrbit.resize(2*L); spinOrbit = complex<double>(0,0);
    }
    else if( method.initialType == "readWaveFunction" )
    {
        variationalState.read("phi.dat");
        SDSDOperation sdsdOperation(variationalState, variationalState);
        HubbardSOCSDSDMeasureCommute meas(model);
        meas.addMeasurement(sdsdOperation, 1.0);

        minimumEnergy = ( meas.returnEnergy() ).real();
        minimumState = variationalState;
        cout<<"Read wave function, variational energy: "<<fixed<<setprecision(16)<<minimumEnergy<<endl;

        density = sdsdOperation.returnGreenDiagonal();
        spinOrbit = sdsdOperation.returnGreenOffDiagonal();
    }
    else if( method.initialType == "readOrderParameter" )
    {
        density.read("density.dat"); spinOrbit.read("spinOrbit.dat");
    }
    else
    {
        cout<<"Error!!! Do not know initialType "<<method.initialType<<endl;
        exit(1);
    }

    setMeanFieldVectorsValuesFromOrderParameter();
    setVariationalStateFromMeanFieldVectors();
    backupAndUpdateOrderParameterFromVariationalState();
    setVariationalEnergyFromOrderParameterAndMeanFieldValues();
}

void Ghf::setMeanFieldVectorsValuesFromOrderParameter()
{
    size_t L = model.getL();
    const TensorHao< double, 1> &U = model.getU();

    meanFieldVectors = H0;
    for(size_t i = 0; i < L; ++i)
    {
        meanFieldVectors(i,  i  ) += U(i) * density(i+L);
        meanFieldVectors(i+L,i+L) += U(i) * density(i);
        meanFieldVectors(i,  i+L) -= U(i) * spinOrbit(i+L);
        meanFieldVectors(i+L,i  ) -= U(i) * spinOrbit(i);
    }

    meanFieldValues.resize(2*L);

    BL_NAME(eigen)(meanFieldVectors, meanFieldValues);
}

void Ghf::setVariationalStateFromMeanFieldVectors()
{
    size_t L = model.getL();
    size_t N = model.getN();

    variationalState.resize(2*L, N);
    TensorHao<complex<double>,2> &wf = variationalState.wfRef();
    copy( meanFieldVectors.data(), meanFieldVectors.data()+2*L*N, wf.data() );
}

void Ghf::backupAndUpdateOrderParameterFromVariationalState()
{
    densityBefore = move(density);
    spinOrbitBefore = move(spinOrbit);

    SDSDOperation sdsdOperation(variationalState, variationalState);
    density = sdsdOperation.returnGreenDiagonal();
    spinOrbit = sdsdOperation.returnGreenOffDiagonal();
}

void Ghf::setVariationalEnergyFromOrderParameterAndMeanFieldValues()
{
    variationalEnergy = 0.0;

    size_t L = model.getL();
    size_t N = model.getN();
    const TensorHao< double, 1> &U = model.getU();

    for(size_t i = 0; i < N; ++i) variationalEnergy += meanFieldValues(i);
    for(size_t i = 0; i < L; ++i)
    {
        variationalEnergy += U(i) * ( -densityBefore(i)*density(i+L) - densityBefore(i+L)*density(i)
                                      +spinOrbitBefore(i)*spinOrbit(i+L) + spinOrbitBefore(i+L)*spinOrbit(i)
                                      +density(i)*density(i+L)-spinOrbit(i)*spinOrbit(i+L)
                                    ).real();
    }
    cout<<"Variational energy: "<<fixed<<setprecision(16)<<variationalEnergy<<endl;
}

void Ghf::relaxOrderParameter()
{
    size_t L2 = 2*model.getL();
    for(size_t i = 0; i < L2; ++i)
    {
        density(i) = densityBefore(i) + method.relaxMagnitude * ( density(i)-densityBefore(i) );
        spinOrbit(i) = spinOrbitBefore(i) + method.relaxMagnitude * ( spinOrbit(i)-spinOrbitBefore(i) );
    }
}

void Ghf::annealOrderParameter(double anneal)
{
    size_t L = model.getL();
    double real, imag;
    for(size_t i = 0; i < L; ++i)
    {
        density(i  ) *= ( 1.0 + (2.0*uniformHao()-1.0 )*anneal );
        density(i+L) *= ( 1.0 + (2.0*uniformHao()-1.0 )*anneal );

        real  = ( spinOrbit(i) + spinOrbit(i+L) ).real() / 2.0;
        imag  = ( spinOrbit(i) - spinOrbit(i+L) ).imag() / 2.0;
        real *= ( 1.0 + (2.0*uniformHao()-1.0 )*anneal );
        imag *= ( 1.0 + (2.0*uniformHao()-1.0 )*anneal );

        spinOrbit(i)   = complex<double>(real,  imag);
        spinOrbit(i+L) = complex<double>(real, -imag);
    }
}