#include "shaderError.h"

#include <iostream>

static constexpr auto LOG_MAXSIZE = 1024;

using namespace tri::core;

void  tri::core::getShaderError(const std::string& prefix, GLuint shader){
    GLint hasCompiled;
    char infoLog[LOG_MAXSIZE];
    glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
    glGetShaderiv(shader,GL_COMPILE_STATUS, &hasCompiled);
    if(hasCompiled){
        return;
    }
    std::cout << prefix << infoLog << std::endl;
    
    exit(EXIT_FAILURE);
}

void tri::core::getProgramError(GLuint program){
    GLint hasLinked;
    char infoLog[LOG_MAXSIZE];
    glGetProgramInfoLog(program, 1024, nullptr, infoLog);
    glGetProgramiv(program, GL_LINK_STATUS, &hasLinked);
    if(hasLinked){
        return;
    }
    std::cout << "Program:" << infoLog << std::endl;
    exit(EXIT_FAILURE);
}