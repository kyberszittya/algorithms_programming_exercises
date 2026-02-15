#ifndef FIBONACCI_PLOTTER_H
#define FIBONACCI_PLOTTER_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

namespace PlotterConstants {
    constexpr int DEFAULT_WIDTH = 800;
    constexpr int DEFAULT_HEIGHT = 600;
    constexpr float ZOOM_FACTOR = 1.1f;
    constexpr float GRID_STEP = 20.0f;
    constexpr float MAX_N_INDEX = 12.0f;
    constexpr float SPIRAL_RESOLUTION = 0.01f;
}

class fibonacci_plotter {
public:
    fibonacci_plotter(int width, int height, const std::string& title);
    ~fibonacci_plotter();

    void run();

private:
    void initGLFW();
    void initGLAD();
    void initShaders();
    void initData();
    void processInput();
    void render();

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
    unsigned int gridVAO, gridVBO;

    std::vector<float> vertices;
    std::vector<float> gridVertices;

    // Uniform locations
    int colorLoc;
    int zoomLoc;
    int panLoc;

    // View State
    float zoom = 1.0f;
    float panX = 0.0f;
    float panY = 0.0f;
    bool isDragging = false;
    double lastMouseX = 0.0;
    double lastMouseY = 0.0;
};

#endif //FIBONACCI_PLOTTER_H