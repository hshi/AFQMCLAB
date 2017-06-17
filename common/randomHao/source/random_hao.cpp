#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include <string>
#include "../include/random_hao.h"

using namespace std;

void randomHaoInit(int seed, int gtype)
{
    MPIBcast(seed);
    MPIBcast(gtype);

    if(seed==-1) //If seed is -1, start from last run
    {
        randomHaoRead();
    }
    else if(seed==0) //If seed is 0, random set the seed
    {
        seed = make_sprng_seed();
        init_sprng(gtype,seed,SPRNG_DEFAULT);
    }
    else
    {
        init_sprng(gtype,seed,SPRNG_DEFAULT);
    }
}

void randomHaoRead()
{
    int size;
    char buffer[MAX_PACKED_LENGTH];

    int rank=MPIRank();
    string filename="./random/checkpoint_"+ to_string(rank) +".dat";
    FILE *fp = fopen(filename.c_str(),"r"); //use the example code from sprng
    fread(&size,1,sizeof(int),fp);
    fread(buffer,1,size,fp);
    unpack_sprng(buffer);
    fclose(fp);
}

void randomHaoSave()
{
    //Backup random seeds generated before
    MPIBarrier();
    if( MPIRank() == 0)
    {
        int flag(0);
        flag+=system("mkdir -p random");
        flag+=system("rm -rf random.bk");
        flag+=system("mkdir -p random.bk");
        flag+=system("mv random/* random.bk");
        if(flag != 0) cout<<"WARNING!!! system command does not exit properly!"<<endl;
    }
    MPIBarrier();

    int size;
    char *bytes;

    size = pack_sprng(&bytes);

    int rank=MPIRank();
    string filename="./random/checkpoint_"+ to_string(rank) +".dat";
    FILE *fp = fopen(filename.c_str(),"w"); //use the example code from sprng 
    fwrite(&size,1,sizeof(int),fp); 
    fwrite(bytes,1,size,fp); 
    fclose(fp);
    free(bytes);	
}

double uniformHao()
{
    return sprng();
}

double gaussianHao()
{
#define pi 3.14159265358979324
    double tmp=sprng();
    //log(tmp) will be NA, if tmp==0
    if(tmp==0) tmp+=1e-300;
    return sqrt(-2.0*log(tmp))*cos(2.0*pi*sprng());
}