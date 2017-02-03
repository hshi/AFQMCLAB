//
// Created by boruoshihao on 9/22/16.
//

#include <iostream>
#include "../include/cluster.h"
#include "../../readWriteHao/include/readWriteHao.h"

using namespace std;

Cluster::Cluster() : L(0) {}

Cluster::Cluster(size_t L) : L(L) {}

Cluster::Cluster(const string& filename)
{
    read(filename);
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

void Cluster::read(const string &filename)
{
    readFile(L, filename);
}

void Cluster::write(const string &filename) const
{
    writeFile(L, filename);
}

#ifdef MPI_HAO
void MPIBcast(Cluster &buffer, int root, MPI_Comm const &comm)
{
    MPIBcast(buffer.L, root, comm);
    MPIBarrier();
}
#endif
