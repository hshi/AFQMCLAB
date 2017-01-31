#include "afqmclab.h"

using namespace std;
using namespace tensor_hao;

void measureLogExpMinusTauModel(MeasureBasedOnLanMatrix &meas)
{
    TensorHao<double,1> tau(100);
    for(size_t j = 0; j < tau.size() ; ++j) tau(j) = 0.2*j;
    TensorHao<double,1> Gtau = meas.returnLogExpMinusTauModel(tau, 100);
    writeFile(tau.size(), tau.data(), Gtau.data(), "Gtau.dat" );
}

void measureMinusSpectralFunction(MeasureBasedOnLanMatrix &meas, double E0)
{
    TensorHao<complex<double>,1> omega(3000), EMinusOgema(3000);
    for(size_t j = 0; j < omega.size() ; ++j) omega(j) = complex<double>(0.02*j-30.0, 0.0);
    EMinusOgema = complex<double>(E0, 0.1) - omega;
    TensorHao<complex<double>,1> spectral = meas.returnGreenFunction(EMinusOgema, 100);
    writeFile(omega.size(), omega.data(), spectral.data(), "spectralMinus.dat" );
}

void measureDynamic(Lanczos &lan, RealMaterial& H)
{
    size_t i = 2;
    const LanczosBasisWf & phi0 = lan.getEigenstate(0);
    LanczosBasisWf CiupPhi0;

    vector<LanOneOperator> Cup(1); Cup[0] = { i, {1.0, 0.0} };
    H.applyCupToWf(phi0, CiupPhi0, Cup);

    RealMaterial HNupMinusOne = H.generateNewModel( H.getL(), H.getNup()-1, H.getNdn() );
    MeasureBasedOnLanMatrix meas( HNupMinusOne, CiupPhi0 );

    measureLogExpMinusTauModel( meas );
    measureMinusSpectralFunction( meas, lan.getEigenvalue(0) );
}

void measureStatic(Lanczos &lan, RealMaterial& H)
{
    size_t L = H.getL();
    const LanczosBasisWf & phi0 = lan.getEigenstate(0);
    LanczosBasisWf & phip = lan.getLanWavefunction(0);

    H.applyKToWf(phi0, phip);
    complex<double> K = phi0.calculateOverlapWith(phip);
    writeFile(K.real(), "K.dat");

    H.applyVToWf(phi0, phip);
    complex<double> V = phi0.calculateOverlapWith(phip);
    writeFile(V.real(), "V.dat");

    TensorHao<complex<double>, 1> SzSz(L);
    for(size_t i = 0; i < L; ++i)
    {
        H.applySziSzjToWf(phi0, phip, 0, i);
        SzSz(i) = phi0.calculateOverlapWith(phip);
    }
    writeFile(SzSz.size(), SzSz.data(), "SzSz.dat");

    TensorHao<complex<double>, 1> SS(L);
    for(size_t i = 0; i < L; ++i)
    {
        H.applySiSjToWf(phi0, phip, 0, i);
        SS(i) = phi0.calculateOverlapWith(phip);
    }
    writeFile(SS.size(), SS.data(), "SS.dat");

    TensorHao<complex<double>, 1> NN(L);
    for(size_t i = 0; i < L; ++i)
    {
        H.applyNiNjToWf(phi0, phip, 0, i);
        NN(i) = phi0.calculateOverlapWith(phip);
    }
    writeFile(NN.size(), NN.data(), "NN.dat");

    TensorHao<complex<double>, 1> DD(L);
    for(size_t i = 0; i < L; ++i)
    {
        H.applyDiDaggerDjToWf(phi0, phip, 0, i);
        DD(i) = phi0.calculateOverlapWith(phip);
    }
    writeFile(DD.size(), DD.data(), "DD.dat");
}

void lanczosRealMaterial()
{
    RealMaterial H("model_param");
    LanczosParam lanParam; lanParam.read("lanczos_param");
    Lanczos lan(H);
    try
    {
        lan.findEigen(1, lanParam);
//        lan.readWfInit("lanwfs0.dat");
//        lan.FindOneEigen( lanParam );
    }
    catch ( exception& e)
    {
        cout << "Standard exception: " << e.what() << endl;
        lan.writeEigens();
        lan.writeLanWavefunction("lanwfs0.dat");
    }

    measureStatic(lan, H);
    measureDynamic(lan, H);
}

int main(int argc, char** argv)
{
    MPIInit(argc,argv);

    TimerHao timer;
    timer.start(); if(MPIRank()==0) {cout<<"\nStart time:\n";timer.printCurrentTime();}

#ifdef USE_MAGMA
    magma_init();
#endif

    lanczosRealMaterial();

#ifdef USE_MAGMA
    magma_finalize();
#endif

    timer.end(); if(MPIRank()==0) {cout<<"\n\nEnd time:\n";timer.printCurrentTime();}
    if(MPIRank()==0) {cout<<"The program's running walltime is:\n"; timer.printFormat();}

    MPIFinalize();
    return 0;
}
