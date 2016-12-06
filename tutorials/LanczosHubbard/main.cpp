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

    TimerHao timer;
    timer.start(); if(MPIRank()==0) {cout<<"\nStart time:\n";timer.printCurrentTime();}

#ifdef USE_MAGMA
    magma_init();
#endif

    findEigenOfRealMaterial();

#ifdef USE_MAGMA
    magma_finalize();
#endif

    timer.end(); if(MPIRank()==0) {cout<<"\n\nEnd time:\n";timer.printCurrentTime();}
    if(MPIRank()==0) {cout<<"The program's running walltime is:\n"; timer.printFormat();}

    MPIFinalize();
    return 0;
}