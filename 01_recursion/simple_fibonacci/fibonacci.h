#ifndef FIBONACCI_H
#define FIBONACCI_H

#include <cmath>

namespace BinetConstants {
    const double SQRT_5 = std::sqrt(5);
    const double PHI = (1.0 + SQRT_5) / 2.0;
    const double PSI = (1.0 - SQRT_5) / 2.0;
}

unsigned long fibonacci(int n);

double fibonacci_binet(double n);

double fibonacci_real_binet(double n);


#endif //FIBONACCI_H