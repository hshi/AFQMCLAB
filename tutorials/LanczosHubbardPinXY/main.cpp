#include "afqmc.h"

using namespace std;
using namespace tensor_hao;

void measure(Lanczos &lan, SpinlessFermions& H)
{
    size_t L = H.getL() / 2;
    const LanczosBasisWf & phi0 = lan.getEigenstate(0);
    LanczosBasisWf & phip = lan.getLanWavefunction(0);

    vector< complex<double> > greens(L);
    for(size_t i = 0; i < L; ++i)
    {
        H.applyCiDaggerCjToWf(phi0, phip, i, i+L);
        greens[i] = phi0.calculateOverlapWith(phip);
        cout<<greens[i]<<endl;
    }

    complex<double> Nup(0,0);
    for(size_t i = 0; i < L; ++i)
    {
        H.applyCiDaggerCjToWf(phi0, phip, i, i);
        Nup += phi0.calculateOverlapWith(phip);
    }
    cout<<"Nup: "<<Nup<<endl;
}

void findEigenOfSpinlessFermin()
{
    SpinlessFermions H("model_param");
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

    measure(lan, H);
}

int main(int argc, char** argv)
{
    MPIInitFunnel(argc,argv);

#ifdef USE_MAGMA
    magma_init();
#endif

    findEigenOfSpinlessFermin();

#ifdef USE_MAGMA
    magma_finalize();
#endif

    MPIFinalize();
    return 0;
}