#include "program.h"
#include "throw.h"

void checkProgramLinkResult(GLuint programId) {
    GLint result;
    GLint logLength;

    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 0) {
        std::vector<char> errorMessage(logLength + 1);
        glGetProgramInfoLog(programId, logLength, nullptr, errorMessage.data());

        throw std::runtime_error({errorMessage.begin(), errorMessage.end()});
    }
}

Program Program::create(const std::vector<Shader>& shaders) {
    GLuint programId = glCreateProgram();

    for (auto shader : shaders)
        glAttachShader(programId, shader.getId());
    
    glLinkProgram(programId);
    checkProgramLinkResult(programId);

    return {programId};
}

Program::Program(GLuint id) : id(id) {}

void Program::use() {
    glUseProgram(id);
}