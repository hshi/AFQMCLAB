#include "../../../libhao/test_hao/gtest_custom.h"
#include "../../interface/include/Lanczos.h"
#include "fullMatrix.h"

using namespace std;

using namespace tensor_hao;

class lanczosModelFullMatrixTest: public ::testing::Test
{
 public:
    const size_t L = 30;
    TensorHao<complex<double>, 2> Hm;
    TensorHao<complex<double>, 1> Hv, Hvp;
    lanczosModelFullMatrixTest( )
    {
        Hm.resize(L,L); randomFill(Hm);
        Hv.resize(L); randomFill(Hv);
        Hvp.resize(L); Hvp = complex<double>(0,0);
        for(size_t i = 0; i < L; ++i)
        {
            for(size_t j = 0; j < L; ++j)
            {
                Hvp(i) += Hm(i,j) * Hv(j);
            }
        }
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
    FullMatrix fm( Hm ); fm.write("fullMatrix.dat");
    FullMatrix fmNew; fmNew.read("fullMatrix.dat");
    EXPECT_FALSE( diff( fm.getHm(), fmNew.getHm(), 1e-12 ) );
}

TEST_F(lanczosModelFullMatrixTest, applyHToWf)
{
    FullMatrix fm( Hm );
    LanczosBasisWf wf( Hv ), wfp;

    fm.applyHToWf(wf, wfp);

    EXPECT_FALSE( diff( Hvp, wfp.getWf(), 1e-12 ) );
}

TEST_F(lanczosModelFullMatrixTest, lanczos)
{
    TensorHao<complex<double>, 2> matrix(L, L);
    randomFill(matrix); matrix += conjtrans( matrix );

    TensorHao<complex<double>, 2> vector(matrix);
    TensorHao<double, 1> value(L);
    eigen_cpu(vector, value);

    FullMatrix fm(matrix); Lanczos lan( fm );
    lan.findEigen(1);

    EXPECT_NEAR( value(0), lan.getEigenvalue(0), 1e-10 );
}