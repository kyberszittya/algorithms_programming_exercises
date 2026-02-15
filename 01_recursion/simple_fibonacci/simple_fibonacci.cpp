//
// Created by keret on 2026. 02. 15..
//

#include <iostream>
#include <iomanip>
#include "fibonacci.h"

int main(int argc, char *argv[]) {
    std::cout << "n\tRecursive\tBinet" << std::endl;
    for (int i = 0; i <= 10; ++i) {
        std::cout << i << "\t"
                  << fibonacci(i) << "\t\t"
                  << std::fixed << std::setprecision(2) << fibonacci_binet(i)
                  << std::endl;
    }
    return 0;
}