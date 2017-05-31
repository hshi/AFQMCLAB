#include <cmath>
#include "../include/tensor_hao.h"
#include "../include/tensor_mpi.h"
#include "../../testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(Tensor_hao_ref, void_construction)
{
    TensorHaoRef<double,2>  tensor_ref;

    for (size_t i = 0; i < 2; ++i)
    {
        EXPECT_EQ( static_cast<size_t>(0), tensor_ref.rank(i) );
        EXPECT_EQ( static_cast<size_t>(0), tensor_ref.rankStep(i) );
    }
    EXPECT_FALSE( tensor_ref.data() );
    EXPECT_EQ( static_cast<size_t>(0), tensor_ref.size() );
}

TEST(Tensor_hao_ref, variadic_construction)
{
    const size_t D=3;
    TensorHaoRef<double, D>  tensor_ref(3,4,7);
    size_t size=84;
    size_t n[D]={3,4,7};
    size_t n_step[D]={1,3,12};

    EXPECT_FALSE( tensor_ref.data() );
    EXPECT_EQ( size, tensor_ref.size() );
    for(size_t i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor_ref.rank(i) );
        EXPECT_EQ( n_step[i], tensor_ref.rankStep(i) );
    }
}

TEST(Tensor_hao_ref, pointer_construction)
{
    const size_t D=3;
    size_t n_ptr[D] = {3,4,7};
    TensorHaoRef<double, D>  tensor_ref(n_ptr);
    size_t size=84;
    size_t n[D]={3,4,7};
    size_t n_step[D]={1,3,12};

    EXPECT_FALSE( tensor_ref.data() );
    EXPECT_EQ( size, tensor_ref.size() );
    for(size_t i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor_ref.rank(i) );
        EXPECT_EQ( n_step[i], tensor_ref.rankStep(i) );
    }
}


TEST(Tensor_hao_ref, constructor_assginment)
{
    TensorHao<double,2>  tensor_a(3,4);

    TensorHaoRef<double,2> tensor_a_ref_p0(tensor_a);
    tensor_a_ref_p0={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    TensorHaoRef<double,2> tensor_a_ref_p1(tensor_a_ref_p0);

    TensorHaoRef<double,2> tensor_a_ref_p2, tensor_a_ref_p3;

    tensor_a_ref_p2 = tensor_a_ref_p0; 

    tensor_a_ref_p3 = tensor_a; 

    const size_t size=12;
    const size_t D=2;
    size_t n[D]={3,4};
    size_t n_step[D]={1,3};
    double p_value[size]={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    EXPECT_EQ( size, tensor_a_ref_p3.size() );
    EXPECT_EQ( tensor_a_ref_p0.data(), tensor_a.data() );
    EXPECT_EQ( tensor_a_ref_p1.data(), tensor_a.data() );
    EXPECT_EQ( tensor_a_ref_p2.data(), tensor_a.data() );
    EXPECT_EQ( tensor_a_ref_p3.data(), tensor_a.data() );

    for(size_t i=0; i<D; i++)
    {
        EXPECT_EQ(tensor_a_ref_p3.rank(i), n[i] );
        EXPECT_EQ(tensor_a_ref_p3.rankStep(i), n_step[i] );
    }
    EXPECT_POINTER_EQ(size, p_value, tensor_a_ref_p0.data() );
}

TEST(Tensor_hao_ref, equal_T)
{
    TensorHao<double,3>  tensor(3,4,5);
    TensorHaoRef<double,3>  tensor_ref( tensor );
    size_t L = tensor_ref.size();
    tensor_ref=3.0;

    vector<double> exact(L, 3.0);
    EXPECT_POINTER_DOUBLE_EQ(L, exact.data(), tensor_ref.data() );
}


TEST(Tensor_hao_ref, point)
{
    TensorHaoRef<double,2> tensor_ref(5,8), tensor_ref_p(5,8);
    vector<double> vec(40);
    tensor_ref.point(vec);
    tensor_ref_p.point( vec.data() );

    EXPECT_EQ( vec.data(), tensor_ref.data() );
    EXPECT_EQ( vec.data(), tensor_ref_p.data() );
}

TEST(Tensor_hao_ref, resize_Variadic)
{
    const size_t D=3;
    TensorHaoRef<double, D>  tensor(84,1,1);
    size_t size=84;
    size_t n[D]={3,4,7};
    size_t n_step[D]={1,3,12};
    tensor.resize(3, 4, 7);

    EXPECT_EQ( size, tensor.size() );
    for(size_t i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor.rank(i) );
        EXPECT_EQ( n_step[i], tensor.rankStep(i) );
    }
}

TEST(Tensor_hao_ref, resize_pointer)
{
    const size_t D=3;
    TensorHaoRef<double, D>  tensor(84,1,1);
    size_t size=84;
    size_t n[D]={3,4,7};
    size_t n_step[D]={1,3,12};
    tensor.resize(n);

    EXPECT_EQ( size, tensor.size() );
    for(size_t i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor.rank(i) );
        EXPECT_EQ( n_step[i], tensor.rankStep(i) );
    }
}

TEST(Tensor_hao_ref, getMemory)
{
    TensorHaoRef<double,2>  tensor_a(3,4);
    EXPECT_DOUBLE_EQ(48.0, tensor_a.getMemory() );

    TensorHaoRef<complex<double>,2>  tensor_b(3,4);
    EXPECT_DOUBLE_EQ(48.0, tensor_b.getMemory() );

    TensorHaoRef<int,3>  tensor_c(3,4,5);
    EXPECT_DOUBLE_EQ(64.0, tensor_c.getMemory() );
}

TEST(Tensor_hao_ref, readWriteBcast)
{
    string filename ="tensorFile.dat";
    TensorHao<double,2>  tensor_a(3,4), tensor_b(3,4);
    TensorHaoRef<double,2>  tensor_a_ref(tensor_a), tensor_b_ref(tensor_b);
    tensor_a_ref={ 1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    if( MPIRank() == 0 )
    {
        tensor_a_ref.write(filename);
        tensor_b_ref.read(filename);
    }
    MPIBcast( tensor_b_ref );

    EXPECT_EQ( tensor_a_ref.size(), tensor_b_ref.size() );
    for(size_t i=0; i< static_cast<size_t>(2); i++)
    {
        EXPECT_EQ( tensor_a_ref.rank(i), tensor_b_ref.rank(i) );
        EXPECT_EQ( tensor_a_ref.rankStep(i), tensor_b_ref.rankStep(i) );
    }
    EXPECT_POINTER_EQ(tensor_a_ref.size(), tensor_a_ref.data(), tensor_b_ref.data() );

    string command = "rm -rf " + filename;
    MPIBarrier();
    if( MPIRank()==0 )
    {
        int flag=system( command.c_str() );
        if(flag != 0) cout<<"WARNING!!! system command does not exit properly!"<<endl;
    }
    MPIBarrier();
}