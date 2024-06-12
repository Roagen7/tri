#pragma once

#include <vector>
#include <memory>
#include <optional>

#include "../program/Program.h"
#include <glad/glad.h>
#include <glm/vec3.hpp>

class Mesh {

public:    
    Mesh() = default;

    Mesh& setVertices(std::vector<glm::vec3> vertices);
    Mesh& setIndices(std::vector<glm::ivec3> indices);
    Mesh& setColors(std::vector<glm::vec3> colors);

    void draw() const;

    ~Mesh();
private:
    void setup();
    void cleanup();
    std::optional<std::vector<glm::vec3>> vertices{};
    std::optional<std::vector<glm::ivec3>> indices{};
    std::optional<std::vector<glm::vec3>> colors{};
    std::optional<std::vector<glm::vec3>> normals{};

    GLuint VAO, VBOverts, VBOcolors, EBO;
};