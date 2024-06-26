#include "Model.h"

#include <glm/gtc/matrix_transform.hpp>
#include "../program/Program.h"

using namespace tri::core;
using namespace tri::core::materials;

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
    material.uniformMat4("projection", projection);
    draw(material);
}

void Model::draw(Program& material){
    material.use();
    material.uniformInt("hasShadow", receiveShadow);
    setupSpaceMatrices(material);
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
    border.material = std::make_unique<LightMaterial>(color);
    border.thickness = thickness;
    return *this;
}

Model& Model::removeBorder(){
    border.material.reset();
    return *this;
}
