//
// Created by boruoshihao on 10/17/16.
//

#ifndef AFQMCLIB_LANCZOSEXCEPTS_H
#define AFQMCLIB_LANCZOSEXCEPTS_H

#include<iostream>
#include<stdexcept>
#include<string>

class LanczosNotConverge_error: public std::runtime_error
{
 public:
    explicit LanczosNotConverge_error (const std::string& what_arg): runtime_error(what_arg) {};
};

#endif //AFQMCLIB_LANCZOSEXCEPT_H
