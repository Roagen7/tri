#include "Model.h"

#include <glm/gtc/matrix_transform.hpp>
#include "../program/Program.h"

using namespace tri::core;
using namespace tri::core::materials;

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

glm::vec3 Model::getWorldPosition() const{
    return this->translation;
}


Model& Model::setScaleXYZ(glm::vec3 scale){
    this->scale = scale;
    return *this;
}

void Model::borderPrehook(){
    if(border.material){
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
    } else {
        glStencilMask(0x00);
    }
}


void Model::draw(const Camera& camera){     
    borderPrehook();
    draw(camera, *material);
    drawBorder(camera);
}

void Model::drawBorder(const Camera& camera){
    if(!border.material) return;
    auto currentScale = this->scale;
    auto currentTranslation = this->translation;

    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);

    this->scale = this->scale * (1 + border.thickness);

    draw(camera, *border.material);
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    
    this->scale = currentScale;
    glClearStencil(0);
    glClear(GL_STENCIL_BUFFER_BIT);

}
    
Model& Model::enableTransparency(){
    transparency=true;
    return *this;
}

bool Model::hasTransparency(){
    return transparency;
}


void Model::draw(const Camera& camera, Program& material){
    draw(camera.view(), material);
}

void Model::draw(glm::mat4 projection, Program& material){
    material.use();
    material.uniformInt("hasShadow", receiveShadow);
    material.uniformMat4("rotation", glm::rotate(glm::identity<glm::mat4x4>(), (float)rotation.x, {1, 0, 0})
    * glm::rotate(glm::identity<glm::mat4x4>(), (float)rotation.y, {0, 1, 0})
    * glm::rotate(glm::identity<glm::mat4x4>(), (float)rotation.z, {0, 0, 1}));
    material.uniformMat4("transform", glm::translate(glm::identity<glm::mat4x4>(), translation) * glm::scale(glm::identity<glm::mat4x4>(), scale));
    material.uniformMat4("projection", projection);
    mesh.draw();
}

bool Model::castsShadow(){
    return castShadow;
}

Model& Model::enableCastShadow(){
    castShadow = true;
    return *this;
}

Model& Model::enableReceiveShadow(){
    receiveShadow = true;
    return *this;
}

Model& Model::setBorder(glm::vec3 color, float thickness){
    // border.material = std::make_unique<LightMaterial>(color);
    // border.thickness = thickness;
    return *this;
}

Model& Model::removeBorder(){
    border.material.reset();
    return *this;
}
