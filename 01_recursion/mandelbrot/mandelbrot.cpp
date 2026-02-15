#include "mandelbrot.h"

// Helper function for recursive Mandelbrot calculation
int mandelbrot_recursive(std::complex<double> c, std::complex<double> z, int iteration, int maxIterations) {
    // Base cases
    if (iteration == maxIterations) {
        return maxIterations;  // Didn't diverge within max iterations
    }

    if (std::abs(z) > 2.0) {
        return iteration;  // Diverged
    }

    // Recursive case: z = z^2 + c
    return mandelbrot_recursive(c, z * z + c, iteration + 1, maxIterations);
}

// Calculates the number of iterations before a complex number diverges in the Mandelbrot set
int mandelbrot(std::complex<double> c, int maxIterations) {
    return mandelbrot_recursive(c, std::complex<double>(0.0, 0.0), 0, maxIterations);
}

