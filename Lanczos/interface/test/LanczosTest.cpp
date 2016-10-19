//
// Created by boruoshihao on 9/24/16.
//
#include "../../../libhao/test_hao/gtest_custom.h"
#include "../include/Lanczos.h"
#include "../include/modelInterface.h"

using namespace std;
using namespace tensor_hao;

class Hmatrix : public ModelInterface
{
    TensorHao<complex<double>, 2> Hm;
 public:

    const TensorHao<complex<double>, 2> &getHm() const
    {
        return Hm;
    }

    void resize(size_t L)
    {
        Hm.resize(L, L);
        randomFill(Hm);
        auto HmDagger = conjtrans(Hm);
        Hm += HmDagger;
        checkHermitian(Hm);
    }

    virtual size_t getWfSize() const
    {
        return Hm.rank(0);
    };

    virtual void applyHToWf(const LanczosBasisWf &wf, LanczosBasisWf &wfNew) const
    {
        if( wfNew.size() != wf.size() ) wfNew.resize( wf.size() );
        gemv_cpu( Hm, wf.getWf(), wfNew.wfRef() );
    };

    virtual void projectSymmetry(LanczosBasisWf &wf) const
    {
    };
};


class LanczosTest: public ::testing::Test
{
 public:
    const size_t L = 30;
    Hmatrix hmatrix;
    TensorHao<double,1> he;
    TensorHao<complex<double>,2> hv;
    LanczosTest( )
    {
        hmatrix.resize(L);
        he.resize(L);
        hv = hmatrix.getHm();
        eigen_cpu( hv, he);
    }

    ~LanczosTest( )
    {
    }
};

TEST_F(LanczosTest, findEigen)
{
    cout<<he<<endl;
    Lanczos lanczos(hmatrix);
    lanczos.findEigen(5);
}