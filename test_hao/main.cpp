#include "gtest/gtest.h"

#ifdef MPI_HAO
#include <mpi.h>
#endif

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    int rank=0;

#ifdef MPI_HAO
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#endif

    int result = RUN_ALL_TESTS();

#ifdef MPI_HAO
    MPI_Finalize();
#endif

    return result;
}
