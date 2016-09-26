#include "../../../libhao/test_hao/gtest_custom.h"
#include "../include/LanczosBasisWf.h"

using namespace std;
using namespace tensor_hao;

class LanczosBasisWfTest: public ::testing::Test
{
 public:
    const int L = 10;
    TensorHao<complex<double>, 1> vec;
    LanczosBasisWfTest( )
    {
        vec = TensorHao<complex<double>,1 > (L);
        randomFill(vec);
    }

    ~LanczosBasisWfTest( )
    {
    }
};

TEST_F(LanczosBasisWfTest, LConstructor)
{
    LanczosBasisWf wf(L);
    EXPECT_EQ( L, wf.getWf().size() );
}

TEST_F(LanczosBasisWfTest, matrixCopyConstructor)
{
    LanczosBasisWf wf(vec);
    EXPECT_FALSE( diff( vec, wf.getWf(), 1e-12 ) );
}

TEST_F(LanczosBasisWfTest, matrixMoveConstructor)
{
    TensorHao<complex<double>, 1> vecTemp(vec);
    LanczosBasisWf wf(move(vecTemp));
    EXPECT_FALSE( diff( vec, wf.getWf(), 1e-12 ) );
    EXPECT_FALSE( vecTemp.data() );
}

TEST_F(LanczosBasisWfTest, copyConstructor)
{
    LanczosBasisWf wfBase(vec);
    LanczosBasisWf wf(wfBase);
    EXPECT_FALSE( diff( vec, wf.getWf(), 1e-12 ) );
}

TEST_F(LanczosBasisWfTest, moveConstructor)
{
    LanczosBasisWf wfBase(vec);
    LanczosBasisWf wf( move(wfBase) );
    EXPECT_FALSE( diff( vec, wf.getWf(), 1e-12 ) );
    EXPECT_FALSE( wfBase.getWf().data() );
}

TEST_F(LanczosBasisWfTest, copyAssignment)
{
    LanczosBasisWf wfBase(vec);
    LanczosBasisWf wf; wf = wfBase;
    EXPECT_FALSE( diff( vec, wf.getWf(), 1e-12 ) );
}

TEST_F(LanczosBasisWfTest, moveAssignment)
{
    LanczosBasisWf wfBase(vec);
    LanczosBasisWf wf; wf = move(wfBase);
    EXPECT_FALSE( diff( vec, wf.getWf(), 1e-12 ) );
    EXPECT_FALSE( wfBase.getWf().data() );
}

TEST_F(LanczosBasisWfTest, normalize)
{
    LanczosBasisWf wf(vec);
    wf.normalize();

    TensorHao<complex<double>, 1> vecNorm(L);
    complex<double> norm(0,0);
    for(int i = 0; i < L; ++i) norm += std::norm( vec(i) );
    norm = 1.0 / sqrt(norm);
    for(int i = 0; i < L; ++i) vecNorm(i) = vec(i) * norm;

    EXPECT_FALSE( diff(vecNorm, wf.getWf(), 1e-12) );
}
