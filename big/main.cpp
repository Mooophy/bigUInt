#include <iostream>
#include "biguint.h"

int main()
{
    bigUInt number0{99999999};
    bigUInt number1{"99999999"};

    auto sub = number0 - number1;

    sub.print();

    std::cout << std::endl << sub << std::endl;

    std::cout << "\nexit normally\n";
    return 0;
}
