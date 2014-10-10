#include <iostream>
#include "biguint.h"

int main()
{
    bigUInt number0{"9"};
    bigUInt number1{"1001"};

    auto sub = number0 - number1;

    std::cout << "\nexit normally\n";
    return 0;
}
