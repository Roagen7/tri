#pragma once

#include <vector>
#include <memory>
#include <optional>

#include "../program/Program.h"
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <iostream>

class Mesh { 

public:    
    Mesh() = default;
    Mesh(const Mesh& other);
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(const Mesh& other);
    Mesh& operator=(Mesh&& other) noexcept;

    Mesh& setVertices(std::vector<glm::vec3> vertices);
    Mesh& setIndices(std::vector<glm::ivec3> indices);
    Mesh& setColors(std::vector<glm::vec3> colors);
    Mesh& setNormals(std::vector<glm::vec3> normals);
    Mesh& setTextureUnits(std::vector<glm::vec2> normals);
    static Mesh fromFile(const std::string& path);
    static Mesh fromStream(std::istream& stream);

    bool hasVertices();
    void draw() const;

    ~Mesh();
protected:
    virtual void isNotPredefinedMesh() {}

    void setup();
    std::optional<std::vector<glm::vec3>> vertices{};
    std::optional<std::vector<glm::ivec3>> indices{};
    std::optional<std::vector<glm::vec3>> colors{};
    std::optional<std::vector<glm::vec3>> normals{};
    std::optional<std::vector<glm::vec2>> texture{};

private:
    void cleanup();
  

    GLuint VAO{}, VBOverts{}, VBOcolors{}, VBOnormals{}, VBOtexture{}, EBO{};
};
