//
// Created by boruoshihao on 6/24/17.
//

#ifndef AFQMCLAB_READBYSEARCHSTRING_H
#define AFQMCLAB_READBYSEARCHSTRING_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <complex>
#include <limits>
#include <iomanip>

int readBySearchString(bool &data, const std::string & stringName, const std::string &filename);

template<class T> int readBySearchString(T &data, const std::string & stringName, const std::string &filename)
{
    std::string firstElement;
    std::ifstream file;
    file.open(filename, std::ios::in);
    if ( ! file.is_open() ) {std::cout << "Error opening file in File!!! "<<filename<<std::endl; exit(1);}
    while( file >> firstElement )
    {
        if( firstElement == stringName )
        {
            std::string str;
            file>>str;
            if( str == "=" ) file>>str;
            std::istringstream iss(str);
            iss>>data;
            return 0;
        }
        else
        {
            file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
    }
    file.close();

    return 1;
}
#endif //AFQMCLAB_READBYSEARCHSTRING_H