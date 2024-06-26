#include "SpatialIfc.h"

using namespace tri::core;

 void SpatialIfc::setupSpaceMatrices(const Program& shader){
    shader.uniformMat4("rotation", glm::rotate(glm::identity<glm::mat4x4>(), (float)rotation.x, {1, 0, 0})
    * glm::rotate(glm::identity<glm::mat4x4>(), (float)rotation.y, {0, 1, 0})
    * glm::rotate(glm::identity<glm::mat4x4>(), (float)rotation.z, {0, 0, 1}));
    shader.uniformMat4("transform", glm::translate(glm::identity<glm::mat4x4>(), translation) * glm::scale(glm::identity<glm::mat4x4>(), scale));
}

SpatialIfc& SpatialIfc::setRotationXYZ(glm::vec3 rotation){
    this->rotation = rotation;
    return *this;
}

SpatialIfc& SpatialIfc::setScaleXYZ(glm::vec3 scale){
    this->scale = scale;
    return *this;
}

SpatialIfc& SpatialIfc::setTranslation(glm::vec3 translation){
    this->translation = translation;
    return *this;
}

glm::vec3 SpatialIfc::getWorldPosition() const {
    return this->translation;
}