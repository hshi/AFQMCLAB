#include <cmath>
#include "../include/tensor_element_wise.h"
#include "../../../utilities/test_hao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(Tensor_element, conj)
{
    Tensor_hao< complex<double>,2>  tensor_a(3,2);
    tensor_a={ {1.0 ,2.0} , {3.0 ,4.0} , {5.0 ,6.0} , {7.0 ,8.0} , {9.0 ,10.0} , {11.0 ,12.0} };

    Tensor_hao< complex<double>,2> tensor_b = conj( tensor_a );

    for(int j=0; j<2; j++)
    {
        for(int i=0; i<3; i++)
        {
            EXPECT_COMPLEXDOUBLE_EQ( tensor_b(i,j), conj( tensor_a(i,j) ) );
        }
    }
}

TEST(Tensor_element, exp)
{
    Tensor_hao<double,2>  tensor_a(3,4);
    tensor_a={1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};

    Tensor_hao<double,2> tensor_b = exp( tensor_a );

    for(int j=0; j<4; j++)
    {
        for(int i=0; i<3; i++)
        {
            EXPECT_COMPLEXDOUBLE_EQ( tensor_b(i,j), exp( tensor_a(i,j) ) );
        }
    }
}

TEST(Tensor_element, norm)
{
    Tensor_hao< complex<double>,2>  tensor_a(3,2);
    tensor_a={ {1.0 ,2.0} , {3.0 ,4.0} , {5.0 ,6.0} , {7.0 ,8.0} , {9.0 ,10.0} , {11.0 ,12.0} };

    Tensor_hao< complex<double>,2> tensor_b = norm( tensor_a );

    for(int j=0; j<2; j++)
    {
        for(int i=0; i<3; i++)
        {
            EXPECT_COMPLEXDOUBLE_EQ( tensor_b(i,j), norm( tensor_a(i,j) ) );
        }
    }
}

TEST(Tensor_element, abs)
{
    Tensor_hao< complex<double>,2>  tensor_a(3,2);
    tensor_a={ {1.0 ,2.0} , {3.0 ,4.0} , {5.0 ,6.0} , {7.0 ,8.0} , {9.0 ,10.0} , {11.0 ,12.0} };

    Tensor_hao< complex<double>,2> tensor_b = abs( tensor_a );

    for(int j=0; j<2; j++)
    {
        for(int i=0; i<3; i++)
        {
            EXPECT_COMPLEXDOUBLE_EQ( tensor_b(i,j), abs( tensor_a(i,j) ) );
        }
    }
}

TEST(Tensor_element, sqrt)
{
    Tensor_hao<double,2>  tensor_a(3,4);
    tensor_a={1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};

    Tensor_hao<double,2> tensor_b = sqrt( tensor_a );

    for(int j=0; j<4; j++)
    {
        for(int i=0; i<3; i++)
        {
            EXPECT_COMPLEXDOUBLE_EQ( tensor_b(i,j), sqrt( tensor_a(i,j) ) );
        }
    }
}


TEST(Tensor_element, minus)
{
    Tensor_hao<double,2>  tensor_a(3,4);
    tensor_a={1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};

    Tensor_hao<double,2> tensor_b = -tensor_a;

    for(int j=0; j<4; j++)
    {
        for(int i=0; i<3; i++)
        {
            EXPECT_COMPLEXDOUBLE_EQ( tensor_b(i,j), -tensor_a(i,j) );
        }
    }
}

TEST(Tensor_element, add_Tensor)
{
    Tensor_hao<double,3>  tensor_a(3,4,5);
    int L = tensor_a.size();
    double* p_a = tensor_a.data();
    for(int i=0; i<L; i++) p_a[i] = i*2.0;

    Tensor_hao<double,3>  tensor_b(3,4,5);
    double* p_b = tensor_b.data();
    for(int i=0; i<L; i++) p_b[i] = i*1.0;

    //Tensor_hao_ref<double,3> tensor_a_ref = tensor_a;
    //Tensor_hao_ref<double,3> tensor_b_ref = tensor_b;
    Tensor_hao<double,3> tensor_c = tensor_a + tensor_b;

    vector<double> exact(L);
    for (int i = 0; i < L; ++i) exact[i] =  i * 3.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor_c.data() );
}

TEST(Tensor_element, minus_Tensor)
{
    Tensor_hao<double,3>  tensor_a(3,4,5);
    int L = tensor_a.size();
    double* p_a = tensor_a.data();
    for(int i=0; i<L; i++) p_a[i] = i*2.0;

    Tensor_hao<double,3>  tensor_b(3,4,5);
    double* p_b = tensor_b.data();
    for(int i=0; i<L; i++) p_b[i] = i*1.0;

    //Tensor_hao_ref<double,3> tensor_a_ref = tensor_a;
    //Tensor_hao_ref<double,3> tensor_b_ref = tensor_b;
    Tensor_hao<double,3> tensor_c = tensor_a - tensor_b;

    vector<double> exact(L);
    for (int i = 0; i < L; ++i) exact[i] =  i;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor_c.data() );
}

TEST(Tensor_element, time_Tensor)
{
    Tensor_hao<double,3>  tensor_a(3,4,5);
    int L = tensor_a.size();
    double* p_a = tensor_a.data();
    for(int i=0; i<L; i++) p_a[i] = i*2.0;

    Tensor_hao<double,3>  tensor_b(3,4,5);
    double* p_b = tensor_b.data();
    for(int i=0; i<L; i++) p_b[i] = i*1.0;

    //Tensor_hao_ref<double,3> tensor_a_ref = tensor_a;
    //Tensor_hao_ref<double,3> tensor_b_ref = tensor_b;
    Tensor_hao<double,3> tensor_c = tensor_a * tensor_b;

    vector<double> exact(L);
    for (int i = 0; i < L; ++i) exact[i] =  i*i*2.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor_c.data() );
}

TEST(Tensor_element, divide_Tensor)
{
    Tensor_hao<double,3>  tensor_a(3,4,5);
    int L = tensor_a.size();
    double* p_a = tensor_a.data();
    for(int i=0; i<L; i++) p_a[i] = i*2.0;

    Tensor_hao<double,3>  tensor_b(3,4,5);
    double* p_b = tensor_b.data();
    for(int i=0; i<L; i++) p_b[i] = i*1.0;

    //Tensor_hao_ref<double,3> tensor_a_ref = tensor_a;
    //Tensor_hao_ref<double,3> tensor_b_ref = tensor_b;
    Tensor_hao<double,3> tensor_c = tensor_a / tensor_b;

    vector<double> exact(L);
    for (int i = 0; i < L; ++i) exact[i] =  2.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor_c.data() );
}

TEST(Tensor_element, add_T)
{
    Tensor_hao<double,3>  tensor_a(3,4,5);
    int L = tensor_a.size();
    double* p_a = tensor_a.data();
    for(int i=0; i<L; i++) p_a[i] = i*2.0;

    double b =3.0;

    //Tensor_hao_ref<double,3> tensor_a_ref = tensor_a;
    Tensor_hao<double,3> tensor_c = tensor_a + b ;

    vector<double> exact(L);
    for (int i = 0; i < L; ++i) exact[i] =  i*2.0+3.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor_c.data() );
}

TEST(Tensor_element, minus_T)
{
    Tensor_hao<double,3>  tensor_a(3,4,5);
    int L = tensor_a.size();
    double* p_a = tensor_a.data();
    for(int i=0; i<L; i++) p_a[i] = i*2.0;

    double b =3.0;

    //Tensor_hao_ref<double,3> tensor_a_ref = tensor_a;
    Tensor_hao<double,3> tensor_c = tensor_a -b;

    vector<double> exact(L);
    for (int i = 0; i < L; ++i) exact[i] =  i*2.0-3.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor_c.data() );
}

TEST(Tensor_element, time_T)
{
    Tensor_hao<double,3>  tensor_a(3,4,5);
    int L = tensor_a.size();
    double* p_a = tensor_a.data();
    for(int i=0; i<L; i++) p_a[i] = i*2.0;

    double b =3.0;

    //Tensor_hao_ref<double,3> tensor_a_ref = tensor_a;
    Tensor_hao<double,3> tensor_c = tensor_a * b  ;

    vector<double> exact(L);
    for (int i = 0; i < L; ++i) exact[i] =  i*2.0*3.0;

    EXPECT_POINTER_DOUBLE_EQ( L, exact.data(), tensor_c.data() );
}

TEST(Tensor_element, div_T)
{
    Tensor_hao<double, 3> tensor_a(3, 4, 5);
    int L = tensor_a.size();
    double *p_a = tensor_a.data();
    for (int i = 0; i < L; i++) p_a[i] = i * 2.0;

    double b = 3.0;

    //Tensor_hao_ref<double,3> tensor_a_ref = tensor_a;
    Tensor_hao<double, 3> tensor_c = tensor_a / b;

    vector<double> exact(L);
    for (int i = 0; i < L; ++i) exact[i] = i * 2.0 / 3.0;

    EXPECT_POINTER_DOUBLE_EQ(L, exact.data(), tensor_c.data());
}

TEST(Tensor_element, diff)
{
    Tensor_hao<double,2>  tensor_a(3,4);
    Tensor_hao<double,2>  tensor_b(3,4);
    Tensor_hao_ref<double,2>  tensor_b_ref(tensor_b);
    tensor_a = {1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.};
    tensor_b = {1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.};

    EXPECT_FALSE( diff(tensor_a, tensor_b_ref, 1e-12) );
}