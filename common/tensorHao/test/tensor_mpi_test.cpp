#include "../include/tensor_mpi.h"
#include "../../testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(Tensor_mpi, MPIBcast_double)
{
    TensorHao<double,1> A, A_exact(4);

    A_exact = {14.861,12.630129,20.984,23.753129};

    if( MPIRank() == 0 ) A = A_exact;

    MPIBcast(A);
    EXPECT_FALSE( diff(A,A_exact,1e-12) );
}

TEST(Tensor_mpi, MPIBcast_complex_double)
{
    TensorHao<complex<double>, 2> A, A_exact(2, 2);

    A_exact = {{-13.769,    40.877},
               {-16.551971, 38.73806},
               {-17.756,    56.71},
               {-22.838971, 66.77106}};

    if (MPIRank() == 0) A = A_exact;

    MPIBcast(A);

    EXPECT_FALSE( diff(A, A_exact, 1e-12) );
}

TEST(Tensor_mpi, MPIBcast_complex_double_Ref)
{
    TensorHao<complex<double>, 2>  Ap(2, 2), A_exact(2, 2);
    TensorHaoRef<complex<double>, 2> A( Ap );

    A_exact = {{-13.769,    40.877},
               {-16.551971, 38.73806},
               {-17.756,    56.71},
               {-22.838971, 66.77106}};

    if (MPIRank() == 0) A = A_exact;

    MPIBcast(A);

    EXPECT_FALSE( diff(A, A_exact, 1e-12) );
}