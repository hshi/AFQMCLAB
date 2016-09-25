//
// Created by boruoshihao on 9/22/16.
//

#ifndef AFQMCLIB_CLUSTER_H
#define AFQMCLIB_CLUSTER_H

#include <string>

class Cluster
{
 private:
    int L;

 public:
    Cluster();
    Cluster(int L);
    Cluster(const std::string& filename);
    Cluster(const Cluster &x);
    Cluster(Cluster &&x);
    ~Cluster();

    Cluster& operator  = (const Cluster& x);
    Cluster& operator  = (Cluster&& x);

    int getL() const;
};

#endif //AFQMCLIB_CLUSTER_H