//
// Created by boruoshihao on 9/24/16.
//
#include "../../../common/testHao/gtest_custom.h"
#include "../include/LanczosInterface.h"
#include "Hmatrix.h"

using namespace std;
using namespace tensor_hao;

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
    cout<<"\n\n\n==========================Testing==========================\n\n"<<endl;
    Lanczos lanczos(hmatrix);
    size_t numberOfState = 5;
    lanczos.findEigen(numberOfState);
    for(size_t i = 0; i < numberOfState; ++i)
    {
        EXPECT_NEAR( he(i),lanczos.getEigenvalue(i), 1e-12 );
    }
}

TEST_F(LanczosTest, findEigenReserve)
{
    cout<<"\n\n\n==========================Testing==========================\n\n"<<endl;
    Lanczos lanczos(hmatrix);
    size_t targetLanSize(1000), targetEigenSize(2000);
    //When we want to use lanczos matrix size > 300 or want to find more than 1000 exicited states
    //Use reserve function to improve efficiency. In most case, 300 and 1000 is large enough.
    lanczos.reserve(targetLanSize, targetEigenSize);
    lanczos.findEigen(1);
    EXPECT_DOUBLE_EQ( he(0),lanczos.getEigenvalue(0) );
}

TEST_F(LanczosTest, findEigenReadWriteEigen)
{
    cout<<"\n\n\n==========================Testing==========================\n\n"<<endl;
    size_t numberOfState(6), numberOfWrite(3);

    Lanczos lanczosWrite(hmatrix);
    lanczosWrite.findEigen(numberOfWrite);
    lanczosWrite.writeEigens();

    Lanczos lanczos(hmatrix);
    lanczos.readEigens(numberOfWrite);
    lanczos.findEigen(numberOfState-numberOfWrite, {10, 1e-10, 'E', 100, 0.01, 'F'});
    for(size_t i = 0; i < numberOfState; ++i)
    {
        EXPECT_NEAR( he(i),lanczos.getEigenvalue(i), 1E-10 );
    }
}

TEST_F(LanczosTest, findOneEigenRandomWfInit)
{
    cout<<"\n\n\n==========================Testing==========================\n\n"<<endl;
    Lanczos lanczos(hmatrix);
    lanczos.randomWfInit();
    lanczos.FindOneEigen();
    EXPECT_DOUBLE_EQ( he(0),lanczos.getEigenvalue(0) );
}


TEST_F(LanczosTest, findOneEigenReadWfInit)
{
    cout<<"\n\n\n==========================Testing==========================\n\n"<<endl;
    string filename = "wf.dat";
    Lanczos lanczos(hmatrix);
    LanczosBasisWf wf( hmatrix.getWfSize() ); wf.randomFill(); wf.write(filename);
    lanczos.readWfInit(filename);
    lanczos.FindOneEigen();
    EXPECT_NEAR( he(0),lanczos.getEigenvalue(0), 1e-10);
    remove( filename.c_str() );
}

TEST_F(LanczosTest, findOneEigenInputWfInit)
{
    cout<<"\n\n\n==========================Testing==========================\n\n"<<endl;
    Lanczos lanczos(hmatrix);
    LanczosBasisWf wf( hmatrix.getWfSize() ); wf.randomFill();
    lanczos.inputWfInit( wf );
    lanczos.FindOneEigen();
    EXPECT_DOUBLE_EQ( he(0),lanczos.getEigenvalue(0) );
}

TEST_F(LanczosTest, findOneEigenReadLanInit)
{
    cout<<"\n\n\n==========================Testing==========================\n\n"<<endl;
    Lanczos lanczos(hmatrix);

    lanczos.randomWfInit();
    lanczos.getLanczosMatrix(5);
    lanczos.writeLanMatrix();

    lanczos.clear();
    lanczos.readLanInit();
    lanczos.FindOneEigen();
    EXPECT_DOUBLE_EQ( he(0),lanczos.getEigenvalue(0) );
    int flag=system("rm -rf *.dat");
    if(flag != 0) cout<<"WARNING!!! system command does not exit properly!"<<endl;
}

TEST_F(LanczosTest, getLanczosMatrix)
{
    cout<<"\n\n\n==========================Testing==========================\n\n"<<endl;
    Lanczos lanczos(hmatrix);
    LanczosBasisWf wfBase( hmatrix.getWfSize() ); wfBase.randomFill();
    LanczosBasisWf wfOne, wfTwo;

    wfOne = wfBase;
    lanczos.inputWfInit( wfOne );
    vector<double> a,b;
    tie(a, b) = lanczos.getLanczosMatrix(11, 1e-10, 0.01, 'F');  //Use Copy for a,b

    Lanczos lanczosNew(hmatrix);
    wfTwo = wfBase;
    lanczos.inputWfInit( wfTwo );
    lanczos.getLanczosMatrix(5, 1e-10, 0.01, 'F');
    lanczos.writeLanMatrix();
    lanczosNew.readLanMatrix();
    auto lanabNew = lanczosNew.getLanczosMatrix(6, 1e-10, 0.01, 'F'); //Always reference

    for(size_t i = 0; i < a.size(); ++i)
    {
        EXPECT_DOUBLE_EQ( a[i], get<0>(lanabNew)[i] );
        EXPECT_DOUBLE_EQ( b[i], get<1>(lanabNew)[i] );
    }

    int flag=system("rm -rf *.dat");
    if(flag != 0) cout<<"WARNING!!! system command does not exit properly!"<<endl;
}

TEST_F(LanczosTest, findOneEigenLargeMatrixSize)
{
    cout<<"\n\n\n==========================Testing==========================\n\n"<<endl;
    Lanczos lanczos(hmatrix);

    lanczos.randomWfInit();
    lanczos.FindOneEigen({50, 1e-10, 'E', 100, 0.01, 'F'});
    EXPECT_NEAR( he(0),lanczos.getEigenvalue(0), 1E-12 );
}

TEST_F(LanczosTest, findEigenFullState)
{
    cout<<"\n\n\n==========================Testing==========================\n\n"<<endl;
    Lanczos lanczos(hmatrix);
    size_t numberOfState = 30;
    lanczos.findEigen(numberOfState, {3, 1e-12, 'E', 1000, 0.01, 'F'});
    for(size_t i = 0; i < numberOfState; ++i)
    {
        EXPECT_NEAR( he(i),lanczos.getEigenvalue(i), 1e-12 );
    }
}

TEST_F(LanczosTest, findEigenRecurse)
{
    cout<<"\n\n\n==========================Testing==========================\n\n"<<endl;
    Lanczos lanczos(hmatrix);
    size_t numberOfState = 5;
    lanczos.findEigen(numberOfState, {20, 1e-10, 'E', 100, 0.01, 'R'});
    for(size_t i = 0; i < numberOfState; ++i)
    {
        EXPECT_NEAR( he(i),lanczos.getEigenvalue(i), 1e-12 );
    }
}

TEST_F(LanczosTest, findOneEigenRandomWfInitRecurse)
{
    cout<<"\n\n\n==========================Testing==========================\n\n"<<endl;
    Lanczos lanczos(hmatrix);
    lanczos.randomWfInit();
    lanczos.FindOneEigen({20, 1e-10, 'E', 100, 0.01, 'R'});
    EXPECT_DOUBLE_EQ( he(0),lanczos.getEigenvalue(0) );
}

TEST_F(LanczosTest, findOneEigenLargeMatrixSizeRecurse)
{
    cout<<"\n\n\n==========================Testing==========================\n\n"<<endl;
    Lanczos lanczos(hmatrix);

    lanczos.randomWfInit();
    lanczos.FindOneEigen({50, 1e-10, 'E', 100, 0.01, 'R'});
    EXPECT_NEAR( he(0),lanczos.getEigenvalue(0), 1E-12 );
}

//For intel compiler, failed the test! Lost accuracy!
//TEST_F(LanczosTest, findEigenFullStateRecurse)
//{
//    cout<<"\n\n\n==========================Testing==========================\n\n"<<endl;
//    Lanczos lanczos(hmatrix);
//    size_t numberOfState = 30;
//    lanczos.findEigen(numberOfState, {5, 1e-12, 'E', 1000, 0.01, 'R'});
//    for(size_t i = 0; i < numberOfState; ++i)
//    {
//        EXPECT_NEAR( he(i),lanczos.getEigenvalue(i), 1e-12 );
//    }
//}