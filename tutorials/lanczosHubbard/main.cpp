#include "afqmclab.h"
#include "measureDynamicParam.h"

using namespace std;
using namespace tensor_hao;

void lanczosRealMaterial();
void measureStatic(Lanczos &lan, RealMaterial& H);
void measureDynamicCreateToWf(Lanczos &lan, RealMaterial& H, const DynamicParams& dynamicParams);
void measureDynamicDestroyToWf(Lanczos &lan, RealMaterial& H, const DynamicParams& dynamicParams);
void measureDynamicDensityToWf(Lanczos &lan, RealMaterial& H, const DynamicParams& dynamicParams);

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

//        lan.readEigens();
    }
    catch ( exception& e)
    {
        cout << "Standard exception: " << e.what() << endl;
        lan.writeEigens();
        lan.writeLanWavefunction("lanwfs0.dat");
    }

    lan.writeEigens();

    measureStatic(lan, H);

    DynamicParams dynamicParams;
    dynamicParams.matrixSize = 100;
    dynamicParams.accuracy = lanParam.accuracy;
    dynamicParams.litForProjection = lanParam.litForProjection;
    dynamicParams.lanwfsFlag = 'R';

    measureDynamicCreateToWf(lan, H, dynamicParams);

    measureDynamicDestroyToWf(lan, H, dynamicParams);

    measureDynamicDensityToWf(lan, H, dynamicParams);
}