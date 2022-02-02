#include <fstream>
#include <sstream>
#include <vector>

#include "shader.h"
#include "throw.h"

std::string readFileAsString(std::string filename) {
    std::ifstream ifs(filename);
    throwIf(!ifs.is_open(), std::runtime_error("Failed to open file " + filename));

    std::stringstream ss;
    ss << ifs.rdbuf();

    return ss.str();
}

void compileShader(GLuint shaderId, std::string sourceCode) {
    auto cPtr = sourceCode.c_str();
    glShaderSource(shaderId, 1, &cPtr, nullptr);
    glCompileShader(shaderId);
}

void checkShaderCompileResult(GLuint shaderId) {
    GLint result;
    GLint logLength;

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 0) {
        std::vector<char> errorMessage(logLength + 1);
        glGetShaderInfoLog(shaderId, logLength, nullptr, errorMessage.data());

        throw std::runtime_error({errorMessage.begin(), errorMessage.end()});
    }
}

Shader Shader::create(GLuint type, std::string filename) {
    GLuint shaderId = glCreateShader(type);

    compileShader(shaderId, readFileAsString(filename));
    checkShaderCompileResult(shaderId);

    return {shaderId};
}

Shader::Shader(GLuint id) : id(id) {}

GLuint Shader::getId() const {
    return id;
}