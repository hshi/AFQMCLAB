//
// Created by boruoshihao on 10/21/16.
//
#include "../include/Lanczos.h"

using namespace tensor_hao;

using namespace std;

void Lanczos::initLanczosMatrixFromLanwfsZero()
{
    projectWaveFunction( 0 );

    lanStatus = 'B';
    lana.resize(0); lanb.resize(0);
    lanb.push_back( 0.0 );
    getLanczosDiagonalElement( 0 );
}

int Lanczos::getLanczosMatrixFull(size_t L, double accuracy, double litForProjection)
{
    size_t startIndex = lana.size();
    size_t endIndex = startIndex + L;

    for(size_t i = startIndex; i < endIndex; ++i)
    {
        getLanczosOffdiagonalElement( i );

        if( abs( lanb.back() ) < accuracy ) { lanb.pop_back(); return 0; }
        if( abs( lanb.back() ) < litForProjection )
        {
            cout<<"\nSmall b "<<lanb.back()<<", try to stabilize new wave function:"<<endl;
            double nrm2 = projectWaveFunction( i );
            cout<<"After projection, the normalized factor is "<<nrm2<<endl;
            cout<<endl;
        }

        getLanczosDiagonalElement( i );
    }

    if( lana.size() < 4 ) lanStatus = 'B';
    else lanStatus = 'F';

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

    size_t startIndex = lana.size();
    for(size_t i = startIndex; i < endIndex; ++i)
    {
        getLanczosOffdiagonalElement( 3 );

        if( abs( lanb.back() ) < accuracy ) { lanb.pop_back(); return 0; }

        if( abs( lanb.back() ) < litForProjection )
        {
            cout<<setprecision(16)<<"\nSmall b "<<lanb.back()<<", try to stabilize new wave function:"<<endl;
            double nrm2 = projectWaveFunction( 3 );
            cout<<"After projection, the normalized factor is "<<nrm2<<endl;
            cout<<endl;
        }

        recurseWaveFunctions();

        getLanczosDiagonalElement( 2 );
    }

    lanStatus = 'R';

    return 1;
}

void Lanczos::getNewLanwfsZero(const vector<double> &vec, double litForProjection, char wfFlag)
{
    if( wfFlag == 'F' ) getNewLanwfsZeroFull(vec);
    if( wfFlag == 'R' ) getNewLanwfsZeroRecurse(vec, litForProjection);
}

void Lanczos::getNewLanwfsZeroFull(const vector<double> &vec)
{
    if( lana.size() != vec.size() ) { cout<<"Error!!! vec size is different with lana size!"<<endl; exit(1); }

    lanwfs[0].scale( vec[0] );
    for(size_t i = 1; i < vec.size(); ++i)
    {
        lanwfs[0].addEqual( vec[i], lanwfs[i] );
    }
    initLanczosMatrixFromLanwfsZero();
}


void Lanczos::getNewLanwfsZeroRecurse(const vector<double> &vec, double litForProjection)
{
    if( vec.size() < 4 ) { getNewLanwfsZeroFull(vec); return; }

    if( lana.size() != vec.size() ) { cout<<"Error!!! vec size is different with lana size!"<<endl; exit(1); }

    getNewLanwfsZeroRecurseZeroToThree(vec, litForProjection);

    getNewLanwfsZeroRecurseThreeToMatrixSize(vec, litForProjection);

    initLanczosMatrixFromLanwfsZero();
}

void Lanczos::getNewLanwfsZeroRecurseZeroToThree(const vector<double> &vec, double litForProjection)
{
    double currentb;

    getLanczosHtoWf( 1 );

    lanwfs[0].scale( vec[0] );

    for(size_t i = 1; i < 3; ++i)
    {
        currentb = getLanczosOrthonormalWf( i, lana[i-1], lanb[i-1] );

        if( abs( lanb[i] - currentb ) > 1e-12 )
        {
            cout<<"Error, Lanczos off diagonal element is not consistent!"<<endl;
            exit(1);
        }

        if( abs( lanb[i] ) < litForProjection ) projectWaveFunction( i );

        lanwfs[0].addEqual( vec[i], lanwfs[i] );

        getLanczosHtoWf( i+1 );
    }
}

void Lanczos::getNewLanwfsZeroRecurseThreeToMatrixSize(const vector<double> &vec, double litForProjection)
{
    double currentb;

    for(size_t i = 3; i < vec.size(); ++i)
    {
        currentb = getLanczosOrthonormalWf( 3, lana[i-1], lanb[i-1] );

        if( abs( lanb[i] - currentb ) > 1e-12 )
        {
            cout<<"Error, Lanczos off diagonal element is not consistent!"<<endl;
            exit(1);
        }

        if( abs( lanb[i] ) < litForProjection ) projectWaveFunction( 3 );

        lanwfs[0].addEqual( vec[i], lanwfs[3] );

        recurseWaveFunctions();

        if( i != ( vec.size()-1 )  ) getLanczosHtoWf( 3 );
    }
}