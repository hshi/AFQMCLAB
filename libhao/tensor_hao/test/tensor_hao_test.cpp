#include "../include/tensor_hao_ref.h"
#include "../include/tensor_hao.h"
#include "../../test_hao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(Tensor_hao, void_construction)
{
    TensorHao<double,2>  tensor;
    for (size_t i = 0; i < 2; ++i)
    {
        EXPECT_EQ( 0, tensor.rank(i) );
        EXPECT_EQ( 0, tensor.rankStep(i) );
    }
    EXPECT_FALSE( tensor.data() );
    EXPECT_EQ( 0, tensor.size() );

}

TEST(Tensor_hao, variadic_construction)
{
    const size_t D=3;
    TensorHao<double, D>  tensor(3,4,7);
    size_t size=84;
    size_t n[D]={3,4,7};
    size_t n_step[D]={1,3,12};

    EXPECT_TRUE( tensor.data() );
    EXPECT_EQ( size, tensor.size() );
    for(size_t i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor.rank(i) );
        EXPECT_EQ( n_step[i], tensor.rankStep(i) );
    }
}

TEST(Tensor_hao, pointer_constructor)
{
    const size_t D=3;
    size_t n_ptr[D] = {3,4,7};
    TensorHao<double, D>  tensor(n_ptr);
    size_t size=84;
    size_t n[D]={3,4,7};
    size_t n_step[D]={1,3,12};

    EXPECT_TRUE( tensor.data() );
    EXPECT_EQ( size, tensor.size() );
    for(size_t i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor.rank(i) );
        EXPECT_EQ( n_step[i], tensor.rankStep(i) );
    }
}

TEST(Tensor_hao, copy_constructor)
{
    TensorHao<double,2>  tensor_a(3,4);
    tensor_a={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    TensorHao<double,2>  tensor_b( tensor_a );

    const size_t size=12;
    const size_t D=2;
    size_t n[D]={3,4};
    size_t n_step[D]={1,3};
    double p_value[size]={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    EXPECT_EQ( size, tensor_b.size() );
    for(size_t i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor_b.rank(i) );
        EXPECT_EQ( n_step[i], tensor_b.rankStep(i) );
    }
    EXPECT_POINTER_EQ(size, p_value, tensor_b.data() );
}

TEST(Tensor_hao, move_constructor)
{
    TensorHao<double,2>  tensor_a(3,4);
    tensor_a={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    TensorHao<double,2>  tensor_b( move(tensor_a) );

    const size_t size=12;
    const size_t D=2;
    size_t n[D]={3,4};
    size_t n_step[D]={1,3};
    double p_value[size]={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    EXPECT_EQ( size, tensor_b.size() );
    for(size_t i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor_b.rank(i) );
        EXPECT_EQ( n_step[i], tensor_b.rankStep(i) );
    }
    EXPECT_POINTER_EQ(size, p_value, tensor_b.data() );
}

TEST(Tensor_hao, copy_ref_constructor)
{
    TensorHao<double,2>  tensor_a(3,4);
    tensor_a={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };
    TensorHaoRef<double,2>  tensor_a_ref(tensor_a);

    TensorHao<double,2>  tensor_b( tensor_a_ref );

    const size_t size=12;
    const size_t D=2;
    size_t n[D]={3,4};
    size_t n_step[D]={1,3};
    double p_value[size]={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    EXPECT_EQ( size, tensor_b.size() );
    for(size_t i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor_b.rank(i) );
        EXPECT_EQ( n_step[i], tensor_b.rankStep(i) );
    }
    EXPECT_POINTER_EQ(size, p_value, tensor_b.data() );
}

TEST(Tensor_hao, copy_assignment)
{
    TensorHao<double,2>  tensor_a(3,4);
    tensor_a={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    TensorHao<double,2>  tensor_b; tensor_b = tensor_a;

    const size_t size=12;
    const size_t D=2;
    size_t n[D]={3,4};
    size_t n_step[D]={1,3};
    double p_value[size]={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    EXPECT_EQ( size, tensor_b.size() );
    for(size_t i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor_b.rank(i) );
        EXPECT_EQ( n_step[i], tensor_b.rankStep(i) );
    }
    EXPECT_POINTER_EQ(size, p_value, tensor_b.data() );
}

TEST(Tensor_hao, move_assignment)
{
    TensorHao<double,2>  tensor_a(3,4);
    tensor_a={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    TensorHao<double,2>  tensor_b; tensor_b = move(tensor_a) ;

    const size_t size=12;
    const size_t D=2;
    size_t n[D]={3,4};
    size_t n_step[D]={1,3};
    double p_value[size]={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    EXPECT_EQ( size, tensor_b.size() );
    for(size_t i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor_b.rank(i) );
        EXPECT_EQ( n_step[i], tensor_b.rankStep(i) );
    }
    EXPECT_POINTER_EQ(size, p_value, tensor_b.data() );
}

TEST(Tensor_hao, copy_ref_assignment)
{
    TensorHao<double,2>  tensor_a(3,4);
    tensor_a={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };
    TensorHaoRef<double,2>  tensor_a_ref(tensor_a);

    TensorHao<double,2>  tensor_b; tensor_b = tensor_a_ref ;

    const size_t size=12;
    const size_t D=2;
    size_t n[D]={3,4};
    size_t n_step[D]={1,3};
    double p_value[size]={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    EXPECT_EQ( size, tensor_b.size() );
    for(size_t i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor_b.rank(i) );
        EXPECT_EQ( n_step[i], tensor_b.rankStep(i) );
    }
    EXPECT_POINTER_EQ(size, p_value, tensor_b.data() );
}

TEST(Tensor_hao, equal_T)
{
    TensorHao<double,3>  tensor(3,4,5);
    size_t L = tensor.size();
    tensor=3.0;

    vector<double> exact(L, 3.0);
    EXPECT_POINTER_DOUBLE_EQ(L, exact.data(), tensor.data() );
}

TEST(Tensor_hao, resize_Variadic)
{
    const size_t D=3;
    TensorHao<double, D>  tensor;
    size_t size=84;
    size_t n[D]={3,4,7};
    size_t n_step[D]={1,3,12};
    tensor.resize(3, 4, 7);

    EXPECT_TRUE( tensor.data() );
    EXPECT_EQ( size, tensor.size() );
    for(size_t i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor.rank(i) );
        EXPECT_EQ( n_step[i], tensor.rankStep(i) );
    }
}

TEST(Tensor_hao, resize_pointer)
{
    const size_t D=3;
    TensorHao<double, D>  tensor;
    size_t size=84;
    size_t n[D]={3,4,7};
    size_t n_step[D]={1,3,12};
    tensor.resize(n);

    EXPECT_TRUE( tensor.data() );
    EXPECT_EQ( size, tensor.size() );
    for(size_t i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor.rank(i) );
        EXPECT_EQ( n_step[i], tensor.rankStep(i) );
    }
}


