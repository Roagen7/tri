#pragma once

#include "../Camera.h"


#include "Mesh.h"
#include <tri/program/materials/DefaultMaterial.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <map>

class Model {
public:
    Model() {
        setMaterial<DefaultMaterial>();
    };

    Model& setRotationXYZ(glm::vec3 rotation);
    Model& setScaleXYZ(glm::vec3 scale);
    Model& setScale(glm::vec3 scale);
    Model& setTranslation(glm::vec3 translation);

    Model& setMesh(const Mesh& mesh);

    const Program& getMaterial();

    template<typename T, typename... A>
    void setMaterial(A&&... args){
        this->material = std::make_unique<T>(std::forward<A>(args)...);
    }

    Model& setMaterial(std::unique_ptr<Program>&& material);

    void draw(const Camera& camera);

private:
    // TODO: change to quaternion
    glm::vec3 rotation{};
    glm::vec3 translation{};
    glm::vec3 scale{1, 1, 1};
    Mesh mesh;
    std::unique_ptr<Program> material{};
};