#include "Model.h"

#include <glm/gtc/matrix_transform.hpp>
#include "../program/Program.h"

Model& Model::setRotationXYZ(glm::vec3 rotation){
    this->rotation = rotation;
    return *this;
}

Model& Model::setTranslation(glm::vec3 translation){
    this->translation = translation;
    return *this;
}

Model& Model::setMesh(const Mesh& mesh){
    this->mesh = mesh;
    return *this;
}

Model& Model::setMaterial(std::unique_ptr<Program>&& material){
    this->material = std::move(material);
    return *this;
}


const Program& Model::getMaterial(){
    if(!material) assert(0);
    return *material;
}

Model& Model::setScaleXYZ(glm::vec3 scale){
    this->scale = scale;
    return *this;
}

void Model::draw(const Camera& camera){      
    material->use();
    material->uniformMat4("rotation", glm::rotate(glm::identity<glm::mat4x4>(), (float)rotation.x, {1, 0, 0})
    * glm::rotate(glm::identity<glm::mat4x4>(), (float)rotation.y, {0, 1, 0})
    * glm::rotate(glm::identity<glm::mat4x4>(), (float)rotation.z, {0, 0, 1}));
    material->uniformMat4("transform", glm::translate(glm::identity<glm::mat4x4>(), translation) * glm::scale(glm::identity<glm::mat4x4>(), scale));
    material->uniformMat4("projection", camera.view());
    mesh.draw();
}