#include "afqmc.h"

using namespace std;
using namespace tensor_hao;

void findEigenOfSpinlessFermin()
{
    SpinlessFermions H("model_param");
    Lanczos lan(H);
    try
    {
        lan.findEigen(1, {20, 1e-10, 'E', 100, 0.01, 'F'});
//        lan.readWfInit("lanwfs0.dat");
//        lan.FindOneEigen( {20, 1e-10, 'E', 100, 0.01, 'F'} );
    }
    catch ( exception& e)
    {
        cout << "Standard exception: " << e.what() << endl;
        lan.writeEigens();
        lan.writeLanWavefunction("lanwfs0.dat");
    }
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