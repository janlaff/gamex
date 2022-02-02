#include <iostream>
#include <unordered_map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "throw.h"
#include "buffer.h"
#include "program.h"

void initializeGLFW() {
    throwIf(
        !glfwInit(),
        std::runtime_error("Failed to initialize GLFW")
    );

    const std::unordered_map<int, int> windowHints {
        {GLFW_SAMPLES, 4},
        {GLFW_CONTEXT_VERSION_MAJOR, 4},
        {GLFW_CONTEXT_VERSION_MINOR, 4},
        {GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE},
    };

    for (auto [key, value] : windowHints)
        glfwWindowHint(key, value);
}

void initializeGLEW() {
    throwIf(
        glewInit() != GLEW_OK,
        std::runtime_error("Failed to initialize GLEW")
    );
}


int main(int argc, char* argv[]) {
    initializeGLFW();

    GLFWwindow* windowHandle = nullptr;
    windowHandle = glfwCreateWindow(1024, 768, "GameX", nullptr, nullptr);
    throwIfNull(
        windowHandle,
        std::runtime_error("Failed to open GLFW window")
    );

    glfwMakeContextCurrent(windowHandle);
    initializeGLEW();

    GLuint vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

    auto triangleBuffer = Buffer<float>::create();
    triangleBuffer.setData({
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    });

    auto triangleProgram = Program::create({
        Shader::create(GL_VERTEX_SHADER, "triangle.vert"),
        Shader::create(GL_FRAGMENT_SHADER, "triangle.frag")
    });
    triangleProgram.use();

    while (!glfwWindowShouldClose(windowHandle)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnableVertexAttribArray(0);
        triangleBuffer.bind();
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        glfwSwapBuffers(windowHandle);
        glfwPollEvents();
    }

    return 0;
}