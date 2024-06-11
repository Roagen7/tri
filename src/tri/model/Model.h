#pragma once

#include "../Camera.h"

#include "Mesh.h"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Model {
public:
    Model() = default;

    void setRotation(glm::vec3 rotation);
    void setTranslation(glm::vec3 translation);

    void add(const Mesh& mesh);
    void draw(const Program& program, const Camera& camera);

private:
    glm::vec3 rotation;
    glm::vec3 translation;
    std::vector<Mesh> meshes;
};