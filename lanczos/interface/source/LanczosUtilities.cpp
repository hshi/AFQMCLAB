//
// Created by boruoshihao on 10/20/16.
//
#include "../include/LanczosInterface.h"

using namespace tensor_hao;

using namespace std;

void Lanczos::prepareLanReturn(string defaultStatus)
{
    lanb.pop_back();

    if( lana.size() < 4 )
    {
        lanStatus = "bothConverged";
    }
    else
    {
        if ( defaultStatus == string("full")  ) lanStatus = "fullConverged";
        else if( defaultStatus == string("recurse")  )  lanStatus = "recurseConverged";
        else { cout<<"Unexpect defaultStatus! "<<defaultStatus<<endl; exit(1); }
    }
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
    lanStatus = "none";
    eigenvalues.push_back( lana[0] );
    eigenstates.push_back( move(lanwfs[0]) );
    lanwfs[0] = LanczosBasisWf();
}

void Lanczos::checkConvergedStatusAndChangetoNoneConvergedStatus()
{
    if( lanStatus==string("bothConverged") || lanStatus==string("fullConverged") )
    {
        getLanczosHtoWf( lana.size() );
    }
    else if( lanStatus==string("recurseConverged") )
    {
        getLanczosHtoWf( 3 );
    }
    else
    {
        return;;
    }
}

void Lanczos::changeLanStatusToRecurse()
{
    if( lanStatus==string("none") )
    {
        cout<<"Error!!! lanStatus is none, can not transfer to Recurse!"<<endl;
        exit(1);
    }

    if( lanStatus==string("bothConverged") || lanStatus==string("fullConverged") || lanStatus==string("recurseConverged") )
    {
        cout<<"Error!!! lanStatus is *Converged, unexpected!!!"<<endl;
        exit(1);
    }

    if( lanStatus==string("both") || lanStatus== string("recurse") ) return;

    if( lanStatus!=string("full") ) { cout<<"Error!!! lanStatus is not full!"<<endl; exit(1); }

    size_t L = lana.size();
    if( L < 4 ) { lanStatus = "both"; return; }

    lanwfs[3] = move( lanwfs[L]   );
    lanwfs[2] = move( lanwfs[L-1] );
    lanwfs[1] = move( lanwfs[L-2] );
    lanwfs.resize(4);
    lanStatus = "recurse";
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
    if( abs( a.real() ) < 1e-10 )
    {
        if( abs( a.imag() ) > 1e-10 ) { cout<<"Error!!! The model is not Hermition!"<<endl; exit(1); }
    }
    else
    {
        if( abs( a.imag()/a.real() ) > 1e-10 ) { cout<<"Error!!! The model is not Hermition!"<<endl; exit(1); }

    }
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