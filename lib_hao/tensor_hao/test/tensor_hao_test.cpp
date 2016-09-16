#include "../include/tensor_hao_ref.h"
#include "../include/tensor_hao.h"
#include "../../../utilities/test_hao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(Tensor_hao, void_construction)
{
    TensorHao<double,2>  tensor;
    for (int i = 0; i < 2; ++i)
    {
        EXPECT_EQ( 0, tensor.getRank(i) );
        EXPECT_EQ( 0, tensor.getRankStep(i) );
    }
    EXPECT_FALSE( tensor.data() );
    EXPECT_EQ( 0, tensor.size() );

}

TEST(Tensor_hao, variadic_construction)
{
    const int D=3;
    TensorHao<double, D>  tensor(3,4,7);
    int size=84;
    int n[D]={3,4,7};
    int n_step[D]={1,3,12};

    EXPECT_TRUE( tensor.data() );
    EXPECT_EQ( size, tensor.size() );
    for(int i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor.getRank(i) );
        EXPECT_EQ( n_step[i], tensor.getRankStep(i) );
    }
}

TEST(Tensor_hao, pointer_constructor)
{
    const int D=3;
    int n_ptr[D] = {3,4,7};
    TensorHao<double, D>  tensor(n_ptr);
    int size=84;
    int n[D]={3,4,7};
    int n_step[D]={1,3,12};

    EXPECT_TRUE( tensor.data() );
    EXPECT_EQ( size, tensor.size() );
    for(int i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor.getRank(i) );
        EXPECT_EQ( n_step[i], tensor.getRankStep(i) );
    }
}

TEST(Tensor_hao, copy_constructor)
{
    TensorHao<double,2>  tensor_a(3,4);
    tensor_a={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    TensorHao<double,2>  tensor_b( tensor_a );

    const int size=12;
    const int D=2;
    int n[D]={3,4};
    int n_step[D]={1,3};
    double p_value[size]={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    EXPECT_EQ( size, tensor_b.size() );
    for(int i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor_b.getRank(i) );
        EXPECT_EQ( n_step[i], tensor_b.getRankStep(i) );
    }
    EXPECT_POINTER_EQ(size, p_value, tensor_b.data() );
}

TEST(Tensor_hao, move_constructor)
{
    TensorHao<double,2>  tensor_a(3,4);
    tensor_a={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    TensorHao<double,2>  tensor_b( move(tensor_a) );

    const int size=12;
    const int D=2;
    int n[D]={3,4};
    int n_step[D]={1,3};
    double p_value[size]={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    EXPECT_EQ( size, tensor_b.size() );
    for(int i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor_b.getRank(i) );
        EXPECT_EQ( n_step[i], tensor_b.getRankStep(i) );
    }
    EXPECT_POINTER_EQ(size, p_value, tensor_b.data() );
}

TEST(Tensor_hao, copy_ref_constructor)
{
    TensorHao<double,2>  tensor_a(3,4);
    tensor_a={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };
    TensorHaoRef<double,2>  tensor_a_ref(tensor_a);

    TensorHao<double,2>  tensor_b( tensor_a_ref );

    const int size=12;
    const int D=2;
    int n[D]={3,4};
    int n_step[D]={1,3};
    double p_value[size]={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    EXPECT_EQ( size, tensor_b.size() );
    for(int i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor_b.getRank(i) );
        EXPECT_EQ( n_step[i], tensor_b.getRankStep(i) );
    }
    EXPECT_POINTER_EQ(size, p_value, tensor_b.data() );
}

TEST(Tensor_hao, copy_assignment)
{
    TensorHao<double,2>  tensor_a(3,4);
    tensor_a={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    TensorHao<double,2>  tensor_b; tensor_b = tensor_a;

    const int size=12;
    const int D=2;
    int n[D]={3,4};
    int n_step[D]={1,3};
    double p_value[size]={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    EXPECT_EQ( size, tensor_b.size() );
    for(int i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor_b.getRank(i) );
        EXPECT_EQ( n_step[i], tensor_b.getRankStep(i) );
    }
    EXPECT_POINTER_EQ(size, p_value, tensor_b.data() );
}

TEST(Tensor_hao, move_assignment)
{
    TensorHao<double,2>  tensor_a(3,4);
    tensor_a={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    TensorHao<double,2>  tensor_b; tensor_b = move(tensor_a) ;

    const int size=12;
    const int D=2;
    int n[D]={3,4};
    int n_step[D]={1,3};
    double p_value[size]={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    EXPECT_EQ( size, tensor_b.size() );
    for(int i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor_b.getRank(i) );
        EXPECT_EQ( n_step[i], tensor_b.getRankStep(i) );
    }
    EXPECT_POINTER_EQ(size, p_value, tensor_b.data() );
}

TEST(Tensor_hao, copy_ref_assignment)
{
    TensorHao<double,2>  tensor_a(3,4);
    tensor_a={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };
    TensorHaoRef<double,2>  tensor_a_ref(tensor_a);

    TensorHao<double,2>  tensor_b; tensor_b = tensor_a_ref ;

    const int size=12;
    const int D=2;
    int n[D]={3,4};
    int n_step[D]={1,3};
    double p_value[size]={1.0 ,2.0 ,3.0 ,4.0 ,5.0 ,6.0 ,7.0 ,8.0 ,9.0 ,10.0 ,11.0 ,12.0 };

    EXPECT_EQ( size, tensor_b.size() );
    for(int i=0; i<D; i++)
    {
        EXPECT_EQ( n[i], tensor_b.getRank(i) );
        EXPECT_EQ( n_step[i], tensor_b.getRankStep(i) );
    }
    EXPECT_POINTER_EQ(size, p_value, tensor_b.data() );
}

TEST(Tensor_hao, equal_T)
{
    TensorHao<double,3>  tensor(3,4,5);
    int L = tensor.size();
    tensor=3.0;

    vector<double> exact(L, 3.0);
    EXPECT_POINTER_DOUBLE_EQ(L, exact.data(), tensor.data() );
}


TEST(Tensor_hao, slice)
{
    TensorHao<double,3>  tensor(3,4,5);
    int L = tensor.size(); double* p = tensor.data();
    for(int i=0; i<L; i++) p[i] = i*1.0;

    TensorHaoRef<double,2 >  slice = tensor[4];

    EXPECT_EQ( 12, slice.size() );
    EXPECT_POINTER_EQ(12, tensor.data()+12*4, slice.data() );
}