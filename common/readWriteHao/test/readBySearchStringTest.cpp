//
// Created by boruoshihao on 6/24/17.
//
#include "../include/readBySearchString.h"
#include "../include/readWriteStringFile.h"
#include "../../testHao/gtest_custom.h"
#include "../../mpiHao/include/mpi_fun.h"

using namespace std;

class ReadBySearchStringTest: public ::testing::Test
{
 public:
    string filename="input_param";

    ReadBySearchStringTest()
    {
        if( MPIRank() == 0 )
        {
            ofstream file;
            file.open(filename, ios::out|ios::trunc);
            if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
            file<<setprecision(16)<<scientific;

            file<<"boola 1 \n";
            file<<"boolb 0 \n";
            file<<"boolc True \n";
            file<<"boold False \n";
            file<<"boole FalseDD \n";
            file<<"boolf 0.123 \n";

            file<<"boolaeq = 1 \n";
            file<<"boolbeq = 0 \n";
            file<<"boolceq = True \n";
            file<<"booldeq = False \n";
            file<<"booleeq = FalseDD \n";
            file<<"boolfeq = 0.123 \n";

            file<<"stringa 0.123 \n";
            file<<"stringb 0.347 \n";
            file<<"stringc 0.129 \n";
            file<<"stringaeq = 0.123 \n";
            file<<"stringbeq = 0.347 \n";
            file<<"stringceq = 0.129 \n";

            file<<"stringd (0.347,2.2) \n";
            file<<"stringe (1.219,3.3) \n";
            file<<"stringf (1.235,4.4) \n";
            file<<"stringdeq = (0.347,2.2) \n";
            file<<"stringeeq = (1.219,3.3) \n";
            file<<"stringfeq = (1.235,4.4) \n";

            file.close();
        }
        MPIBarrier();
    }

    ~ReadBySearchStringTest()
    {
        removeFile(filename);
    }
};

TEST_F(ReadBySearchStringTest, bool)
{
    int flag;
    bool data;

    flag=readBySearchString(data, "boola", filename);
    EXPECT_EQ(data, true);
    EXPECT_EQ(flag, 0);

    flag=readBySearchString(data, "boolb", filename);
    EXPECT_EQ(data, false);
    EXPECT_EQ(flag, 0);

    flag=readBySearchString(data, "boolc", filename);
    EXPECT_EQ(data, true);
    EXPECT_EQ(flag, 0);

    flag=readBySearchString(data, "boold", filename);
    EXPECT_EQ(data, false);
    EXPECT_EQ(flag, 0);

    flag=readBySearchString(data, "boolaeq", filename);
    EXPECT_EQ(data, true);
    EXPECT_EQ(flag, 0);

    flag=readBySearchString(data, "boolbeq", filename);
    EXPECT_EQ(data, false);
    EXPECT_EQ(flag, 0);

    flag=readBySearchString(data, "boolceq", filename);
    EXPECT_EQ(data, true);
    EXPECT_EQ(flag, 0);

    flag=readBySearchString(data, "booldeq", filename);
    EXPECT_EQ(data, false);
    EXPECT_EQ(flag, 0);

    flag = readBySearchString(data, "xxdfdfdffdfdfd", filename);
    EXPECT_EQ(flag, 1);

//    flag=readBySearchString(data, "boole", filename);
//    EXPECT_EQ(data, false);
//    EXPECT_EQ(flag, 0);

//    flag=readBySearchString(data, "booleeq", filename);
//    EXPECT_EQ(data, false);
//    EXPECT_EQ(flag, 0);
}

TEST_F(ReadBySearchStringTest, realNumber)
{
    int flag;
    double data;

    flag = readBySearchString(data, "stringa", filename);
    EXPECT_EQ(data, 0.123);
    EXPECT_EQ(flag, 0);

    flag = readBySearchString(data, "stringb", filename);
    EXPECT_EQ(data, 0.347);
    EXPECT_EQ(flag, 0);

    flag = readBySearchString(data, "stringc", filename);
    EXPECT_EQ(data, 0.129);
    EXPECT_EQ(flag, 0);

    flag = readBySearchString(data, "stringaeq", filename);
    EXPECT_EQ(data, 0.123);
    EXPECT_EQ(flag, 0);

    flag = readBySearchString(data, "stringbeq", filename);
    EXPECT_EQ(data, 0.347);
    EXPECT_EQ(flag, 0);

    flag = readBySearchString(data, "stringceq", filename);
    EXPECT_EQ(data, 0.129);
    EXPECT_EQ(flag, 0);

    flag = readBySearchString(data, "xxdfdfdffdfdfd", filename);
    EXPECT_EQ(flag, 1);
}

TEST_F(ReadBySearchStringTest, complexDoulbe)
{
    int flag;
    complex<double> data;

    flag = readBySearchString(data, "stringd", filename);
    EXPECT_EQ( data, complex<double>(0.347,2.2) );
    EXPECT_EQ(flag, 0);

    flag = readBySearchString(data, "stringe", filename);
    EXPECT_EQ( data, complex<double>(1.219,3.3) );
    EXPECT_EQ(flag, 0);

    flag = readBySearchString(data, "stringf", filename);
    EXPECT_EQ( data, complex<double>(1.235,4.4) );
    EXPECT_EQ(flag, 0);

    flag = readBySearchString(data, "stringdeq", filename);
    EXPECT_EQ( data, complex<double>(0.347,2.2) );
    EXPECT_EQ(flag, 0);

    flag = readBySearchString(data, "stringeeq", filename);
    EXPECT_EQ( data, complex<double>(1.219,3.3) );
    EXPECT_EQ(flag, 0);

    flag = readBySearchString(data, "stringfeq", filename);
    EXPECT_EQ( data, complex<double>(1.235,4.4) );
    EXPECT_EQ(flag, 0);

    flag = readBySearchString(data, "xxdfdfdffdfdfd", filename);
    EXPECT_EQ(flag, 1);
}