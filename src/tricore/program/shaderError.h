#pragma once
#include <glad/glad.h>
#include <string>

namespace tri::core {
    void getShaderError(const std::string& prefix, GLuint shader);
    void getProgramError(GLuint program);
}