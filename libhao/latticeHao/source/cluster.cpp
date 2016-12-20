//
// Created by boruoshihao on 9/22/16.
//

#include <iostream>
#include "../include/cluster.h"
#include "../../mpiHao/include/mpi_fun.h"
#include "../../readWriteHao/include/readWriteHao.h"

using namespace std;

Cluster::Cluster() : L(0) {}

Cluster::Cluster(size_t L) : L(L) {}

Cluster::Cluster(const string& filename)
{
    if( MPIRank() == 0 ) readFile(L, filename);
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

size_t Cluster::getL() const
{
    return L;
}
