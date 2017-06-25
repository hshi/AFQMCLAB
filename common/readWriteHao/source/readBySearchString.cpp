//
// Created by boruoshihao on 6/24/17.
//
#include <algorithm>
#include "../include/readBySearchString.h"

using namespace std;

bool readBySearchStringIsNumber(const string &s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int readBySearchString(bool &data, const string & stringName, const string &filename)
{
    string firstElement;
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in File!!! "<<filename<<endl; exit(1);}
    while( file >> firstElement )
    {
        if( firstElement == stringName )
        {
            string str;
            file>>str;
            if( str == "=" ) file>>str;

            if(readBySearchStringIsNumber(str) )
            {
                data = stoi(str);
            }
            else
            {
                transform(str.begin(), str.end(), str.begin(), ::tolower);
                if( str == "true" ) data=true;
                else if( str == "false") data= false;
                else { cout<<"Error!!! Do not know the type of "<<stringName<<" "<<str<<endl; exit(1); }
            }
            return 0;
        }
        else
        {
            file.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }
    file.close();

    return 1;
}