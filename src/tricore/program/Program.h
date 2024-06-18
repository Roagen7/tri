#pragma once
#include <string>
#include <functional>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace tri::core {
    class Program {

    public:
        Program(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath="");
        Program(const Program& other);
        Program(Program&& other) noexcept;
        Program& operator=(const Program& other);
        Program& operator=(Program&& other) noexcept;

        virtual void use() const;
        

        const Program& uniform(const std::string& name, 
            std::function<void(GLint64)> fun
        ) const;


        const Program& uniformMat4(const std::string& name, const glm::mat4x4& mat) const;
        const Program& uniformVec3(const std::string& name, const glm::vec3& vec) const;
        const Program& uniformFloat(const std::string& name, float value) const;
        const Program& uniformInt(const std::string& name, int value) const;

        ~Program(){
            cleanup();
        }

        GLuint program;

    private:
        std::string vsSource{}, fsSource{}, gsSource{};
        GLuint vertexShader, fragmentShader, geometryShader;

        void readShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath="");
        void compileShaders();
        void cleanup();

    };
}