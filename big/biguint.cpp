//! @note   several c++11 features are being used.
//!         to compile :
//!         g++ -std=c++11 -Wall main.cpp

#include <string>
#include <cstring>
#include <deque>
#include <iostream>
#include <algorithm>
#include "biguint.h"

template<typename Iter>
inline char* build_str(Iter first, Iter last)
{
    auto dest = new char[last - first + 1];
    std::copy(first, last, dest);
    dest[last - first] = '\0';

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

bigUInt::bigUInt(unsigned int n)
{
    std::string num {std::to_string(n)};
    p = build_str(num.begin(), num.end());
}

bigUInt::bigUInt(const char *s)
{
    std::string num {s};
    p = build_str(num.begin(), num.end());
}

bigUInt::bigUInt(const bigUInt &x)
{
    std::string num {x.get_p()};
    p = build_str(num.begin(), num.end());
}

void bigUInt::add(unsigned int n)
{
    std::string lhs{p};
    std::string rhs{std::to_string(n)};
    std::deque<char> sum;
    auto l = lhs.end();
    auto r = rhs.end();
    unsigned carry = 0;
    while( l != lhs.begin() - 1  &&  r != rhs.begin() - 1)
    {
        unsigned digit_sum = *l++   +   *r++    +   carry   -   2 * 48;
        sum.push_front(digit_sum >= 10? digit_sum - 10  :   digit_sum);
        carry = digit_sum/10;
    }

    if(l == lhs.begin() - 1)    //left exausted
        while(r != rhs.begin() - 1)
        {
            unsigned digit_sum  =   *r++    +   carry   -   48;
            sum.push_front(digit_sum >= 10? digit_sum - 10  :   digit_sum);
            carry = digit_sum/10;
        }

    if(r == rhs.begin() - 1)    //right exausted
        while(l != lhs.begin() - 1)
        {
            unsigned digit_sum =    *l++    +   carry   -   48;
            sum.push_front(digit_sum >= 10? digit_sum - 10  :   digit_sum);
            carry = digit_sum/10;
        }


    char* new_data = build_str(sum.begin(), sum.end());
    delete[] p;
    p = new_data;
}

void bigUInt::print()
{
    std::cout << p;
}

std::ostream & operator<<(std::ostream &out, const bigUInt &x)
{
    return out << x.get_p();
}
