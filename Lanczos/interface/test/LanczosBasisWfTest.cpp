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
    complex<double> inverseNorm(0,0);
    for(int i = 0; i < L; ++i) inverseNorm += std::norm( vec(i) );
    inverseNorm = 1.0 / sqrt(inverseNorm);
    for(int i = 0; i < L; ++i) vecNorm(i) = vec(i) * inverseNorm;

    EXPECT_FALSE( diff(vecNorm, wf.getWf(), 1e-12) );
}

TEST_F(LanczosBasisWfTest, overlap)
{
    TensorHao<complex<double>, 1> vecRightSide(L); randomFill(vecRightSide);
    LanczosBasisWf wfLeft(vec), wfRight(vecRightSide);
    complex<double> overlap = wfLeft.calculateOverlapWith(wfRight);
    complex<double> overlap_exact;
    for(int i = 0; i < L; ++i)
    {
        overlap_exact += conj( vec(i) ) * vecRightSide(i);
    }
    EXPECT_COMPLEXDOUBLE_EQ(overlap_exact, overlap);
}

TEST_F(LanczosBasisWfTest, orthogonal)
{
    TensorHao<complex<double>, 1> vecBase(L); randomFill(vecBase);
    LanczosBasisWf wf(vec), wfBase(vecBase);

    complex<double> overlap = wfBase.calculateOverlapWith(wf);
    TensorHao<complex<double>, 1> vecOrthogonal(L);
    for(int i = 0; i < L; ++i)
    {
        vecOrthogonal(i) = vec(i) - overlap * vecBase(i);
    }

    wf.orthogonalizeWith(wfBase);

    EXPECT_FALSE( diff(vecOrthogonal, wf.getWf(), 1e-12) );
}