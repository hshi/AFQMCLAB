#include <complex>
#include "../include/tensor_hao_ref.h"
#include "../include/tensor_hao.h"
#include "../../../utilities/test_hao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(Tensor_core, nptr)
{
    TensorHao<double,5>  tensor(2,3,4,5,6);
    int n_ptr_exact[5] = {2,3,4,5,6};
    EXPECT_POINTER_EQ( 5, n_ptr_exact, tensor.n_ptr() );
}

TEST(Tensor_core, read_1)
{
    TensorHao<double,1>  tensor(3);
    int L = tensor.size();
    double* p = tensor.data();

    for(int i=0; i<L; i++) p[i] = i*1.0;

    int count=0;
    for(int k=0; k<3; k++)
    {
        EXPECT_EQ( p[count], tensor(k) );
        count++;
    }
}


TEST(Tensor_core, write_1)
{
    TensorHao<double,1>  tensor(3);
    int L = tensor.size();
    double* p = tensor.data();
    int count=0;

    count=0;
    for(int k=0; k<3; k++) 
    {
        tensor(k) = count*1.0;
        count++;
    }

    for(int i=0; i<L; i++) 
    {
        EXPECT_EQ( i, p[i] );
    }
}



TEST(Tensor_core, read_2)
{
    TensorHao<double,2>  tensor(3,4);
    int L = tensor.size();
    double* p = tensor.data();

    for(int i=0; i<L; i++) p[i] = i*1.0;

    int count=0;
    for(int j=0; j<4; j++)
    {
        for(int k=0; k<3; k++)
        {
            EXPECT_EQ( p[count], tensor(k,j) );
            count++;
        }
    }
}

TEST(Tensor_core, write_2)
{
    TensorHao<double,2>  tensor(3,4);
    int L = tensor.size();
    double* p = tensor.data();
    int count=0;

    count=0;
    for(int j=0; j<4; j++)
    {
        for(int k=0; k<3; k++)
        {
            tensor(k,j) = count*1.0;
            count++;
        }
    }

    for(int i=0; i<L; i++)
    {
        EXPECT_EQ( i, p[i]) ;
    }
}


TEST(Tensor_core, read_3)
{
    TensorHao<double,3>  tensor(3,4,5);
    int L = tensor.size();
    double* p = tensor.data();

    for(int i=0; i<L; i++) p[i] = i*1.0;

    int count=0;
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<4; j++)
        {
            for(int k=0; k<3; k++) 
            {
                EXPECT_EQ( p[count], tensor(k,j,i) );
                count++;
            }
        }
    }
}

TEST(Tensor_core, write_3)
{
    TensorHao<double,3>  tensor(3,4,5);
    int L = tensor.size();
    double* p = tensor.data();
    int count=0;

    count=0;
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<4; j++)
        {
            for(int k=0; k<3; k++)
            {
                tensor(k,j,i)=count*1.0;
                count++;
            }
        }
    }

    for(int i=0; i<L; i++)
    {
        EXPECT_EQ( i, p[i]) ;
    }
}


TEST(Tensor_core, read_5)
{
    TensorHao<double,5>  tensor(3,4,5,6,7);
    int L = tensor.size();
    double* p = tensor.data();

    for(int i=0; i<L; i++) p[i] = i*1.0;

    int count=0;
    for(int i5=0; i5<7; i5++)
    {
        for(int i4=0; i4<6; i4++)
        {
            for(int i=0; i<5; i++)
            {
                for(int j=0; j<4; j++)
                {
                    for(int k=0; k<3; k++)
                    {
                        EXPECT_EQ( p[count], tensor(k,j,i, i4, i5) );
                        count++;
                    }
                }
            }
        }
    }
}

TEST(Tensor_core, write_5)
{
    TensorHao<double,5>  tensor(3,4,5,6,7);
    int L = tensor.size();
    double* p = tensor.data();
    int count=0;

    count=0;
    for(int i5=0; i5<7; i5++)
    {
        for(int i4=0; i4<6; i4++)
        {
            for(int i=0; i<5; i++)
            {
                for(int j=0; j<4; j++)
                {
                    for(int k=0; k<3; k++)
                    {
                        tensor(k,j,i,i4,i5) = count*1.0;
                        count++;
                    }
                }
            }
        }
    }

    for(int i=0; i<L; i++)
    {
        EXPECT_EQ( i, p[i]) ;
    }
}

TEST(Tensor_core, add_equal_Tensor_core)
{
    TensorHao<double,3>  tensor(3,4,5);
    int L = tensor.size();
    double* p = tensor.data();
    for(int i=0; i<L; i++) p[i] = i*2.0;

    TensorHao<double,3>  tensor_b(3,4,5);
    double* p_b = tensor_b.data();
    for(int i=0; i<L; i++) p_b[i] = i*1.0;

    tensor+=tensor_b;

    vector<double> exact(L);
    for (int i = 0; i < L; ++i) exact[i] = i * 3.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor.data() );
}


TEST(Tensor_core, minus_equal_Tensor_core)
{
    TensorHao<double,3>  tensor(3,4,5);
    int L = tensor.size();
    double* p = tensor.data();
    for(int i=0; i<L; i++) p[i] = i*3.0;

    TensorHao<double,3>  tensor_b(3,4,5);
    double* p_b = tensor_b.data();
    for(int i=0; i<L; i++) p_b[i] = i*1.0;

    tensor-=tensor_b;

    vector<double> exact(L);
    for (int i = 0; i < L; ++i) exact[i] = i * 2.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor.data() );
}


TEST(Tensor_core, min_add_equal_Tensor_core)
{
    TensorHao<double,3>  tensor(3,4,5);
    int L = tensor.size();
    double* p = tensor.data();
    for(int i=0; i<L; i++) p[i] = i*3.0;

    TensorHao<double,3>  tensor_b(3,4,5);
    double* p_b = tensor_b.data();
    for(int i=0; i<L; i++) p_b[i] = i*1.0;

    tensor.min_add_equal(tensor_b);

    vector<double> exact(L);
    for (int i = 0; i < L; ++i) exact[i] = - i * 2.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor.data() );
}


TEST(Tensor_core, time_equal_Tensor_core)
{
    TensorHao<double,3>  tensor(3,4,5);
    int L = tensor.size();
    double* p = tensor.data();
    for(int i=0; i<L; i++) p[i] = i*3.0;

    TensorHao<double,3>  tensor_b(3,4,5);
    double* p_b = tensor_b.data();
    for(int i=0; i<L; i++) p_b[i] = i*1.0;

    tensor*=tensor_b;

    vector<double> exact(L);
    for (int i = 0; i < L; ++i) exact[i] = i * i * 3.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor.data() );
}

TEST(Tensor_core, divide_equal_Tensor_core)
{
    TensorHao<double,3>  tensor(3,4,5);
    int L = tensor.size();
    double* p = tensor.data();
    for(int i=0; i<L; i++) p[i] = i*3.0;

    TensorHao<double,3>  tensor_b(3,4,5);
    double* p_b = tensor_b.data();
    for(int i=0; i<L; i++) p_b[i] = i*1.0;

    tensor/=tensor_b;

    vector<double> exact(L);
    for (int i = 0; i < L; ++i) exact[i] = 3.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor.data() );
}

TEST(Tensor_core, inv_div_equal_Tensor_core)
{
    TensorHao<double,3>  tensor(3,4,5);
    int L = tensor.size();
    double* p = tensor.data();
    for(int i=0; i<L; i++) p[i] = i*3.0;

    TensorHao<double,3>  tensor_b(3,4,5);
    double* p_b = tensor_b.data();
    for(int i=0; i<L; i++) p_b[i] = i*1.0;

    tensor.inv_div_equal(tensor_b);

    vector<double> exact(L);
    for (int i = 0; i < L; ++i) exact[i] = 1.0/3.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor.data() );
}


TEST(Tensor_core, add_equal_T)
{
    TensorHao<double,3>  tensor(3,4,5);
    int L = tensor.size();
    double* p = tensor.data();
    for(int i=0; i<L; i++) p[i] = i*2.0;

    double b=3.0;

    tensor+=b;

    vector<double> exact(L);
    for (int i = 0; i < L; ++i) exact[i] = i * 2.0 + 3.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor.data() );
}

TEST(Tensor_core, minus_equal_T)
{
    TensorHao<double,3>  tensor(3,4,5);
    int L = tensor.size();
    double* p = tensor.data();
    for(int i=0; i<L; i++) p[i] = i*2.0;

    double b=3.0;

    tensor-=b;

    vector<double> exact(L);
    for (int i = 0; i < L; ++i) exact[i] = i * 2.0 - 3.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor.data() );
}

TEST(Tensor_core, min_add_equal_T)
{
    TensorHao<double,3>  tensor(3,4,5);
    int L = tensor.size();
    double* p = tensor.data();
    for(int i=0; i<L; i++) p[i] = i*2.0;

    double b=3.0;

    tensor.min_add_equal(b);

    vector<double> exact(L);
    for (int i = 0; i < L; ++i) exact[i] = -i * 2.0 + 3.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor.data() );
}


TEST(Tensor_core, time_equal_T)
{
    TensorHao<double,3>  tensor(3,4,5);
    int L = tensor.size();
    double* p = tensor.data();
    for(int i=0; i<L; i++) p[i] = i*2.0;

    double b=3.0;

    tensor*=b;

    vector<double> exact(L);
    for (int i = 0; i < L; ++i) exact[i] = i * 6.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor.data() );
}

TEST(Tensor_core, divide_equal_T)
{
    TensorHao<double,3>  tensor(3,4,5);
    int L = tensor.size();
    double* p = tensor.data();
    for(int i=0; i<L; i++) p[i] = i*2.0;

    double b=3.0;

    tensor/=b;

    vector<double> exact(L);
    for (int i = 0; i < L; ++i) exact[i] = i * 2.0 / 3.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor.data() );
}


TEST(Tensor_core, inv_div_equal_T)
{
    TensorHao<double,3>  tensor(3,4,5);
    int L = tensor.size();
    double* p = tensor.data();
    for(int i=0; i<L; i++) p[i] = i*2.0;

    double b=3.0;

    tensor.inv_div_equal(b);

    vector<double> exact(L);
    for (int i = 0; i < L; ++i) exact[i] = 3.0 / ( i * 2.0 );

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor.data() );
}

TEST(Tensor_core, sum)
{
    TensorHao< complex<double>,2>  tensor_a(3,2);
    tensor_a={ {1.0, 2.0} , {3.0 ,4.0} , {5.0 ,6.0} , {7.0 ,8.0} , {9.0 ,10.0} , {11.0 ,12.0} };

    complex<double> exact(15., 18.0);

    EXPECT_COMPLEXDOUBLE_EQ( exact, tensor_a.sum(0, 5, 2) );
}

TEST(Tensor_core, mean)
{
    TensorHao< complex<double>,2>  tensor_a(3,2);
    tensor_a={ {1.0, 2.0} , {3.0 ,4.0} , {5.0 ,6.0} , {7.0 ,8.0} , {9.0 ,10.0} , {11.0 ,12.0} };

    complex<double> exact(5., 6.0);

    EXPECT_COMPLEXDOUBLE_EQ( exact, tensor_a.mean(0, 5, 2) );
}
