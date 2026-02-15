#include "mandelbrot_visualizer.h"
#include "mandelbrot.h"
#include <iostream>
#include <cmath>

using namespace MandelbrotConstants;

const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 0.0, 1.0);\n"
    "   vertexColor = aColor;\n"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "in vec3 vertexColor;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(vertexColor, 1.0);\n"
    "}\n\0";

mandelbrot_visualizer::mandelbrot_visualizer(int width, int height, const std::string& title)
    : width(width), height(height), title(title), window(nullptr) {
    initGLFW();
    initGLAD();
    initShaders();
    initData();
}

mandelbrot_visualizer::~mandelbrot_visualizer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}

void mandelbrot_visualizer::initGLFW() {
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
    glfwSwapInterval(1); // Enable vsync
}

void mandelbrot_visualizer::initGLAD() {
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        throw std::runtime_error("Failed to initialize OpenGL context");
    }
    glEnable(GL_MULTISAMPLE);
    glViewport(0, 0, width, height);
}

void mandelbrot_visualizer::initShaders() {
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
}

void mandelbrot_visualizer::initData() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    updateMandelbrotData();
}

void mandelbrot_visualizer::updateMandelbrotData() {
    vertices.clear();
    colors.clear();

    float aspect_ratio = (float)width / (float)height;
    int resolution = 3;  // Points per pixel (3x3 sampling)

    for (int y = 0; y < height; y += resolution) {
        for (int x = 0; x < width; x += resolution) {
            // Normalize to [-1, 1]
            float ndc_x = (2.0f * x / width) - 1.0f;
            float ndc_y = 1.0f - (2.0f * y / height);

            // Convert NDC to Mandelbrot space
            double real = centerX + (ndc_x / aspect_ratio) * scale / 2.0;
            double imag = centerY + ndc_y * scale / 2.0;

            // Calculate Mandelbrot
            int iterations = mandelbrot(std::complex<double>(real, imag), maxIterations);

            // Color based on iterations
            float hue = (float)iterations / maxIterations;
            float r, g, b;

            if (iterations == maxIterations) {
                // Black for points in the set
                r = 0.0f;
                g = 0.0f;
                b = 0.0f;
            } else {
                // Color gradient based on escape time
                hue = (float)std::sqrt((float)iterations / maxIterations);
                r = std::sin(hue * 3.14159f) * 0.5f + 0.5f;
                g = std::sin(hue * 3.14159f + 2.094f) * 0.5f + 0.5f;
                b = std::sin(hue * 3.14159f + 4.189f) * 0.5f + 0.5f;
            }

            vertices.push_back(ndc_x);
            vertices.push_back(ndc_y);
            colors.push_back(r);
            colors.push_back(g);
            colors.push_back(b);
        }
    }

    // Combine vertices and colors
    std::vector<float> data;
    for (size_t i = 0; i < vertices.size() / 2; ++i) {
        data.push_back(vertices[i * 2]);
        data.push_back(vertices[i * 2 + 1]);
        data.push_back(colors[i * 3]);
        data.push_back(colors[i * 3 + 1]);
        data.push_back(colors[i * 3 + 2]);
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_DYNAMIC_DRAW);

    needsUpdate = false;
}

void mandelbrot_visualizer::run() {
    while (!glfwWindowShouldClose(window)) {
        processInput();

        if (needsUpdate) {
            updateMandelbrotData();
        }

        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void mandelbrot_visualizer::processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        maxIterations = std::min(maxIterations + 10, 2048);
        needsUpdate = true;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        maxIterations = std::max(maxIterations - 10, 32);
        needsUpdate = true;
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        centerX = -0.5;
        centerY = 0.0;
        scale = DEFAULT_SCALE;
        maxIterations = DEFAULT_MAX_ITERATIONS;
        needsUpdate = true;
    }
}

void mandelbrot_visualizer::render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, vertices.size() / 2);
}

// Static Callbacks
void mandelbrot_visualizer::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    auto* visualizer = static_cast<mandelbrot_visualizer*>(glfwGetWindowUserPointer(window));
    if (yoffset > 0)
        visualizer->scale /= ZOOM_FACTOR;
    else
        visualizer->scale *= ZOOM_FACTOR;
    visualizer->needsUpdate = true;
}

void mandelbrot_visualizer::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    auto* visualizer = static_cast<mandelbrot_visualizer*>(glfwGetWindowUserPointer(window));
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            visualizer->isDragging = true;
            glfwGetCursorPos(window, &visualizer->lastMouseX, &visualizer->lastMouseY);
        } else if (action == GLFW_RELEASE) {
            visualizer->isDragging = false;
        }
    }
}

void mandelbrot_visualizer::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    auto* visualizer = static_cast<mandelbrot_visualizer*>(glfwGetWindowUserPointer(window));
    if (visualizer->isDragging) {
        float dx = (float)(xpos - visualizer->lastMouseX) / visualizer->width;
        float dy = (float)(visualizer->lastMouseY - ypos) / visualizer->height;

        float aspect_ratio = (float)visualizer->width / visualizer->height;
        visualizer->centerX -= dx * visualizer->scale / aspect_ratio;
        visualizer->centerY += dy * visualizer->scale;

        visualizer->lastMouseX = xpos;
        visualizer->lastMouseY = ypos;
        visualizer->needsUpdate = true;
    }
}

void mandelbrot_visualizer::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    auto* visualizer = static_cast<mandelbrot_visualizer*>(glfwGetWindowUserPointer(window));
    visualizer->width = width;
    visualizer->height = height;
    glViewport(0, 0, width, height);
    visualizer->needsUpdate = true;
}

