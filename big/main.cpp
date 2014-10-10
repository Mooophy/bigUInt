#include <iostream>
#include <string>
#include "biguint.h"

int main()
{
    bigUInt number0{"9"};
    bigUInt number1{"1000"};
    number0.print();

    std::cout << "\n";
    number0.add(number1);
    number0.print();

    std::cout << "\nexit normally\n";
    return 0;
}
