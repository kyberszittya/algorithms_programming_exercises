#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include <iostream>
#include "fibonacci.h"

const int WIDTH = 800;
const int HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 uColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = uColor;\n"
    "}\n\0";

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Fibonacci Plotter (OpenGL 3.3)", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    printf("GL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    // Compile shaders
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

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    int colorLoc = glGetUniformLocation(shaderProgram, "uColor");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Generate data
    std::vector<float> vertices;
    
    // Spiral Parameters
    // We want to show roughly 12 Fibonacci steps (3 rotations)
    // n = theta * 2 / PI  => theta = n * PI / 2
    float max_n_index = 12.0f; 
    float max_theta = max_n_index * 3.14159265f / 2.0f;
    
    // Calculate max radius to normalize the view
    float max_radius = (float)fibonacci_real_binet(max_n_index);
    float aspect_ratio = (float)WIDTH / (float)HEIGHT;

    // Generate Axes (Crosshair)
    std::vector<float> gridVertices;
    // X Axis
    gridVertices.push_back(-0.95f); gridVertices.push_back(0.0f);
    gridVertices.push_back(0.95f);  gridVertices.push_back(0.0f);
    // Y Axis
    gridVertices.push_back(0.0f); gridVertices.push_back(-0.95f);
    gridVertices.push_back(0.0f); gridVertices.push_back(0.95f);

    // Generate Spiral
    // We start from a small value to avoid 0 singularity issues visually
    for (float theta = 0.0f; theta <= max_theta; theta += 0.05f) {
        // Map angle to Fibonacci index
        double n = theta * 2.0 / 3.14159265;
        
        // Get radius from Binet formula
        double r = fibonacci_real_binet(n);

        // Polar to Cartesian
        float x = (float)(r * std::cos(theta));
        float y = (float)(r * std::sin(theta));

        // Normalize to screen coordinates [-0.9, 0.9]
        // Correct X by aspect ratio so the spiral isn't squashed
        float ndc_x = (x / max_radius) * 0.9f / aspect_ratio;
        float ndc_y = (y / max_radius) * 0.9f;

        vertices.push_back(ndc_x);
        vertices.push_back(ndc_y);
    }

    unsigned int gridVAO, gridVBO;
    glGenVertexArrays(1, &gridVAO);
    glGenBuffers(1, &gridVBO);
    glBindVertexArray(gridVAO);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    glBufferData(GL_ARRAY_BUFFER, gridVertices.size() * sizeof(float), gridVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Draw Grid
        glUniform4f(colorLoc, 0.5f, 0.5f, 0.5f, 1.0f); // Grey
        glBindVertexArray(gridVAO);
        glDrawArrays(GL_LINES, 0, gridVertices.size() / 2);

        // Draw Plot
        glUniform4f(colorLoc, 1.0f, 0.5f, 0.2f, 1.0f); // Orange
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_STRIP, 0, vertices.size() / 2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &gridVAO);
    glDeleteBuffers(1, &gridVBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}