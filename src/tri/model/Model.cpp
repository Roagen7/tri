#include "Model.h"

#include <glm/gtc/matrix_transform.hpp>
#include "../program/Program.h"

void Model::setRotationXYZ(glm::vec3 rotation){
    this->rotation = rotation;
}

void Model::setTranslation(glm::vec3 translation){
    this->translation = translation;
}

void Model::setMesh(const Mesh& mesh){
    this->mesh = mesh;
}

const Program& Model::getMaterial(){
    if(!material) assert(0);
    return *material;
}

void Model::setScaleXYZ(glm::vec3 scale){
    this->scale = scale;
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