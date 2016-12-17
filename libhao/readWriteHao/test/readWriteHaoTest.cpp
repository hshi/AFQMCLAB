//
// Created by boruoshihao on 12/17/16.
//

#include <iostream>
#include "../include/readWriteHao.h"
#include "../../testHao/gtest_custom.h"

using namespace std;
using namespace tensor_hao;

TEST(readWriteHaoTest, checkFile)
{
    string filename = "readWriteTest.dat";
    removeFile(filename);
    EXPECT_FALSE( checkFile(filename) );

    if( MPIRank() == 0 ) system("touch readWriteTest.dat");
    EXPECT_TRUE( checkFile(filename) );
    removeFile(filename);
}