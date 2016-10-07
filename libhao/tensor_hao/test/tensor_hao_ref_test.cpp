#include <cmath>
#include "../include/tensor_hao.h"
#include "../../test_hao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(Tensor_hao_ref, void_construction)
{
    TensorHaoRef<double,2>  tensor_ref;

    for (size_t i = 0; i < 2; ++i)
    {
        EXPECT_EQ( 0, tensor_ref.rank(i) );
        EXPECT_EQ( 0, tensor_ref.rankStep(i) );
    }
    EXPECT_FALSE( tensor_ref.data() );
    EXPECT_EQ( 0, tensor_ref.size() );
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

TEST(Tensor_hao_ref, slice)
{
    TensorHaoRef<double,3>  tensor(3,4,5);
    size_t L = tensor.size(); vector<double> p(L);
    for(size_t i=0; i<L; i++) p[i] = i*1.0;
    tensor.point(p);

    TensorHaoRef<double,2 >  slice = tensor[4];

    EXPECT_EQ( 12, slice.size() );
    EXPECT_POINTER_EQ(12, tensor.data()+12*4, slice.data() );
}
