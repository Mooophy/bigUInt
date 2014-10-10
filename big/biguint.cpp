#include <iostream>
#include <string>
#include "biguint.h"

char gen_digit(char number)
{
    return number + 48;
}

//! default Ctor
bigUInt::bigUInt():
    p(new char[2])
{
    p[0] = gen_digit(0);
    p[1] = '\0';
}

//! Dtor
bigUInt::~bigUInt()
{
    delete[] p;
}

std::ostream & operator<<(std::ostream &out, const bigUInt &x)
{
    out << x.get_p();
    return out;
}
