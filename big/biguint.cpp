//! @note   several c++11 features are being used.
//!         to compile :
//!         g++ -std=c++11 -Wall main.cpp

#include <string>
#include <deque>
#include <iostream>
#include <algorithm>
#include "biguint.h"

template<typename Iter>
inline char* make_new_data(Iter first, Iter last)
{
    auto dest = new char[last - first + 1];
    std::copy(first, last, dest);
    dest[last - first] = '\0';

    return dest;
}

char* add_str_num(const std::string& lhs, const std::string& rhs)
{
    std::deque<char> sum;

    auto l = lhs.end() - 1;
    auto r = rhs.end() - 1;
    unsigned carry = 0;
    while( l != lhs.begin() - 1  &&  r != rhs.begin() - 1)
    {
        unsigned digit_sum = *l--   +   *r--    +   carry   -   2 * 48;
        sum.push_front((digit_sum >= 10? digit_sum - 10  :   digit_sum) + 48);
        carry = digit_sum/10;
    }

    if(l == lhs.begin() - 1)    //left exausted
        while(r != rhs.begin() - 1)
        {
            unsigned digit_sum  =   *r--    +   carry   -   48;
            sum.push_front((digit_sum >= 10? digit_sum - 10  :   digit_sum) + 48);
            carry = digit_sum/10;
        }

    if(r == rhs.begin() - 1)    //right exausted
        while(l != lhs.begin() - 1)
        {
            unsigned digit_sum =    *l--    +   carry   -   48;
            sum.push_front((digit_sum >= 10? digit_sum - 10  :   digit_sum) + 48);
            carry = digit_sum/10;
        }

    if(carry)
        sum.push_front(carry + 48);

    char* new_data = make_new_data(sum.begin(), sum.end());
    return new_data;
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
    p = make_new_data(num.begin(), num.end());
}

bigUInt::bigUInt(const char *s)
{
    std::string num {s};
    p = make_new_data(num.begin(), num.end());
}

bigUInt::bigUInt(const bigUInt &x)
{
    std::string num {x.get_p()};
    p = make_new_data(num.begin(), num.end());
}

void bigUInt::add(unsigned int n)
{
    std::string lhs{p};
    std::string rhs{std::to_string(n)};
    char* new_data = add_str_num(lhs,rhs);

    delete[] p;
    p = new_data;
}

void bigUInt::add(const bigUInt &x)
{
    std::string lhs{p};
    std::string rhs{x.get_p()};
    char* new_data = add_str_num(lhs,rhs);

    delete[] p;
    p = new_data;
}

void bigUInt::increment()
{
    add(1);
}

bigUInt bigUInt::operator+(const bigUInt &x)
{
    bigUInt ret{*this};
    ret.add(x);
    return ret;
}

bigUInt& bigUInt::operator=(const bigUInt &x)
{
    std::string buff{x.get_p()};
    char* new_data = make_new_data(buff.begin(), buff.end());
    delete[] p;
    p = new_data;

    return *this;
}

void bigUInt::print()
{
    std::cout << p;
}

std::ostream & operator<<(std::ostream &out, const bigUInt &x)
{
    return out << x.get_p();
}
