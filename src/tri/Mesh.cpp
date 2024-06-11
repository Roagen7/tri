#include "Mesh.h"
#include <glad/glad.h>

Mesh::Mesh(){

}

Mesh& Mesh::setVertices(std::vector<glm::vec3> vertices){
    this->vertices = vertices;
    setup();
    return *this;
}
Mesh& Mesh::setIndices(std::vector<glm::ivec3> indices){
    this->indices = indices;
    setup();
    return *this;
}

void Mesh::draw(){
    glBindVertexArray(VAO);

    if(indices){
        glDrawElements(GL_TRIANGLES, indices->size() * 3, GL_UNSIGNED_INT, 0);
    } else if (vertices){
        glDrawArrays(GL_TRIANGLES, 0, vertices->size() * 3);
    }
    glBindVertexArray(0);        
}


Mesh& Mesh::setColors(std::vector<glm::vec3> colors){
    this->colors = colors;
    setup();
    return *this;
}

void Mesh::setup(){
    cleanup();
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    if(indices){
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(GLint) * 3, indices->data(), GL_STATIC_DRAW);
    }
    
    if(vertices){
        glGenBuffers(1, &VBOverts);
        glBindBuffer(GL_ARRAY_BUFFER, VBOverts);
        glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(GLfloat) * 3, vertices->data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
    }

    if(colors){
        glGenBuffers(1, &VBOcolors);
        glBindBuffer(GL_ARRAY_BUFFER, VBOcolors);
        glBufferData(GL_ARRAY_BUFFER, colors->size() * sizeof(GLfloat) * 3, colors->data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(1);
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::cleanup(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBOcolors);
    glDeleteBuffers(1, &VBOverts);
    glDeleteBuffers(1, &EBO);
}

Mesh::~Mesh(){

}