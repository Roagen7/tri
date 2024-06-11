#pragma once
#include "Buffer.h"

class VAO {

public:
    VAO() {
        glGenVertexArrays(1, &ptr);
        bind();
    }

    template<typename R, GLint ENUM>
    VAO& link(Buffer<R, ENUM> buffer, GLuint numComponents, Buffer<GLint, GL_ELEMENT_ARRAY_BUFFER> ebo){
        bind();
        buffer.bind();
        ebo.bind();
        glVertexAttribPointer(index, numComponents, GL_FLOAT, GL_FALSE, numComponents * sizeof(GL_FLOAT), nullptr);
        glEnableVertexAttribArray(index++);        
        buffer.unbind();
        unbind();
        ebo.unbind();
        return *this;
    }

    void bind(){
        glBindVertexArray(ptr);
    }

    void unbind(){
        glBindVertexArray(0);
    }

    ~VAO(){
        glDeleteVertexArrays(1, &ptr);
    }

private:

    GLuint ptr;
    GLuint index = 0;
};
