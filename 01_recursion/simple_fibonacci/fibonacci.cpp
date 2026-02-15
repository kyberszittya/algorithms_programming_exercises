#include "fibonacci.h"
#include <cmath>

unsigned long fibonacci(int n) {
    if (n == 0 || n == 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

double fibonacci_binet(double n) {
    using namespace BinetConstants;
    return (std::pow(PHI, n) - std::pow(PSI, n)) / SQRT_5;
}

double fibonacci_real_binet(double n) {
    using namespace BinetConstants;
    const double PI = 3.14159265358979323846;
    return (std::pow(PHI, n) - std::cos(n * PI) * std::pow(PHI, -n)) / SQRT_5;
}