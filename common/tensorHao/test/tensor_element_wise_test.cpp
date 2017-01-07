#include <cmath>
#include "../include/tensor_element_wise.h"
#include "../../testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(Tensor_element, conj)
{
    TensorHao< complex<double>,2>  tensor_a(3,2);
    tensor_a={ {1.0 ,2.0} , {3.0 ,4.0} , {5.0 ,6.0} , {7.0 ,8.0} , {9.0 ,10.0} , {11.0 ,12.0} };

    TensorHao< complex<double>,2> tensor_b = conj( tensor_a );

    for(size_t j=0; j<2; j++)
    {
        for(size_t i=0; i<3; i++)
        {
            EXPECT_COMPLEXDOUBLE_EQ( tensor_b(i,j), conj( tensor_a(i,j) ) );
        }
    }
}

TEST(Tensor_element, exp)
{
    TensorHao<double,2>  tensor_a(3,4);
    tensor_a={1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};

    TensorHao<double,2> tensor_b = exp( tensor_a );

    for(size_t j=0; j<4; j++)
    {
        for(size_t i=0; i<3; i++)
        {
            EXPECT_COMPLEXDOUBLE_EQ( tensor_b(i,j), exp( tensor_a(i,j) ) );
        }
    }
}

TEST(Tensor_element, log)
{
    TensorHao<double,2>  tensor_a(3,4);
    tensor_a={1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};

    TensorHao<double,2> tensor_b = log( tensor_a );

    for(size_t j=0; j<4; j++)
    {
        for(size_t i=0; i<3; i++)
        {
            EXPECT_COMPLEXDOUBLE_EQ( tensor_b(i,j), log( tensor_a(i,j) ) );
        }
    }
}


TEST(Tensor_element, norm)
{
    TensorHao< complex<double>,2>  tensor_a(3,2);
    tensor_a={ {1.0 ,2.0} , {3.0 ,4.0} , {5.0 ,6.0} , {7.0 ,8.0} , {9.0 ,10.0} , {11.0 ,12.0} };

    TensorHao< complex<double>,2> tensor_b = norm( tensor_a );

    for(size_t j=0; j<2; j++)
    {
        for(size_t i=0; i<3; i++)
        {
            EXPECT_COMPLEXDOUBLE_EQ( tensor_b(i,j), norm( tensor_a(i,j) ) );
        }
    }
}

TEST(Tensor_element, abs)
{
    TensorHao< complex<double>,2>  tensor_a(3,2);
    tensor_a={ {1.0 ,2.0} , {3.0 ,4.0} , {5.0 ,6.0} , {7.0 ,8.0} , {9.0 ,10.0} , {11.0 ,12.0} };

    TensorHao< complex<double>,2> tensor_b = abs( tensor_a );

    for(size_t j=0; j<2; j++)
    {
        for(size_t i=0; i<3; i++)
        {
            EXPECT_COMPLEXDOUBLE_EQ( tensor_b(i,j), abs( tensor_a(i,j) ) );
        }
    }
}

TEST(Tensor_element, sqrt)
{
    TensorHao<double,2>  tensor_a(3,4);
    tensor_a={1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};

    TensorHao<double,2> tensor_b = sqrt( tensor_a );

    for(size_t j=0; j<4; j++)
    {
        for(size_t i=0; i<3; i++)
        {
            EXPECT_COMPLEXDOUBLE_EQ( tensor_b(i,j), sqrt( tensor_a(i,j) ) );
        }
    }
}


TEST(Tensor_element, minus)
{
    TensorHao<double,2>  tensor_a(3,4);
    tensor_a={1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};

    TensorHao<double,2> tensor_b = -tensor_a;

    for(size_t j=0; j<4; j++)
    {
        for(size_t i=0; i<3; i++)
        {
            EXPECT_COMPLEXDOUBLE_EQ( tensor_b(i,j), -tensor_a(i,j) );
        }
    }
}

TEST(Tensor_element, add_Tensor)
{
    TensorHao<double,3>  tensor_a(3,4,5);
    size_t L = tensor_a.size();
    double* p_a = tensor_a.data();
    for(size_t i=0; i<L; i++) p_a[i] = i*2.0;

    TensorHao<double,3>  tensor_b(3,4,5);
    double* p_b = tensor_b.data();
    for(size_t i=0; i<L; i++) p_b[i] = i*1.0;

    //TensorHaoRef<double,3> tensor_a_ref = tensor_a;
    //TensorHaoRef<double,3> tensor_b_ref = tensor_b;
    TensorHao<double,3> tensor_c = tensor_a + tensor_b;

    vector<double> exact(L);
    for (size_t i = 0; i < L; ++i) exact[i] =  i * 3.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor_c.data() );
}

TEST(Tensor_element, minus_Tensor)
{
    TensorHao<double,3>  tensor_a(3,4,5);
    size_t L = tensor_a.size();
    double* p_a = tensor_a.data();
    for(size_t i=0; i<L; i++) p_a[i] = i*2.0;

    TensorHao<double,3>  tensor_b(3,4,5);
    double* p_b = tensor_b.data();
    for(size_t i=0; i<L; i++) p_b[i] = i*1.0;

    //TensorHaoRef<double,3> tensor_a_ref = tensor_a;
    //TensorHaoRef<double,3> tensor_b_ref = tensor_b;
    TensorHao<double,3> tensor_c = tensor_a - tensor_b;

    vector<double> exact(L);
    for (size_t i = 0; i < L; ++i) exact[i] =  i;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor_c.data() );
}

TEST(Tensor_element, time_Tensor)
{
    TensorHao<double,3>  tensor_a(3,4,5);
    size_t L = tensor_a.size();
    double* p_a = tensor_a.data();
    for(size_t i=0; i<L; i++) p_a[i] = i*2.0;

    TensorHao<double,3>  tensor_b(3,4,5);
    double* p_b = tensor_b.data();
    for(size_t i=0; i<L; i++) p_b[i] = i*1.0;

    //TensorHaoRef<double,3> tensor_a_ref = tensor_a;
    //TensorHaoRef<double,3> tensor_b_ref = tensor_b;
    TensorHao<double,3> tensor_c = tensor_a * tensor_b;

    vector<double> exact(L);
    for (size_t i = 0; i < L; ++i) exact[i] =  i*i*2.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor_c.data() );
}

TEST(Tensor_element, divide_Tensor)
{
    TensorHao<double,3>  tensor_a(3,4,5);
    size_t L = tensor_a.size();
    double* p_a = tensor_a.data();
    for(size_t i=0; i<L; i++) p_a[i] = i*2.0;

    TensorHao<double,3>  tensor_b(3,4,5);
    double* p_b = tensor_b.data();
    for(size_t i=0; i<L; i++) p_b[i] = i*1.0;

    //TensorHaoRef<double,3> tensor_a_ref = tensor_a;
    //TensorHaoRef<double,3> tensor_b_ref = tensor_b;
    TensorHao<double,3> tensor_c = tensor_a / tensor_b;

    vector<double> exact(L);
    for (size_t i = 0; i < L; ++i) exact[i] =  2.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor_c.data() );
}

TEST(Tensor_element, add_T)
{
    TensorHao<double,3>  tensor_a(3,4,5);
    size_t L = tensor_a.size();
    double* p_a = tensor_a.data();
    for(size_t i=0; i<L; i++) p_a[i] = i*2.0;

    double b =3.0;

    //TensorHaoRef<double,3> tensor_a_ref = tensor_a;
    TensorHao<double,3> tensor_c = tensor_a + b ;

    vector<double> exact(L);
    for (size_t i = 0; i < L; ++i) exact[i] =  i*2.0+3.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor_c.data() );
}

TEST(Tensor_element, minus_T)
{
    TensorHao<double,3>  tensor_a(3,4,5);
    size_t L = tensor_a.size();
    double* p_a = tensor_a.data();
    for(size_t i=0; i<L; i++) p_a[i] = i*2.0;

    double b =3.0;

    //TensorHaoRef<double,3> tensor_a_ref = tensor_a;
    TensorHao<double,3> tensor_c = tensor_a -b;

    vector<double> exact(L);
    for (size_t i = 0; i < L; ++i) exact[i] =  i*2.0-3.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor_c.data() );
}

TEST(Tensor_element, time_T)
{
    TensorHao<double,3>  tensor_a(3,4,5);
    size_t L = tensor_a.size();
    double* p_a = tensor_a.data();
    for(size_t i=0; i<L; i++) p_a[i] = i*2.0;

    double b =3.0;

    //TensorHaoRef<double,3> tensor_a_ref = tensor_a;
    TensorHao<double,3> tensor_c = tensor_a * b  ;

    vector<double> exact(L);
    for (size_t i = 0; i < L; ++i) exact[i] =  i*2.0*3.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor_c.data() );
}

TEST(Tensor_element, div_T)
{
    TensorHao<double, 3> tensor_a(3, 4, 5);
    size_t L = tensor_a.size();
    double *p_a = tensor_a.data();
    for (size_t i = 0; i < L; i++) p_a[i] = i * 2.0;

    double b = 3.0;

    //TensorHaoRef<double,3> tensor_a_ref = tensor_a;
    TensorHao<double, 3> tensor_c = tensor_a / b;

    vector<double> exact(L);
    for (size_t i = 0; i < L; ++i) exact[i] = i * 2.0 / 3.0;

    EXPECT_POINTER_DOUBLE_EQ(L, exact.data(), tensor_c.data());
}

TEST(Tensor_element, diff)
{
    TensorHao<double,2>  tensor_a(3,4);
    TensorHao<double,2>  tensor_b(3,4);
    TensorHaoRef<double,2>  tensor_b_ref(tensor_b);
    tensor_a = {1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.};
    tensor_b = {1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.};

    EXPECT_FALSE( diff(tensor_a, tensor_b_ref, 1e-12) );
}
