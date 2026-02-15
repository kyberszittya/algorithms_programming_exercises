//
// Created by keret on 2026. 02. 15..
//

#include <iostream>
#include <complex>
#include "mandelbrot.h"

int main() {
    std::cout << "=== Mandelbrot Set Recursive Calculator ===" << std::endl << std::endl;

    int maxIterations = 100;

    // Test some points in the complex plane
    std::complex<double> testPoints[] = {
        std::complex<double>(0.0, 0.0),      // Center (definitely in set)
        std::complex<double>(-1.0, 0.0),     // Left of center (in set)
        std::complex<double>(-0.5, 0.5),     // In the set
        std::complex<double>(0.5, 0.5),      // Outside the set
        std::complex<double>(-0.7, 0.27015), // Near the main bulb edge
        std::complex<double>(0.25, 0.0)      // Between bulbs
    };

    std::cout << "Testing points with maxIterations = " << maxIterations << ":" << std::endl;
    for (const auto& point : testPoints) {
        int iterations = mandelbrot(point, maxIterations);
        std::cout << "Point (" << point.real() << ", " << point.imag() << "): "
                  << iterations << " iterations";
        if (iterations == maxIterations) {
            std::cout << " (IN SET)";
        } else {
            std::cout << " (outside set)";
        }
        std::cout << std::endl;
    }

    return 0;
}