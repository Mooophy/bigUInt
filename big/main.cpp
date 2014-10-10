#include <iostream>
#include <string>
#include "biguint.h"



int main()
{
    bigUInt number0("42");
    bigUInt number1{number0};

    number0.print();
    std::cout << "\n";
    number1.print();
    std::cout << "\n";
    std::cout << number0;

    std::cout << "\nexit normally\n";
    return 0;
}
