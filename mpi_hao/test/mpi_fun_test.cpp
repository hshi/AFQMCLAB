#include "gtest/gtest.h"
#include "../include/mpi_fun.h"
#include "../../test_hao/gtest_custom.h"

using namespace std;

#ifdef MPI_HAO

TEST (MPIBcast, int)
{
    int i=0;
    if(MPIRank()==0) i=2;
    MPIBcast(i);

    EXPECT_EQ (2, i);
}

TEST (MPIBcast, long)
{
    long i=0;
    if(MPIRank()==0) i=2;
    MPIBcast(i);

    EXPECT_EQ (2, i);
}

TEST (MPIBcast, longlong)
{
    long long i=0;
    if(MPIRank()==0) i=2;
    MPIBcast(i);

    EXPECT_EQ (2, i);
}

TEST (MPIBcast, size_t)
{
    size_t i=0;
    if(MPIRank()==0) i=2;
    MPIBcast(i);

    EXPECT_EQ (2, i);
}

TEST (MPIBcast, float)
{
    float i=0;
    if(MPIRank()==0) i=2.23;
    MPIBcast(i);

    EXPECT_FLOAT_EQ (2.23, i);
}

TEST (MPIBcast, double)
{
    double i=0;
    if(MPIRank()==0) i=2.23;
    MPIBcast(i);

    EXPECT_DOUBLE_EQ (2.23, i);
}

TEST (MPIBcast, complex_float)
{
    complex<float> i(0,0);
    if(MPIRank()==0) i=complex<float>(2.0, 2.2);
    MPIBcast(i);

    EXPECT_COMPLEXFLOAT_EQ(complex<float>(2.0, 2.2), i);
}

TEST (MPIBcast, complex_double)
{
    complex<double> i(0,0);
    if(MPIRank()==0) i=complex<double>(2.0, 2.2);
    MPIBcast(i);

    EXPECT_COMPLEXDOUBLE_EQ(complex<double>(2.0, 2.2), i);
}

TEST (MPIBcast, int_pointer)
{
    int a[3] = {};
    int b[3] = {1, 2, 3};
    if(MPIRank()==0)
    {
        for(int i=0; i<3; i++) a[i]=b[i];
    }
    MPIBcast(3,a);

    EXPECT_POINTER_EQ(3, b, a);
}

TEST (MPIBcast, double_pointer)
{
    double a[3] = {};
    double b[3] = {1.2, 3.6, 9.8};
    if(MPIRank()==0)
    {
        for(int i=0; i<3; i++) a[i]=b[i];
    }
    MPIBcast(3,a);

    EXPECT_POINTER_DOUBLE_EQ(3, b, a);
}

TEST (MPIBcast, complexdouble_pointer)
{
    complex<double> a[3] = {};
    complex<double> b[3] = { {1.2, 2.3}, {3.6, 7.8}, {9.8, 12.5} };
    if(MPIRank()==0)
    {
        for(int i=0; i<3; i++) a[i]=b[i];
    }
    MPIBcast(3,a);

    EXPECT_POINTER_COMPLEXDOUBLE_EQ(3, b, a);
}

TEST(MPISum, int)
{
    int i    = 2;
    int size = MPISize();
    int sum  = MPISum(i);

    if( MPIRank()==0 ) EXPECT_EQ(i*size, sum);
}

TEST(MPISum, long)
{
    long i    = 2;
    long size = MPISize();
    long sum  = MPISum(i);

    if( MPIRank()==0 ) EXPECT_EQ(i*size, sum);
}

TEST(MPISum, longlong)
{
    long long i    = 2;
    long long size = MPISize();
    long long sum  = MPISum(i);

    if( MPIRank()==0 ) EXPECT_EQ(i*size, sum);
}

TEST(MPISum, float)
{
    float i    = 2.0;
    float size = MPISize();
    float sum  = MPISum(i);

    if( MPIRank()==0 ) EXPECT_FLOAT_EQ(i*size, sum);
}

TEST(MPISum, double)
{
    double i    = 2.0;
    double size = MPISize();
    double sum  = MPISum(i);

    if( MPIRank()==0 ) EXPECT_DOUBLE_EQ(i*size, sum);
}

TEST(MPISum, complex_float)
{
    complex<float> i    ={2.0, 3.0};
    complex<float> size = MPISize();
    complex<float> sum  = MPISum(i);

    if( MPIRank()==0 ) EXPECT_COMPLEXFLOAT_EQ(i*size, sum);
}

TEST(MPISum, complex_double)
{
    complex<double> i    ={2.0, 3.0};
    complex<double> size = MPISize();
    complex<double> sum  = MPISum(i);

    if( MPIRank()==0 ) EXPECT_COMPLEXDOUBLE_EQ(i*size, sum);
}

#else

#endif
/*

 #ifdef MPI_HAO

void MPISum_double_pointer_test()
{   
    double s[3]={2,3,5};
    double r[3]={0,0,0};
    MPISum(3,s,r);
    
    if(MPIRank()==0)
    {
        int flag=0;
        for(int i=0; i<3; i++)
        {   
            if( abs( r[i]-s[i]*static_cast<double>(MPISize()) ) > 1e-12) flag++;
        }
        if(flag!=0) cout<<"Warning!!!!MPISum failed the double pointer test! rank: "<<0<<endl;
    }
    else
    {
        int flag=0;
        for(int i=0; i<3; i++)
        {   
            if( abs( r[i] ) > 1e-12) flag++;
        }
       if(flag!=0) cout<<"Warning!!!!MPISum failed the double pointer test! rank: "<<MPIRank()<<endl;

    }
 
}


void MPISum_complex_double_pointer_test()
{
    complex<double> s[3]={{2,3},{1,5},{7,8}};
    complex<double> r[3]={{0,0},{0,0},{0,0}};
    MPISum(3,s,r);
    
    if(MPIRank()==0)
    {
        int flag=0;
        for(int i=0; i<3; i++)
        {
            if( abs( r[i]-s[i]*static_cast<double>(MPISize()) ) > 1e-12) flag++;
        }
        if(flag!=0) cout<<"Warning!!!!MPISum failed the complex double pointer test! rank: "<<0<<endl;
    }
    else
    {
        int flag=0;
        for(int i=0; i<3; i++)
        {
            if( abs( r[i] ) > 1e-12) flag++;
        }
       if(flag!=0) cout<<"Warning!!!!MPISum failed the complex double pointer test! rank: "<<MPIRank()<<endl;

    }
   
}


void MPIGather_double_test()
{
    double i=MPIRank();
    double* v= nullptr;
    if(MPIRank()==0) v=new double[MPISize()];
   
    MPIGather(i,v);
    if(MPIRank()==0) 
    {
        for(int index=0; index<MPISize(); index++) 
        {
            if(abs(v[index]-index)>1e-12) cout<<"Warning!!!!MPIGather failed the double test! index: "<<index<<endl;
        }
    }
   
    if(MPIRank()==0) delete[] v;
}

void MPIGather_complex_double_test()
{
    complex<double>  i={MPIRank()*1.0,MPIRank()*2.0};
    complex<double>* v= nullptr;
    if(MPIRank()==0) v=new complex<double>[MPISize()];
    
    MPIGather(i,v);
    if(MPIRank()==0)
    {
        for(int index=0; index<MPISize(); index++)
        {
            if(abs(v[index]-complex<double>(index*1.0,index*2.0))>1e-12)
              cout<<"Warning!!!!MPIGather failed the complex double test! index: "<<index<<endl;
        }
    }
     
    if(MPIRank()==0) delete[] v;
}

void mpi_fun_test()
{
    MPIBcast_int_test();
    MPIBcast_long_test();
    MPIBcast_long_long_test();
    MPIBcast_sizet_test();
    MPIBcast_float_test();
    MPIBcast_double_test();
    MPIBcast_complex_float_test();
    MPIBcast_complex_double_test();
   
    MPIBcast_int_pointer_test();
    MPIBcast_double_pointer_test();
    MPIBcast_complex_double_pointer_test();
   
    MPISum_int_test();
    MPISum_long_test();
    MPISum_long_long_test();
    MPISum_float_test();
    MPISum_double_test();
    MPISum_complex_float_test();
    MPISum_complex_double_test();

    MPISum_double_pointer_test();
    MPISum_complex_double_pointer_test();
   
    MPIGather_double_test();
    MPIGather_complex_double_test();
}

#else
void mpi_fun_test()
{
    int flag;
    complex<double> buffer(1.9,2.3);
    if(MPISize()!=1) cout<<"Warning!!!!MPISize failed the serial test!"<<endl;
    if(MPIRank()!=0) cout<<"Warning!!!!MPIRank failed the serail test!"<<endl;
   
    MPIBcast(buffer);
    if( abs(buffer-complex<double>(1.9,2.3))>1e-12 ) cout<<"Warning!!!!MPIBcast failed the serial test!"<<endl;
    if( abs(MPISum(buffer)-complex<double>(1.9,2.3))>1e-12 ) cout<<"Warning!!!!MPISum failed the serial test!"<<endl;

    complex<double> a[3]={{2,3},{1,5},{7,8}};
    complex<double> b[3]={};
    MPISum(3,a,b);
    flag=0; for(int i=0; i<3; i++) { if( abs(a[i]-b[i])>1e-12 ) flag++;}   
    if(flag!=0) cout<<"Warning!!!!MPISum failed the serial pointer test!"<<endl;
}
#endif 

 */