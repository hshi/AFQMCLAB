//
// Created by boruoshihao on 12/20/16.
//

#ifndef AFQMCLIB_SUPERCUBIC_H
#define AFQMCLIB_SUPERCUBIC_H

#include<complex>
#include<vector>
#include<string>
#include "../../tensorHao/include/tensor_all.h"

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

 private:
    void read(const std::string &filename);
    void copy_deep(const Supercubic& x);
    void move_deep(Supercubic& x);
};

#endif //AFQMCLIB_SUPERCUBIC_H