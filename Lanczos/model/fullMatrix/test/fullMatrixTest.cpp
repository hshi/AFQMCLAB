#include "../../../../common/testHao/gtest_custom.h"
#include "../../../interface/include/LanczosInterface.h"
#include "../include/fullMatrix.h"

using namespace std;
using namespace tensor_hao;

class lanczosModelFullMatrixTest: public ::testing::Test
{
 public:
    const size_t L = 30;
    TensorHao<complex<double>, 2> Hm, Hv;
    TensorHao<double, 1> Hd;
    lanczosModelFullMatrixTest( )
    {
        Hm.resize(L,L);
        randomFill(Hm);
        Hm += conjtrans( Hm );

        Hv = Hm;
        Hd.resize(L);
        eigen_cpu(Hv, Hd);
    }

    ~lanczosModelFullMatrixTest( )
    {
    }
};

TEST_F(lanczosModelFullMatrixTest, copyConstructor)
{
    FullMatrix fm( Hm );

    EXPECT_FALSE( diff( fm.getHm(), Hm, 1e-12 ) );
    EXPECT_EQ( L, fm.getWfSize() );
}

TEST_F(lanczosModelFullMatrixTest, moveConstructor)
{
    TensorHao<complex<double>, 2> HmTemp( Hm );

    FullMatrix fm( move(HmTemp) );

    EXPECT_FALSE( diff( fm.getHm(), Hm, 1e-12 ) );
    EXPECT_EQ( L, fm.getWfSize() );
    EXPECT_FALSE( HmTemp.data() );
}

TEST_F(lanczosModelFullMatrixTest, readWrite)
{
    string filename = "fullMatrix.dat";
    FullMatrix fm( Hm ); fm.write(filename);
    FullMatrix fmNew(filename);
    EXPECT_FALSE( diff( fm.getHm(), fmNew.getHm(), 1e-12 ) );
    remove( filename.c_str() );
}

TEST_F(lanczosModelFullMatrixTest, lanczos)
{
    FullMatrix fm( Hm ); Lanczos lan( fm );
    lan.findEigen(1);

    EXPECT_NEAR( Hd(0), lan.getEigenvalue(0), 1e-10 );
}