#include "afqmc.h"

using namespace std;
using namespace tensor_hao;

void findEigenOfRealMaterial()
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
}

int main(int argc, char** argv)
{
    MPIInitFunnel(argc,argv);

#ifdef USE_MAGMA
    magma_init();
#endif

    findEigenOfRealMaterial();

#ifdef USE_MAGMA
    magma_finalize();
#endif

    MPIFinalize();
    return 0;
}