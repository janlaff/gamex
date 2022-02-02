#pragma once

#include <vector>
#include <GL/glew.h>

template<typename T>
class Buffer {
public:
    static Buffer create(
        GLenum type = GL_ARRAY_BUFFER,
        GLenum usage = GL_STATIC_DRAW
    );

    GLuint getId() const;
    GLenum getType() const;
    GLenum getUsage() const;

    void bind();
    void setData(const std::vector<T>& data);

private:
    Buffer(GLuint id, GLenum type, GLenum usage);

    GLuint id;
    GLenum type;
    GLenum usage;
};

#include "buffer.impl.h"