//! @note   several c++11 features are being used.
//!         to compile :
//!         g++ -std=c++11 -Wall main.cpp

#include <string>
#include <cstring>
#include <deque>
#include <iostream>
#include <algorithm>
#include "biguint.h"

inline char*
build_str(const std::string& buff)
{
    auto dest = new char[buff.size() + 1];
    std::copy(buff.begin(), buff.end(), dest);
    dest[buff.size()] = '\0';

    return dest;
}

//! default Ctor
bigUInt::bigUInt():
    p{new char[2]}
{
    p[0] = '0';
    p[1] = '\0';
}

//! Dtor
bigUInt::~bigUInt()
{
    delete[] p;
}

bigUInt::bigUInt(unsigned int n):
    p{build_str(std::to_string(n))}
{}

bigUInt::bigUInt(const char *s):
    p{build_str(s)}
{}

bigUInt::bigUInt(const bigUInt &x):
    p{build_str(x.get_p())}
{}

void bigUInt::print()
{
    std::cout << p;
}

std::ostream & operator<<(std::ostream &out, const bigUInt &x)
{
    return out << x.get_p();
}
