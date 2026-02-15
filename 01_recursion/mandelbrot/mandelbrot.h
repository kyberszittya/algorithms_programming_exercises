#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <complex>

// Helper function for recursive Mandelbrot calculation
// Parameters:
//   c: Complex number to test
//   z: Current value in the iteration (starts at 0)
//   iteration: Current iteration count
//   maxIterations: Maximum number of iterations to perform
// Returns: Number of iterations before divergence (or maxIterations if it doesn't diverge)
int mandelbrot_recursive(std::complex<double> c, std::complex<double> z, int iteration, int maxIterations);

// Calculates the number of iterations before a complex number diverges in the Mandelbrot set
// Parameters:
//   c: Complex number to test
//   maxIterations: Maximum number of iterations to perform
// Returns: Number of iterations before divergence (or maxIterations if it doesn't diverge)
int mandelbrot(std::complex<double> c, int maxIterations);

#endif // MANDELBROT_H

