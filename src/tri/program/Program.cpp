#include "Program.h"
#include <glad/glad.h>
#include <util/files.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <tri/program/shaderError.h>
#include <tri/program/ShaderLib.h>

Program::Program(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath) {
    readShaders(vertexShaderPath, fragmentShaderPath, geometryShaderPath);
    compileShaders();
}

void Program::use() const{
    glUseProgram(program);
}

const Program& Program::uniform(const std::string& name, std::function<void(GLint64)> fun) const {
    use();
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

const Program& Program::uniformFloat(const std::string& name, float value) const {
   return uniform(name, [name, value](GLint loc){
        glUniform1f(loc, value);
    });
}

const Program& Program::uniformInt(const std::string& name, int value) const {
    return uniform(name, [name, value](GLint loc){
        glUniform1i(loc, value);
    });
}

void Program::readShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath){
    vsSource = ShaderLib::include(readShader(vertexShaderPath));
    fsSource = ShaderLib::include(readShader(fragmentShaderPath));
    if(!geometryShaderPath.empty()){
        auto gsSource = ShaderLib::include(readShader(geometryShaderPath));
    }
}

void Program::compileShaders(){
    auto vsSourceCStr = vsSource.c_str();
    auto fsSourceCStr = fsSource.c_str();

    cleanup();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    program = glCreateProgram();
    
    glShaderSource(vertexShader, 1, &vsSourceCStr, NULL);
    glShaderSource(fragmentShader, 1, &fsSourceCStr, NULL);
    
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    getShaderError("Vertex:\n", vertexShader);
    getShaderError("Fragment:\n", fragmentShader);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    if(!gsSource.empty()){
        auto gsSourceCStr = gsSource.c_str();
        
        glShaderSource(geometryShader, 1, &gsSourceCStr, NULL);
        glCompileShader(geometryShader);
        getShaderError("Geometry:\n", geometryShader);
        glAttachShader(program, geometryShader);
    }

    ShaderLib::attach(program);

    glLinkProgram(program);
    getProgramError(program);
}

void Program::cleanup(){
    glDeleteProgram(program);
    glDeleteShader(vertexShader); 
    glDeleteShader(fragmentShader);
    glDeleteShader(geometryShader);
}

Program::Program(const Program& other)
    : vsSource(other.vsSource), fsSource(other.fsSource) {
    compileShaders();
}

Program::Program(Program&& other) noexcept
    : program(other.program), vsSource(std::move(other.vsSource)), fsSource(std::move(other.fsSource)),
      vertexShader(other.vertexShader), fragmentShader(other.fragmentShader), geometryShader(other.geometryShader) {
    other.program = 0;
    other.vertexShader = 0;
    other.fragmentShader = 0;
    other.geometryShader = 0;
}

Program& Program::operator=(const Program& other) {
    if (this == &other) {
        return *this;
    }
    vsSource = other.vsSource;
    fsSource = other.fsSource;
    compileShaders();

    return *this;
}

Program& Program::operator=(Program&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    program = other.program;
    vsSource = std::move(other.vsSource);
    fsSource = std::move(other.fsSource);
    vertexShader = other.vertexShader;
    fragmentShader = other.fragmentShader;
    geometryShader = other.geometryShader;

    other.program = 0;
    other.vertexShader = 0;
    other.fragmentShader = 0;
    other.geometryShader = 0;

    return *this;
}
