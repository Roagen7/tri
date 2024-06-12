#include "Program.h"
#include <glad/glad.h>
#include <util/files.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

static constexpr auto LOG_MAXSIZE = 1024;

void getShaderError(const std::string& prefix, GLuint shader){
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

void getProgramError(GLuint program){
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


Program::Program(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath) : 
    vertexShader(glCreateShader(GL_VERTEX_SHADER)),
    fragmentShader(glCreateShader(GL_FRAGMENT_SHADER)),
    geometryShader(glCreateShader(GL_GEOMETRY_SHADER)),
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

    getShaderError("Vertex:\n", vertexShader);
    getShaderError("Fragment:\n", fragmentShader);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    if(!geometryShaderPath.empty()){
        auto gsSource = readShader(geometryShaderPath);
        auto gsSourceCStr = gsSource.c_str();
        
        glShaderSource(geometryShader, 1, &gsSourceCStr, NULL);
        glCompileShader(geometryShader);
        getShaderError("Geometry:\n", geometryShader);
        glAttachShader(program, geometryShader);
    }

    glLinkProgram(program);
    getProgramError(program);
}

void Program::use() const{
    glUseProgram(program);
}

const Program& Program::uniform(const std::string& name, std::function<void(GLint64)> fun) const {
    auto loc = glGetUniformLocation(program, name.c_str());
    fun(loc);
    return *this;
}

const Program& Program::uniformMat4(const std::string& name, const glm::mat4x4& mat) const {
    return uniform(name, [name, mat](GLint loc){
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
    });
}

const Program& Program::uniformVec3(const std::string& name, const glm::vec3& vec) const {
    return uniform(name, [name, vec](GLint loc){
        glUniform3fv(loc, 1, glm::value_ptr(vec));
    });
}
