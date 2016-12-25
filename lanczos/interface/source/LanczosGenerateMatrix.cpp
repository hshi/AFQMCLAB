//
// Created by boruoshihao on 10/21/16.
//
#include "../include/LanczosInterface.h"

using namespace tensor_hao;

using namespace std;

double Lanczos::initLanczosMatrixFromLanwfsZero()
{
    double nrm = projectWaveFunction( 0 );

    lanStatus = "both";
    lana.resize(0); lanb.resize(0);
    lanb.push_back( 0.0 );
    getLanczosDiagonalElement( 0 );

    return nrm;
}

int Lanczos::getLanczosMatrixFull(size_t L, double accuracy, double litForProjection)
{
    size_t startIndex = lana.size();
    size_t endIndex = startIndex + L;

    for(size_t i = startIndex; i < endIndex; ++i)
    {
        getLanczosOffdiagonalElement( i );

        if( abs( lanb.back() ) < litForProjection && abs( lanb.back() ) > accuracy ) projectWaveFunctionUpdateLanb(i);

        if( abs( lanb.back() ) <= accuracy ) { prepareLanReturn("full"); return 0; }

        getLanczosDiagonalElement( i );
    }

    lanStatus = ( lana.size() < 4 ) ? "both" : "full" ;
    return 1;
}

int Lanczos::getLanczosMatrixRecurse(size_t L, double accuracy, double litForProjection)
{
    size_t endIndex = lana.size() + L;

    if( endIndex < 4 ) return getLanczosMatrixFull( L, accuracy, litForProjection);

    if( lana.size() < 3 )
    {
        int result = getLanczosMatrixFull(3 - lana.size(), accuracy, litForProjection);
        if( result == 0 ) return 0;
    }

    if( lana.size() < 3 ) { cout<<"Error!!! In getLanczosMatrixRecurse, we should not have lana.size() < 3 "<<endl; exit(1); }

    if( lanStatus != string("both") && lanStatus != string("recurse") ) {cout<<"Error!!! lanStatus is not recurse or both."<<endl; exit(1);}

    size_t startIndex = lana.size();
    for(size_t i = startIndex; i < endIndex; ++i)
    {
        getLanczosOffdiagonalElement( 3 );

        if( abs( lanb.back() ) < litForProjection && abs( lanb.back() ) > accuracy ) projectWaveFunctionUpdateLanb(i);

        if( abs( lanb.back() ) <= accuracy ) { prepareLanReturn("recurse"); return 0; }

        recurseWaveFunctions();

        getLanczosDiagonalElement( 2 );
    }

    lanStatus = "recurse";

    return 1;
}

void Lanczos::getNewLanwfsZero(const vector<double> &vec, double litForProjection)
{
    if( lanStatus == string("none") )  { cout<<"Error!!! Lanczos Matrix has not been initialized!"<<endl; exit(1); }

    if( lanStatus == string("both") || lanStatus == string("bothConverged") || lanStatus == string("full") || lanStatus == string("fullConverged") )
    {
        getNewLanwfsZeroFull(vec);
    }

    if( lanStatus == string("recurse") || lanStatus == string("recurseConverged") )
    {
        getNewLanwfsZeroRecurse(vec, litForProjection);
    }
}

void Lanczos::getNewLanwfsZeroFull(const vector<double> &vec)
{
    if( lana.size() != vec.size() ) { cout<<"Error!!! vec size is different with lana size!"<<endl; exit(1); }

    lanwfs[0].scale( vec[0] );
    for(size_t i = 1; i < vec.size(); ++i)
    {
        lanwfs[0].addEqual( vec[i], lanwfs[i] );
    }

    double nrm = initLanczosMatrixFromLanwfsZero();
    if( abs(nrm-1.0) > 1e-12  ) {cout<<"Warning!!! EuclideanNorm of New Lanwfs[0] is: "<<nrm<<endl;}
}


void Lanczos::getNewLanwfsZeroRecurse(const vector<double> &vec, double litForProjection)
{
    if( vec.size() < 4 ) { getNewLanwfsZeroFull(vec); return; }

    if( lana.size() != vec.size() ) { cout<<"Error!!! vec size is different with lana size!"<<endl; exit(1); }

    getNewLanwfsZeroRecurseZeroToThree(vec, litForProjection);

    getNewLanwfsZeroRecurseThreeToMatrixSize(vec, litForProjection);

    double nrm = initLanczosMatrixFromLanwfsZero();
    if( abs(nrm-1.0) > 1e-12  ) {cout<<"Warning!!! EuclideanNorm of New Lanwfs[0] is: "<<nrm<<endl;}
}

void Lanczos::getNewLanwfsZeroRecurseZeroToThree(const vector<double> &vec, double litForProjection)
{
    double currentb;

    getLanczosHtoWf( 1 );

    for(size_t i = 1; i < 3; ++i)
    {
        currentb = getLanczosOrthonormalWf( i, lana[i-1], lanb[i-1] );

        if( abs( currentb ) < litForProjection ) currentb *= projectWaveFunction( i );

        if( abs( lanb[i] - currentb ) > 1e-12 )
        {
            cout<<setprecision(16)<<"Error!!! Lanczos off diagonal element is not consistent! "
                <<i<<" "<<lanb[i]<<" "<<currentb<<endl;
            exit(1);
        }

        getLanczosHtoWf( i+1 );
    }

    lanwfs[0].scale( vec[0] );
    lanwfs[0].addEqual( vec[1], lanwfs[1] );
    lanwfs[0].addEqual( vec[2], lanwfs[2] );
}

void Lanczos::getNewLanwfsZeroRecurseThreeToMatrixSize(const vector<double> &vec, double litForProjection)
{
    double currentb;

    for(size_t i = 3; i < vec.size(); ++i)
    {
        currentb = getLanczosOrthonormalWf( 3, lana[i-1], lanb[i-1] );

        if( abs( currentb ) < litForProjection ) currentb *= projectWaveFunction( 3 );

        if( abs( lanb[i] - currentb ) > 1e-12 )
        {
            cout<<setprecision(16)<<"Error!!! Lanczos off diagonal element is not consistent! "
                <<i<<" "<<lanb[i]<<" "<<currentb<<endl;
            exit(1);
        }

        lanwfs[0].addEqual( vec[i], lanwfs[3] );

        recurseWaveFunctions();

        if( i != ( vec.size()-1 )  ) getLanczosHtoWf( 3 );
    }
}