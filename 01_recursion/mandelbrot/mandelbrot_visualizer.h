#ifndef MANDELBROT_VISUALIZER_H
#define MANDELBROT_VISUALIZER_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

namespace MandelbrotConstants {
    constexpr int DEFAULT_WIDTH = 1200;
    constexpr int DEFAULT_HEIGHT = 900;
    constexpr float ZOOM_FACTOR = 1.1f;
    constexpr int DEFAULT_MAX_ITERATIONS = 256;
    constexpr float DEFAULT_SCALE = 3.5f;
}

class mandelbrot_visualizer {
public:
    mandelbrot_visualizer(int width, int height, const std::string& title);
    ~mandelbrot_visualizer();

    void run();

private:
    void initGLFW();
    void initGLAD();
    void initShaders();
    void initData();
    void processInput();
    void render();
    void updateMandelbrotData();

    // Callbacks
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    int width;
    int height;
    std::string title;
    GLFWwindow* window;

    unsigned int shaderProgram;
    unsigned int VAO, VBO;

    std::vector<float> vertices;
    std::vector<float> colors;

    // Uniform locations
    int colorLoc;

    // View State
    double centerX = -0.5;  // Real part of center
    double centerY = 0.0;   // Imaginary part of center
    double scale = MandelbrotConstants::DEFAULT_SCALE;  // How many units are visible
    int maxIterations = MandelbrotConstants::DEFAULT_MAX_ITERATIONS;
    bool isDragging = false;
    double lastMouseX = 0.0;
    double lastMouseY = 0.0;
    bool needsUpdate = true;
};

#endif // MANDELBROT_VISUALIZER_H

