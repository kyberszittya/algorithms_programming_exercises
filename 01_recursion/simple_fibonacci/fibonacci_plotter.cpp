#include "fibonacci_plotter.h"
#include "fibonacci.h"
#include <iostream>
#include <cmath>

using namespace PlotterConstants;

const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "uniform float uZoom;\n"
    "uniform vec2 uPan;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4((aPos.x + uPan.x) * uZoom, (aPos.y + uPan.y) * uZoom, 0.0, 1.0);\n"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 uColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = uColor;\n"
    "}\n\0";

fibonacci_plotter::fibonacci_plotter(int width, int height, const std::string& title)
    : width(width), height(height), title(title), window(nullptr) {
    initGLFW();
    initGLAD();
    initShaders();
    initData();
}

fibonacci_plotter::~fibonacci_plotter() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &gridVAO);
    glDeleteBuffers(1, &gridVBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}

void fibonacci_plotter::initGLFW() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);

    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void fibonacci_plotter::initGLAD() {
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        throw std::runtime_error("Failed to initialize OpenGL context");
    }
    glEnable(GL_MULTISAMPLE);
}

void fibonacci_plotter::initShaders() {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    colorLoc = glGetUniformLocation(shaderProgram, "uColor");
    zoomLoc = glGetUniformLocation(shaderProgram, "uZoom");
    panLoc = glGetUniformLocation(shaderProgram, "uPan");
}

void fibonacci_plotter::initData() {
    float max_theta = MAX_N_INDEX * 3.14159265f / 2.0f;
    float max_radius = (float)fibonacci_real_binet(MAX_N_INDEX);
    float aspect_ratio = (float)width / (float)height;

    // Generate Grid
    int grid_count = (int)(max_radius / GRID_STEP);
    for (int i = -grid_count; i <= grid_count; ++i) {
        float x = (float)i * GRID_STEP;
        float ndc_x = (x / max_radius) * 0.9f / aspect_ratio;
        gridVertices.push_back(ndc_x); gridVertices.push_back(-0.9f);
        gridVertices.push_back(ndc_x); gridVertices.push_back(0.9f);
    }
    for (int i = -grid_count; i <= grid_count; ++i) {
        float y = (float)i * GRID_STEP;
        float ndc_y = (y / max_radius) * 0.9f;
        float x_limit = 0.9f / aspect_ratio;
        gridVertices.push_back(-x_limit); gridVertices.push_back(ndc_y);
        gridVertices.push_back(x_limit);  gridVertices.push_back(ndc_y);
    }

    // Generate Spiral
    for (float theta = 0.0f; theta <= max_theta; theta += SPIRAL_RESOLUTION) {
        double n = theta * 2.0 / 3.14159265;
        double r = fibonacci_real_binet(n);
        float x = (float)(r * std::cos(theta));
        float y = (float)(r * std::sin(theta));
        float ndc_x = (x / max_radius) * 0.9f / aspect_ratio;
        float ndc_y = (y / max_radius) * 0.9f;
        vertices.push_back(ndc_x);
        vertices.push_back(ndc_y);
    }

    glGenVertexArrays(1, &gridVAO);
    glGenBuffers(1, &gridVBO);
    glBindVertexArray(gridVAO);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    glBufferData(GL_ARRAY_BUFFER, gridVertices.size() * sizeof(float), gridVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void fibonacci_plotter::run() {
    while (!glfwWindowShouldClose(window)) {
        processInput();
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void fibonacci_plotter::processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void fibonacci_plotter::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glUniform1f(zoomLoc, zoom);
    glUniform2f(panLoc, panX, panY);

    // Draw Grid
    glUniform4f(colorLoc, 0.5f, 0.5f, 0.5f, 1.0f);
    glBindVertexArray(gridVAO);
    glDrawArrays(GL_LINES, 0, gridVertices.size() / 2);

    // Draw Plot
    glUniform4f(colorLoc, 1.0f, 0.5f, 0.2f, 1.0f);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_STRIP, 0, vertices.size() / 2);
}

// Static Callbacks
void fibonacci_plotter::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    auto* plotter = static_cast<fibonacci_plotter*>(glfwGetWindowUserPointer(window));
    if (yoffset > 0)
        plotter->zoom *= ZOOM_FACTOR;
    else
        plotter->zoom /= ZOOM_FACTOR;
}

void fibonacci_plotter::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    auto* plotter = static_cast<fibonacci_plotter*>(glfwGetWindowUserPointer(window));
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            plotter->isDragging = true;
            glfwGetCursorPos(window, &plotter->lastMouseX, &plotter->lastMouseY);
        } else if (action == GLFW_RELEASE) {
            plotter->isDragging = false;
        }
    }
}

void fibonacci_plotter::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    auto* plotter = static_cast<fibonacci_plotter*>(glfwGetWindowUserPointer(window));
    if (plotter->isDragging) {
        float dx = (float)(xpos - plotter->lastMouseX) / (plotter->width / 2.0f);
        float dy = (float)(plotter->lastMouseY - ypos) / (plotter->height / 2.0f);

        plotter->panX += dx / plotter->zoom;
        plotter->panY += dy / plotter->zoom;

        plotter->lastMouseX = xpos;
        plotter->lastMouseY = ypos;
    }
}

void fibonacci_plotter::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    auto* plotter = static_cast<fibonacci_plotter*>(glfwGetWindowUserPointer(window));
    plotter->width = width;
    plotter->height = height;
    glViewport(0, 0, width, height);
}