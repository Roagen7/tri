#pragma once
#include <string>
#include <functional>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>

class Program {

public:
    Program(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

    void use() const;
    

    const Program& uniform(const std::string& name, 
        std::function<void(GLint64)> fun
    ) const;

    const Program& uniformMat4(const std::string& name, const glm::mat4x4& mat) const;

    ~Program(){
        glDeleteProgram(program);
    }

    GLuint program;

private:
    std::string vsSource, fsSource;
    GLuint vertexShader, fragmentShader;

};