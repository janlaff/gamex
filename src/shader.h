#pragma once

#include <string>

#include <GL/glew.h>

class Shader {
public:
    static Shader create(GLuint type, std::string filename);

    GLuint getId() const;

private:
    Shader(GLuint id);

    GLuint id;
};