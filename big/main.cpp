#include <iostream>
#include <string>
#include "biguint.h"



int main()
{
    bigUInt d0("4477886678990000998622223344");
    bigUInt d1(d0);

    std::cout << d0 << std::endl << d1 << std::endl;

    d0.print();
    std::cout << "\n";
    d1.print();

    std::cout << "\nexit normally\n";
    return 0;
}
