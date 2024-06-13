#pragma once
#include <string>
#include <functional>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Program {

public:
    Program(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath="");

    virtual void use() const;
    

    const Program& uniform(const std::string& name, 
        std::function<void(GLint64)> fun
    ) const;

    const Program& uniformMat4(const std::string& name, const glm::mat4x4& mat) const;
    const Program& uniformVec3(const std::string& name, const glm::vec3& vec) const;
    const Program& uniformFloat(const std::string& name, float value) const;
    const Program& uniformInt(const std::string& name, int value) const;

    ~Program(){
        glDeleteProgram(program);
        glDeleteShader(vertexShader); 
        glDeleteShader(fragmentShader);
        glDeleteShader(geometryShader);
    }

    GLuint program;

private:
    std::string vsSource, fsSource;
    GLuint vertexShader, fragmentShader, geometryShader;

};