#include "gtest/gtest.h"

#ifdef MPI_HAO
#include <mpi.h>
#endif

#ifdef USE_MAGMA
#include "magma.h"
#endif

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

#ifdef MPI_HAO
    MPI_Init(&argc,&argv);
#endif

#ifdef USE_MAGMA
    magma_init();
#endif


    int result = RUN_ALL_TESTS();

#ifdef USE_MAGMA
    magma_finalize();
#endif

#ifdef MPI_HAO
    MPI_Finalize();
#endif

    return result;
}
