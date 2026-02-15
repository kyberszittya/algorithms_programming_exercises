cmake_minimum_required(VERSION 3.20)
project(recursive_algorithms)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

# Add Google Test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add GLFW
FetchContent_Declare(
  glfw
  URL https://github.com/glfw/glfw/archive/refs/tags/3.3.8.zip
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)


# Print current source dir
message(STATUS "Current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")
# Add GLAD from common folder
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/glad/include)
file(GLOB BUTTERFLIES_SOURCES_C ${CMAKE_CURRENT_SOURCE_DIR}/../common/glad/src/*.c)
message(STATUS "Butterflies sources: ${BUTTERFLIES_SOURCES_C}")

# Library for Fibonacci logic
add_library(fibonacci_lib
        simple_fibonacci/fibonacci.cpp
        simple_fibonacci/fibonacci.h
)

# Main executable
add_executable(simple_fibonacci
        simple_fibonacci/simple_fibonacci.cpp
)
target_link_libraries(simple_fibonacci fibonacci_lib)

# Test executable
add_executable(fibonacci_test
        simple_fibonacci/fibonacci_test.cpp
)
target_link_libraries(fibonacci_test fibonacci_lib GTest::gtest_main)

# Plotter executable
add_executable(fibonacci_plotter
        simple_fibonacci/main_fibonacci_plotter.cpp
        simple_fibonacci/fibonacci_plotter.cpp
        simple_fibonacci/fibonacci_plotter.h
        ${BUTTERFLIES_SOURCES_C}
)
target_link_libraries(fibonacci_plotter fibonacci_lib glfw)

# Tower of Hanoi executable
add_executable(tower_of_hanoi tower_of_hanoi/main.cpp)

# Mandelbrot library
add_library(mandelbrot_lib
        mandelbrot/mandelbrot.cpp
        mandelbrot/mandelbrot.h
)

# Mandelbrot executable
add_executable(mandelbrot mandelbrot/main.cpp)
target_link_libraries(mandelbrot mandelbrot_lib)

# Mandelbrot test executable
add_executable(mandelbrot_test mandelbrot/mandelbrot_test.cpp)
target_link_libraries(mandelbrot_test mandelbrot_lib GTest::gtest_main)


include(GoogleTest)
gtest_discover_tests(fibonacci_test)
gtest_discover_tests(mandelbrot_test)

# Mandelbrot visualizer executable
add_executable(mandelbrot_viz
    mandelbrot/main_viz.cpp
        mandelbrot/mandelbrot_visualizer.cpp
        mandelbrot/mandelbrot_visualizer.h
    ${BUTTERFLIES_SOURCES_C}
)
target_link_libraries(mandelbrot_viz mandelbrot_lib glfw)
