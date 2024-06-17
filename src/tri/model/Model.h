#pragma once

#include "../Camera.h"


#include "Mesh.h"
#include <tri/program/materials/DefaultMaterial.h>
#include <tri/program/materials/LightMaterial.h>
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
    Model& setBorder(glm::vec3 color, float thickness);
    Model& removeBorder();

    const Program& getMaterial();

    template<typename T, typename... A>
    Model& setMaterial(A&&... args){
        this->material = std::make_unique<T>(std::forward<A>(args)...);
        return *this;
    }

    Model& setMaterial(std::unique_ptr<Program>&& material);

    void draw(const Camera& camera);

private:
    void drawBorder(const Camera& camera);
    void draw(const Camera& camera, Program& material);
    void borderPrehook();
    // TODO: change to quaternion
    glm::vec3 rotation{};
    glm::vec3 translation{};
    glm::vec3 scale{1, 1, 1};
    Mesh mesh;
    std::unique_ptr<Program> material{};

    struct {
        std::unique_ptr<LightMaterial> material{};
        float thickness;
    } border;
    
};