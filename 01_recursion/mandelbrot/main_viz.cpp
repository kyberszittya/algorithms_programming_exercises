#include "mandelbrot_visualizer.h"
#include <iostream>

int main() {
    try {
        std::cout << "Launching Mandelbrot Set Visualizer (OpenGL 3.3)..." << std::endl;
        std::cout << "Controls:" << std::endl;
        std::cout << "  Mouse Wheel - Zoom in/out" << std::endl;
        std::cout << "  Left Mouse Button + Drag - Pan around" << std::endl;
        std::cout << "  Up Arrow - Increase iterations" << std::endl;
        std::cout << "  Down Arrow - Decrease iterations" << std::endl;
        std::cout << "  R - Reset view" << std::endl;
        std::cout << "  ESC - Exit" << std::endl << std::endl;

        mandelbrot_visualizer visualizer(
            MandelbrotConstants::DEFAULT_WIDTH,
            MandelbrotConstants::DEFAULT_HEIGHT,
            "Mandelbrot Set Visualizer (OpenGL 3.3)"
        );
        visualizer.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
