#include <gtest/gtest.h>
#include "fibonacci.h"

TEST(FibonacciTest, BaseCases) {
    EXPECT_EQ(fibonacci(0), 0);
    EXPECT_EQ(fibonacci(1), 1);
    EXPECT_EQ(fibonacci(2), 1);
}

TEST(FibonacciTest, SmallNumbers) {
    EXPECT_EQ(fibonacci(2), 1);
    EXPECT_EQ(fibonacci(3), 2);
    EXPECT_EQ(fibonacci(4), 3);
    EXPECT_EQ(fibonacci(5), 5);
}

TEST(FibonacciTest, LargerNumber) {
    EXPECT_EQ(fibonacci(10), 55);
}

TEST(FibonacciBinetTest, BaseCases) {
    EXPECT_NEAR(fibonacci_binet(1), 1, 1e-2);
    EXPECT_NEAR(fibonacci_binet(9), 34, 1e-2);
    EXPECT_NEAR(fibonacci_binet(10), 55, 1e-2);
}