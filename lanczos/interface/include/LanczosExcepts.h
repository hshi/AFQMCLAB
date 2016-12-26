//
// Created by boruoshihao on 10/17/16.
//

#ifndef AFQMCLAB_LANCZOSEXCEPTS_H
#define AFQMCLAB_LANCZOSEXCEPTS_H

#include<iostream>
#include<stdexcept>
#include<string>

class Lanczos_error: public std::runtime_error
{
 public:
    explicit Lanczos_error (const std::string& what_arg): runtime_error(what_arg) {};
};

class LanczosNotConverge_error: public Lanczos_error
{
 public:
    explicit LanczosNotConverge_error (const std::string& what_arg): Lanczos_error(what_arg) {};
};

class LanczosLoseAccuracy_error: public Lanczos_error
{
 public:
    explicit LanczosLoseAccuracy_error (const std::string& what_arg): Lanczos_error(what_arg) {};
};

#endif //AFQMCLAB_LANCZOSEXCEPT_H