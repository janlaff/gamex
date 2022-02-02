#pragma once

#include <vector>

#include <GL/glew.h>

#include "shader.h"

class Program {
public:
    static Program create(const std::vector<Shader>& shaders);

    void use();

private:
    Program(GLuint id);

    GLuint id;
};