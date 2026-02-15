#include "fibonacci_plotter.h"
#include <iostream>

int main() {
    try {
        fibonacci_plotter plotter(PlotterConstants::DEFAULT_WIDTH, PlotterConstants::DEFAULT_HEIGHT, "Fibonacci Plotter (OpenGL 3.3)");
        plotter.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}