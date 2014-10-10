#include <iostream>
#include "biguint.h"

int main()
{
    bigUInt number0{"9"};
    bigUInt number1{"1001"};

    (number0 + number1).print();

    //    number0.print();

//    std::cout << "\n";
//    number0.add(number1);
//    number0.increment();
//    number0.print();

//    bigUInt sum = number0 + number0;
//    std::cout << "\n";
//    sum.print();

    std::cout << "\nexit normally\n";
    return 0;
}
