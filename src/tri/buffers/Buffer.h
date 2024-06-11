#pragma once

#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

template<typename T, GLint ENUM>
class Buffer {
public:
    Buffer(const std::vector<T>& arr){
        glGenBuffers(1,&ptr);
        glBindBuffer(ENUM, ptr);
        glBufferData(ENUM,arr.size() * sizeof(T), arr.data(), GL_STATIC_DRAW);
    }

    void bind(){
        glBindBuffer(ENUM, ptr);
    }

    void unbind(){
        glBindBuffer(ENUM, 0);
    }

    ~Buffer(){
        glDeleteBuffers(1, &ptr);
    }

private:
    GLuint ptr;
};

using EBO = Buffer<GLint, GL_ELEMENT_ARRAY_BUFFER>;
