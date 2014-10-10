#include <iostream>
#include "biguint.h"

int main()
{
    bigUInt number0{"23"};
    bigUInt number1{"1"};

    auto sub = number0 - number1;

    sub.print();

    std::cout << "\nexit normally\n";
    return 0;
}
