#include "Program.h"
#include <glad/glad.h>
#include <util/files.h>
#include <glm/gtc/type_ptr.hpp>


Program::Program(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) : 
    vertexShader(glCreateShader(GL_VERTEX_SHADER)),
    fragmentShader(glCreateShader(GL_FRAGMENT_SHADER)),
    program(glCreateProgram()){
        
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    vsSource = readShader(vertexShaderPath);
    fsSource = readShader(fragmentShaderPath);

    auto vsSourceCStr = vsSource.c_str();
    auto fsSourceCStr = fsSource.c_str();

    glShaderSource(vertexShader, 1, &vsSourceCStr, NULL);
    glShaderSource(fragmentShader, 1, &fsSourceCStr, NULL);
    
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
}

void Program::use(){
    glUseProgram(program);
}

Program& Program::uniform(const std::string& name, std::function<void(GLint64)> fun){
    auto loc = glGetUniformLocation(program, name.c_str());
    fun(loc);
    return *this;
}

Program& Program::uniformMat4(const std::string& name, const glm::mat4x4& mat){
    return uniform(name, [name, mat](GLint loc){
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
    });
}