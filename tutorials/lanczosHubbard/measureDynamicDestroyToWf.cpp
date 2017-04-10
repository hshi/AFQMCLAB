//
// Created by boruoshihao on 4/10/17.
//
#include "afqmclab.h"
#include "measureDynamicParam.h"

using namespace std;
using namespace tensor_hao;

void measureLogExpMinusTauModelDestroyToWf(MeasureBasedOnLanMatrix &meas, const DynamicParams& dynamicParams)
{
    TensorHao<double,1> tau(100);
    for(size_t j = 0; j < tau.size() ; ++j) tau(j) = 0.02*j;
    TensorHao<double,1> Gtau = meas.returnLogExpMinusTauModel(tau,
                                                              dynamicParams.matrixSize,
                                                              dynamicParams.accuracy,
                                                              dynamicParams.litForProjection,
                                                              dynamicParams.lanwfsFlag);
    writeFile(tau.size(), tau.data(), Gtau.data(), "CDagger-ExpMTauH-C.dat" );
}

void measureMinusSpectralFunctionDestroyToWf(MeasureBasedOnLanMatrix &meas, double E0, const DynamicParams& dynamicParams)
{
    TensorHao<complex<double>,1> omega(3000), EMinusOgema(3000);
    for(size_t j = 0; j < omega.size() ; ++j) omega(j) = complex<double>(0.02*j-30.0, 0.0);
    EMinusOgema = complex<double>(E0, 0.1) - omega;
    TensorHao<complex<double>,1> spectral = meas.returnGreenFunction(EMinusOgema,
                                                                     dynamicParams.matrixSize,
                                                                     dynamicParams.accuracy,
                                                                     dynamicParams.litForProjection,
                                                                     dynamicParams.lanwfsFlag);
    writeFile(omega.size(), omega.data(), spectral.data(), "spectralMinus.dat" );
}

void measureDynamicDestroyToWf(Lanczos &lan, RealMaterial& H, const DynamicParams& dynamicParams)
{
    size_t i = 2;
    const LanczosBasisWf & phi0 = lan.getEigenstate(0);
    LanczosBasisWf newPhi;

    vector<LanOneOperator> Cup(1); Cup[0] = { i, {1.0, 0.0} };
    H.applyCupToWf(phi0, newPhi, Cup);

    RealMaterial HNupMinusOne = H.generateNewModel( H.getL(), H.getNup()-1, H.getNdn() );
    MeasureBasedOnLanMatrix meas( HNupMinusOne, newPhi );

    measureLogExpMinusTauModelDestroyToWf( meas, dynamicParams );
    measureMinusSpectralFunctionDestroyToWf( meas, lan.getEigenvalue(0), dynamicParams );
}
