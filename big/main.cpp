#include <iostream>
#include <string>
#include "biguint.h"



int main()
{
    bigUInt number0("9");
    number0.print();

    std::cout << "\n";
    number0.add(999999);
    number0.print();

    std::cout << "\nexit normally\n";
    return 0;
}
