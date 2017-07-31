//
// Created by boruoshihao on 9/22/16.
//

#ifndef AFQMCLAB_CLUSTER_H
#define AFQMCLAB_CLUSTER_H

#include <string>
#include "../../mpiHao/include/mpi_fun.h"

#ifdef MPI_HAO
class Cluster;
void MPIBcast(Cluster &buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
#endif

class Cluster
{
 private:
    size_t L;

 public:
    Cluster();
    Cluster(size_t L);
    Cluster(const std::string& filename);
    Cluster(const Cluster &x);
    Cluster(Cluster &&x);
    ~Cluster();

    Cluster& operator  = (const Cluster& x);
    Cluster& operator  = (Cluster&& x);

    size_t getL() const;

    void read(const std::string &filename);
    void write(const std::string &filename) const;

#ifdef MPI_HAO
    friend void MPIBcast(Cluster &buffer, int root,  const MPI_Comm& comm);
#endif
};
#endif //AFQMCLAB_CLUSTER_H