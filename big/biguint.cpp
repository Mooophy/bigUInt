//! @note   several c++11 features are being used.
//!         to compile :
//!         g++ -std=c++11 -Wall main.cpp
//!
//! @test   tested on g++ 4.8.2
//!

#include <string>
#include <deque>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cstring>
#include "biguint.h"

template<typename Iter>
inline char* make_new_data(Iter first, Iter last)
{
    auto data = new char[last - first + 1];
    std::copy(first, last, data);
    data[last - first] = '\0';

    return data;
}

template<typename C>
inline C operator +=(C& lhs, int rhs)
{
    for(auto& elem : lhs)
        elem += rhs;
    return lhs;
}

template<typename Iter>
std::ostream&
print_without_leading_zero(Iter first, Iter last, std::ostream& out)
{
    auto non_zero = first;
    for( ; non_zero != last && *non_zero == '0'; ++non_zero);

    if(non_zero == last)
        out << "0";
    else
        for(auto it = non_zero; it != last; ++it)
            out << *it;

    return out;
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

inline bool
operator <(const bigUInt& lhs, const bigUInt& rhs)
{

    auto l = strlen(lhs.get_p());
    auto r = strlen(rhs.get_p());

    return  l < r?  true    :
                    (l > r? false   :
                            (strcmp(lhs.get_p(),rhs.get_p()) < 0));
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

/**
 * @brief Ctor
 * @param unsigned
 */
bigUInt::bigUInt(unsigned int n)
{
    std::string num {std::to_string(n)};
    p = make_new_data(num.begin(), num.end());
}

/**
 * @brief Ctor
 * @param const char*
 */
bigUInt::bigUInt(const char *s)
{
    std::string num {s};
    p = make_new_data(num.begin(), num.end());
}

/**
 * @brief Ctor
 * @param bigUInt
 */
bigUInt::bigUInt(const bigUInt &x)
{
    std::string num {x.get_p()};
    p = make_new_data(num.begin(), num.end());
}

/**
 * @brief add
 * @param unsigned
 */
void bigUInt::add(unsigned int n)
{
    std::string lhs{p};
    std::string rhs{std::to_string(n)};
    char* new_data = add_str_num(lhs,rhs);

    delete[] p;
    p = new_data;
}

/**
 * @brief add
 * @param const bigUInt&
 */
void bigUInt::add(const bigUInt &x)
{
    std::string lhs{p};
    std::string rhs{x.get_p()};
    char* new_data = add_str_num(lhs,rhs);

    delete[] p;
    p = new_data;
}

/**
 * @brief increment
 */
void bigUInt::increment()
{
    add(1);
}

/**
 * @brief operator +
 * @param const bigUInt&
 * @return bigUInt
 */
bigUInt bigUInt::operator+(const bigUInt &x)
{
    bigUInt ret{*this};
    ret.add(x);
    return ret;
}

/**
 * @brief operator -
 * @param bigUInt
 * @return bigUInt
 */
bigUInt bigUInt::operator-(const bigUInt &x)
{
    if(*this < x)
        throw std::runtime_error{"invalid subtraction"};

    std::string lhs{get_p()};
    std::string rhs{x.get_p()};
    std::deque<char>  sub{};
    lhs +=  -48;
    rhs +=  -48;

    auto l = lhs.end() - 1;
    auto r = rhs.end() - 1;
    char prev = 0, next = 0;
    for (char digit_sub = 0; r != rhs.begin() - 1;    prev = next)
    {
        next        =   *l < (*r + prev)?    1   :   0;
        digit_sub   =   next * 10   +   *l--    -   prev    -   *r--;
        sub.push_front(digit_sub);
    }
    for (char digit_sub  = 0; l != lhs.begin() - 1;   prev = next)
    {
        next        =   *l < prev?    1   :   0;
        digit_sub   =   next * 10   +   *l--    -   prev;
        sub.push_front(digit_sub);
    }
    sub += 48;

    auto new_data = make_new_data(sub.begin(), sub.end());
    delete[] p;
    p = new_data;

    return *this;
}

/**
 * @brief copy assignment
 * @param bigUInt
 * @return bigUInt
 */
bigUInt& bigUInt::operator=(const bigUInt &x)
{
    std::string buff{x.get_p()};
    char* new_data = make_new_data(buff.begin(), buff.end());
    delete[] p;
    p = new_data;

    return *this;
}

/**
 * @brief print
 */
void bigUInt::print()
{
    std::string buff{p};
    print_without_leading_zero(buff.cbegin(),buff.cend(),std::cout);
}

/**
 * @brief operator <<
 * @param out
 * @param bigUInt
 * @return out
 */
std::ostream & operator<<(std::ostream &out, const bigUInt &x)
{
    std::string buff{x.get_p()};
    return print_without_leading_zero(buff.cbegin(),buff.cend(),out);
}
