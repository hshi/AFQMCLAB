//
// Created by boruoshihao on 9/22/16.
//

#include <fstream>
#include "cluster.h"
#include "../../libhao/mpi_hao/mpi_fun.h"

using namespace std;

Cluster::Cluster() : L(0) {}

Cluster::Cluster(int L) : L(L) {}

Cluster::Cluster(const string& filename)
{
    int rank = MPIRank();
    if(rank==0)
    {
        ifstream latt_file;
        latt_file.open(filename,ios::in);
        if ( ! latt_file.is_open() ) { cout<<"Error opening file!!!"<<endl;  exit(1); }
        latt_file>>L;
        latt_file.close();
    }
    MPIBcast(L);
    MPIBarrier();
}

Cluster::Cluster(const Cluster &x) : L(x.L) {}

Cluster::Cluster(Cluster &&x) : L(x.L) {}

Cluster::~Cluster() {}

Cluster& Cluster::operator  = (const Cluster& x)
{
    L=x.L;
    return *this;
}

Cluster& Cluster::operator  = (Cluster&& x)
{
    L=x.L;
    return *this;
}

int Cluster::getL() const
{
    return L;
}