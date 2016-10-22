//
// Created by boruoshihao on 10/20/16.
//
#include "../include/Lanczos.h"

using namespace tensor_hao;

using namespace std;

void Lanczos::prepareLanReturn( char defaultStatus )
{
    lanb.pop_back();
    lanStatus = ( lana.size() < 4 ) ? 'B' : defaultStatus ;
}

void Lanczos::projectWaveFunctionUpdateLanb(size_t lanwfsIndex)
{
    cout << "\nSmall b " << lanb.back() << ", try to stabilize new wave function:" << endl;
    double nrm2 = projectWaveFunction( lanwfsIndex );
    cout<<"After projection, the normalized factor is "<<nrm2<<endl;
    cout<<endl;

    lanb.back() *= nrm2;
}

double Lanczos::projectWaveFunction(size_t lanwfsIndex)
{
    LanczosBasisWf &wf = lanwfs[lanwfsIndex];

    for(size_t i = 0; i < eigenstates.size(); ++i)
    {
        wf.orthogonalizeWith( eigenstates[i] );
    }

    for(size_t i = 0; i < lanwfsIndex; ++i)
    {
        wf.orthogonalizeWith( lanwfs[i] );
    }

    model->projectSymmetry( wf );

    return wf.normalize();
}

void Lanczos::saveToEigen()
{
    cout<<setprecision(16)<<"\nSUCCESS! Find Eigenstate #" << eigenstates.size() <<" : "<<lana[0]<<"\n"<<endl;
    lanStatus = 'N';
    eigenvalues.push_back( lana[0] );
    eigenstates.push_back( move(lanwfs[0]) );
    lanwfs[0] = LanczosBasisWf();
}

void Lanczos::changeLanStatusToRecurse()
{
    if( lanStatus=='N' ) { cout<<"Error!!! lanStatus is None, can not transfer to Recurse!"<<endl; exit(1); }
    if( lanStatus=='B' || lanStatus=='R' ) return;

    if( lanStatus!='F' ) { cout<<"Error!!! lanStatus is not Full!"<<endl; exit(1); }
    size_t L = lana.size();
    if( L < 4 ) { lanStatus = 'B'; return; }

    lanwfs[3] = move( lanwfs[L]   );
    lanwfs[2] = move( lanwfs[L-1] );
    lanwfs[1] = move( lanwfs[L-2] );
    lanwfs.resize(4);
    lanStatus = 'R';
}

void Lanczos::recurseWaveFunctions()
{
    LanczosBasisWf wfTemp = move( lanwfs[1] );
    lanwfs[1] = move( lanwfs[2] );
    lanwfs[2] = move( lanwfs[3] );
    lanwfs[3] = move( wfTemp    );
}

void Lanczos::getLanczosHtoWf(size_t i)
{
    if( lanwfs.size() < (i+1) ) lanwfs.resize(i+1);
    model->applyHToWf( lanwfs[i-1], lanwfs[i] );
}

double Lanczos::getLanczosOrthonormalWf(size_t i, double a, double b)
{
    lanwfs[i].addEqual( -a, lanwfs[i-1] );
    if( abs( b ) > 1e-100 ) lanwfs[i].addEqual( -b,  lanwfs[i-2] );
    return lanwfs[i].normalize();
}

void Lanczos::getLanczosDiagonalElement(size_t i)
{
    getLanczosHtoWf(i+1);
    complex<double> a = lanwfs[i+1].calculateOverlapWith(lanwfs[i]);
    lana.push_back( a.real() );
}

void Lanczos::getLanczosOffdiagonalElement(size_t i)
{
    double offDiag = getLanczosOrthonormalWf( i, lana.back(), lanb.back() );
    lanb.push_back( offDiag );
}

tuple<double, vector<double> > diagonalizeLanczosMatrix(vector<double> a, vector<double> b)
{
    if( a.size()  != b.size() )
    {
        cerr<<"Lanczos a and b size is not consistent in Lanczos::diagonalizeLanczosMatrix!"<<endl;
        exit(1);
    }

    HAO_INT L = a.size();
    HAO_INT lwork = 2*L -2; if( lwork < 1 ) lwork = 1;
    vector<double> work(lwork);
    vector<double> fullvector(L*L);
    char compz = 'I'; HAO_INT info;
    dsteqr( &compz , &L, a.data() , b.data()+1 , fullvector.data() , &L , work.data() , &info );
    if( info != 0 )
    {
        cerr<<"Dsteqr in Lanczos::diagonalizeLanczosMatrix does not execute well "<<info<<endl;
        exit(1);
    }

    double  lowestValue = a[0];
    vector<double> lowestVector(L);
    copy( fullvector.data(), fullvector.data()+L, lowestVector.data() );

    return make_tuple( lowestValue,  move( lowestVector ) );
}

Lanczos::Lanczos(const Lanczos& x)  {};

Lanczos & Lanczos::operator  = (const Lanczos& x) { return *this; }
