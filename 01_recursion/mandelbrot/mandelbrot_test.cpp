#include <gtest/gtest.h>
#include "mandelbrot.h"
#include <complex>

// Test that center point (0, 0) is in the Mandelbrot set
TEST(MandelbrotTest, CenterPointInSet) {
    int result = mandelbrot(std::complex<double>(0.0, 0.0), 100);
    EXPECT_EQ(result, 100);  // Should not diverge
}

// Test point left of center (-1, 0) is in the set
TEST(MandelbrotTest, LeftPointInSet) {
    int result = mandelbrot(std::complex<double>(-1.0, 0.0), 100);
    EXPECT_EQ(result, 100);  // Should not diverge
}

// Test point (-0.5, 0.5) is in the set
TEST(MandelbrotTest, PointMinusHalfHalfInSet) {
    int result = mandelbrot(std::complex<double>(-0.5, 0.5), 100);
    EXPECT_EQ(result, 100);  // Should not diverge
}

// Test point (0.5, 0.5) is outside the set (should diverge quickly)
TEST(MandelbrotTest, PointOutsideSet) {
    int result = mandelbrot(std::complex<double>(0.5, 0.5), 100);
    EXPECT_LT(result, 100);  // Should diverge before reaching max iterations
}

// Test point near the main bulb edge (-0.7, 0.27015)
TEST(MandelbrotTest, PointNearBulbEdge) {
    int result = mandelbrot(std::complex<double>(-0.7, 0.27015), 100);
    EXPECT_EQ(result, 100);  // Close to the edge but still in set
}

// Test point between bulbs (0.25, 0)
TEST(MandelbrotTest, PointBetweenBulbs) {
    int result = mandelbrot(std::complex<double>(0.25, 0.0), 100);
    EXPECT_EQ(result, 100);  // Should be in the set
}

// Test that increasing maxIterations doesn't change result for points outside set
TEST(MandelbrotTest, OutsideSetIndependentOfMaxIterations) {
    std::complex<double> point(0.5, 0.5);
    int result1 = mandelbrot(point, 50);
    int result2 = mandelbrot(point, 100);
    EXPECT_EQ(result1, result2);  // Should diverge at same iteration regardless
}

// Test with very small maxIterations
TEST(MandelbrotTest, SmallMaxIterations) {
    int result = mandelbrot(std::complex<double>(0.0, 0.0), 1);
    EXPECT_EQ(result, 1);  // Should return maxIterations for center point
}

// Test clearly diverging point (5, 5)
TEST(MandelbrotTest, ClearlyDiverging) {
    int result = mandelbrot(std::complex<double>(5.0, 5.0), 100);
    EXPECT_EQ(result, 0);  // Should diverge immediately at iteration 0
}

// Test another clearly diverging point (2, 2)
TEST(MandelbrotTest, AnotherDiverging) {
    int result = mandelbrot(std::complex<double>(2.0, 2.0), 100);
    EXPECT_EQ(result, 0);  // Should diverge immediately at iteration 0
}

