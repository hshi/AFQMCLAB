#include "../../../common/testHao/gtest_custom.h"
#include "../include/LanczosBasisWf.h"

using namespace std;
using namespace tensor_hao;

class LanczosBasisWfTest: public ::testing::Test
{
 public:
    const size_t L = 10;
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

TEST_F(LanczosBasisWfTest, matrixCopyAssignment)
{
    LanczosBasisWf wf; wf =vec;
    EXPECT_FALSE( diff( vec, wf.getWf(), 1e-12 ) );
}

TEST_F(LanczosBasisWfTest, matrixMoveAssignment)
{
    TensorHao<complex<double>, 1> vecTemp(vec);
    LanczosBasisWf wf; wf = move(vecTemp);
    EXPECT_FALSE( diff( vec, wf.getWf(), 1e-12 ) );
    EXPECT_FALSE( vecTemp.data() );
}

TEST_F(LanczosBasisWfTest, scaleCopyAssignment)
{
    TensorHao<complex<double>, 1> vecScale(L);
    vecScale = complex<double>(2.0, 3.0);

    LanczosBasisWf wf(L); wf = complex<double>(2.0, 3.0);
    EXPECT_FALSE( diff( vecScale, wf.getWf(), 1e-12 ) );
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

TEST_F(LanczosBasisWfTest, scale)
{
    LanczosBasisWf wf(vec);
    complex<double> alpha(2.0, 3.0);
    wf.scale(alpha);

    TensorHao<complex<double>, 1> vecExpect = alpha * vec;

    EXPECT_FALSE( diff( vecExpect, wf.getWf(), 1e-12) );
}

TEST_F(LanczosBasisWfTest, addEqual)
{
    TensorHao<complex<double>, 1> vecAdd(L); randomFill(vecAdd);
    LanczosBasisWf wf(vec), wfAdd(vecAdd);

    complex<double> alpha(2.0, 3.0);
    TensorHao<complex<double>, 1> wfNew(L);
    for(size_t i = 0; i < L; ++i)
    {
        wfNew(i) = vec(i) + alpha * vecAdd(i);
    }

    wf.addEqual(alpha, wfAdd);

    EXPECT_FALSE( diff(wfNew, wf.getWf(), 1e-12) );
}

TEST_F(LanczosBasisWfTest, overlap)
{
    TensorHao<complex<double>, 1> vecRightSide(L); randomFill(vecRightSide);
    LanczosBasisWf wfLeft(vec), wfRight(vecRightSide);
    complex<double> overlap = wfLeft.calculateOverlapWith(wfRight);
    complex<double> overlap_exact;
    for(size_t i = 0; i < L; ++i)
    {
        overlap_exact += conj( vec(i) ) * vecRightSide(i);
    }
    EXPECT_COMPLEX_NEAR(overlap_exact, overlap, 1e-11);
}

TEST_F(LanczosBasisWfTest, orthogonalizeWith)
{
    TensorHao<complex<double>, 1> vecBase(L); randomFill(vecBase);
    LanczosBasisWf wf(vec), wfBase(vecBase);

    wfBase.normalize();
    wf.orthogonalizeWith(wfBase);

    complex<double> overlapExpect(0.0, 0.0);
    complex<double> overlapActual = wf.calculateOverlapWith(wfBase);
    EXPECT_COMPLEX_NEAR( overlapExpect, overlapActual, 1e-12);
}

TEST_F(LanczosBasisWfTest, normalize)
{
    LanczosBasisWf wf(vec);

    double nrm2Expect = sqrt( wf.calculateOverlapWith(wf) ).real();
    double nrm2Actual = wf.normalize();
    EXPECT_DOUBLE_EQ( nrm2Expect, nrm2Actual );

    complex<double> overlapExpect(1.0, 0.0);
    complex<double> overlapActual = wf.calculateOverlapWith(wf);
    EXPECT_COMPLEX_NEAR( overlapExpect, overlapActual, 1e-12);
}

TEST_F(LanczosBasisWfTest, orthonormalizeWith)
{
    TensorHao<complex<double>, 1> vecBase(L); randomFill(vecBase);
    LanczosBasisWf wf(vec), wfBase(vecBase);

    wfBase.normalize();
    wf.orthonormalizeWith(wfBase);

    complex<double> overlapExpect(0.0, 0.0);
    complex<double> overlapActual = wf.calculateOverlapWith(wfBase);
    EXPECT_COMPLEX_NEAR( overlapExpect, overlapActual, 1e-12);

    overlapExpect = 1.0;
    overlapActual = wf.calculateOverlapWith(wf);
    EXPECT_COMPLEX_NEAR( overlapExpect, overlapActual, 1e-12);
}


TEST_F(LanczosBasisWfTest, writeAndRead)
{
    string filename = "wf.dat";
    LanczosBasisWf wf(vec), wfp(L);
    wf.write(filename);
    wfp.read(filename);
    EXPECT_FALSE( diff( wf.getWf(), wfp.getWf(), 1e-12 ) );
    if(MPIRank()==0) remove( filename.c_str() );
}