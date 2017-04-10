//
// Created by boruoshihao on 4/10/17.
//

#include "afqmclab.h"
#include "measureDynamicParam.h"

using namespace std;
using namespace tensor_hao;

void measureLogExpMinusTauModelDensityToWf(MeasureBasedOnLanMatrix &meas, const DynamicParams& dynamicParams)
{
    TensorHao<double,1> tau(100);
    for(size_t j = 0; j < tau.size() ; ++j) tau(j) = 0.02*j;
    TensorHao<double,1> Ntau = meas.returnLogExpMinusTauModel(tau,
                                                              dynamicParams.matrixSize,
                                                              dynamicParams.accuracy,
                                                              dynamicParams.litForProjection,
                                                              dynamicParams.lanwfsFlag);
    writeFile(tau.size(), tau.data(), Ntau.data(), "N-ExpMTauH-N.dat" );
}

void measureDynamicDensityToWf(Lanczos &lan, RealMaterial& H, const DynamicParams& dynamicParams)
{
    size_t i = 0;
    const LanczosBasisWf & phi0 = lan.getEigenstate(0);
    LanczosBasisWf newPhi;

    vector<LanOneBody> up, dn;
    vector<LanTwoBody> upUp,upDn,dnDn;

    up.push_back( {i, i, 1.0} );
    //dn.push_back( {i, i, 1.0} );

    H.applyOperatorsToWf(phi0, newPhi, up, dn, upUp, upDn, dnDn);

    MeasureBasedOnLanMatrix meas( H, newPhi );

    measureLogExpMinusTauModelDensityToWf( meas, dynamicParams );
}