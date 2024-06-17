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

void Model::borderPrehook(){
    if(borderMaterial){
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
    if(!borderMaterial) return;
    auto currentScale = this->scale;
    auto currentTranslation = this->translation;

    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);

    float borderWidth = 0.2; // %
    this->scale = this->scale * (1 + borderWidth);

    draw(camera, *borderMaterial);
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    
    this->scale = currentScale;
    glClearStencil(0);
    glClear(GL_STENCIL_BUFFER_BIT);

}


void Model::draw(const Camera& camera, Program& material){
    material.use();
    material.uniformMat4("rotation", glm::rotate(glm::identity<glm::mat4x4>(), (float)rotation.x, {1, 0, 0})
    * glm::rotate(glm::identity<glm::mat4x4>(), (float)rotation.y, {0, 1, 0})
    * glm::rotate(glm::identity<glm::mat4x4>(), (float)rotation.z, {0, 0, 1}));
    material.uniformMat4("transform", glm::translate(glm::identity<glm::mat4x4>(), translation) * glm::scale(glm::identity<glm::mat4x4>(), scale));
    material.uniformMat4("projection", camera.view());
    mesh.draw();
}

Model& Model::setBorder(glm::vec3 color){
    borderMaterial = std::make_unique<LightMaterial>(color);
    return *this;
}

Model& Model::removeBorder(){
    borderMaterial.reset();
    return *this;
}
