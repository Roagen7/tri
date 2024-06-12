#pragma once

#include "../Camera.h"


#include "Mesh.h"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <map>

class Model {
public:
    Model() = default;

    void setRotationXYZ(glm::vec3 rotation);
    void setScale(glm::vec3 scale);
    void setTranslation(glm::vec3 translation);

    void add(const Mesh& mesh);

    template<typename T, typename... A>
    void setMaterial(A&&... args){
        this->material = std::make_unique<T>(args...);
    }
    void draw(const Camera& camera);

private:
    // TODO: change to quaternion
    glm::vec3 rotation{};
    glm::vec3 translation{};
    glm::vec3 scale{};
    std::vector<Mesh> meshes;
    std::unique_ptr<Program> material{};

    std::map<size_t, size_t> textures;

    // TODO: add default texture

};