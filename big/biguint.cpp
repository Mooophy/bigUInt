//! @note   several c++11 features are being used.
//!         to compile :
//!         g++ -std=c++11 -Wall main.cpp

#include <iostream>
#include <string>
#include <stdexcept>
#include <list>
#include <assert.h>
#include "biguint.h"

//! using 'h' (head) as the sentinel.
inline char
gen_digit(char number)
{
    return number + 48;
}

inline unsigned
size(const char* p, char end)
{
    assert(p);

    unsigned ret = 0;
    for(; *p != end; ++p)
        ++ret;

    return ret;
}

inline unsigned
how_many_digit(unsigned int num)
{
    unsigned ret = 1;
    for(; num > 9; num /= 10)
        ++ret;

    return ret;
}

//! default Ctor
bigUInt::bigUInt():
    p(new char[2])
{
    p[0] = gen_digit(0);
    p[1] = 'h';
}

/**
 * @brief bigUInt::bigUInt
 * @param unsigned int
 */
bigUInt::bigUInt(unsigned int n)
{
    std::string buff = std::to_string(n);

    //! allocate p and set tail
    p = new char[buff.size() + 1];
    assert(p);
    auto curr = p + buff.size();
    *curr-- = 'h';

    //! fill the rest
    for(auto digit : buff)
        *curr-- = digit;
}

/**
 * @brief bigUInt::bigUInt
 * @param const char *
 */
bigUInt::bigUInt(const char *s)
{
    std::string buff(s);

    //! allocate p and set tail
    p = new char[buff.size() + 1];
    assert(p);
    auto curr = p + buff.size();
    *curr-- = 'h';

    //! fill the rest
    for(auto digit : buff)
        *curr-- = digit;
}

/**
 * @brief copy ctor
 * @param x
 */
bigUInt::bigUInt(const bigUInt &x):
    p(new char[size(x.get_p(), 'h')])
{
    auto sour = x.get_p();
    auto dest = p;
    while(*sour != 'h')
        *dest++     =   *sour++;
    *dest = 'h';
}

//! Dtor
bigUInt::~bigUInt()
{
    delete[] p;
}

std::ostream&
operator<<(std::ostream &out, const bigUInt &x)
{
    for(unsigned curr = size(x.get_p(), 'h'); curr != 0; --curr)
        std::cout << x.get_p()[curr - 1];
    return out;
}
