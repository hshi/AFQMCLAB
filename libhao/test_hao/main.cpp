#include "gtest/gtest.h"

#ifdef MPI_HAO
#include <mpi.h>
#endif

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

#ifdef MPI_HAO
    MPI_Init(&argc,&argv);
#endif

    int result = RUN_ALL_TESTS();

#ifdef MPI_HAO
    MPI_Finalize();
#endif

    return result;
}
