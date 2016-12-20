//
// Created by boruoshihao on 9/22/16.
//

#ifndef AFQMCLIB_CLUSTER_H
#define AFQMCLIB_CLUSTER_H

#include <string>

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
};

#endif //AFQMCLIB_CLUSTER_H