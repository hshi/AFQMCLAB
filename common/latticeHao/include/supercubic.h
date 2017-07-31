//
// Created by boruoshihao on 12/20/16.
//

#ifndef AFQMCLAB_SUPERCUBIC_H
#define AFQMCLAB_SUPERCUBIC_H

#include<complex>
#include<vector>
#include<string>
#include "../../tensorHao/include/tensor_all.h"

#ifdef MPI_HAO
class Supercubic;
void MPIBcast(Supercubic &buffer, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
#endif

class Supercubic
{
 private:
    tensor_hao::TensorHao<int, 1> n;
    size_t L;

 public:
    Supercubic();
    Supercubic(const tensor_hao::TensorHao<int, 1> &n);
    Supercubic(const std::string &filename);
    Supercubic(const Supercubic& x);
    Supercubic(Supercubic&& x);
    ~Supercubic();

    Supercubic& operator  = (const Supercubic& x);
    Supercubic& operator  = (Supercubic&& x);

    const tensor_hao::TensorHao<int, 1> &getN() const;
    size_t getDimen() const;
    size_t getL() const;

    tensor_hao::TensorHao<int,1> coor(int lattice_index) const;
    int index(const tensor_hao::TensorHao<int,1> &lattice_coor) const;
    int bound(const int i, const int i_max) const;
    tensor_hao::TensorHao<int,1> coor_relat(const tensor_hao::TensorHao<int,1>& coor_i,
                                            const tensor_hao::TensorHao<int,1>& coor_j) const; // return coor_j-coor_i
    tensor_hao::TensorHao<int,1> coor_abs_relat(const tensor_hao::TensorHao<int,1>& coor_i,
                                                const tensor_hao::TensorHao<int,1>& coor_j) const;
    int inverse(int lattice_index) const;

    void read(const std::string &filename);
    void write(const std::string &filename) const;

#ifdef MPI_HAO
    friend void MPIBcast(Supercubic &buffer, int root,  const MPI_Comm& comm);
#endif

 private:
    void copy_deep(const Supercubic& x);
    void move_deep(Supercubic& x);
};

std::tuple< tensor_hao::TensorHao<size_t , 1> , tensor_hao::TensorHao<size_t , 1> , tensor_hao::TensorHao<std::complex<double>, 1>  >
getNearestNeighborHopping(const Supercubic &latt, double t1, const tensor_hao::TensorHao<double, 1> &k);

tensor_hao::TensorHao<double, 1> getNearestNeighborDispersion(const Supercubic &latt, double t1,
                                                              const tensor_hao::TensorHao<double, 1> &k);

tensor_hao::TensorHao<double, 1> getContinuousDispersion(const Supercubic &latt, double t1,
                                                         const tensor_hao::TensorHao<double, 1> &k);
#endif //AFQMCLAB_SUPERCUBIC_H