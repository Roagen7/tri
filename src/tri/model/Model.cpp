#include "Model.h"

#include <glm/gtc/matrix_transform.hpp>
#include "../program/Program.h"

void Model::setRotationXYZ(glm::vec3 rotation){
    this->rotation = rotation;
}

void Model::setTranslation(glm::vec3 translation){
    this->translation = translation;
}

void Model::add(const Mesh& mesh){
    meshes.push_back(mesh);
}


void Model::draw(const Program& program, const Camera& camera){        
    auto model = glm::translate(glm::identity<glm::mat4x4>(), translation) 
    * glm::rotate(glm::identity<glm::mat4x4>(), (float)rotation.x, {1, 0, 0})
    * glm::rotate(glm::identity<glm::mat4x4>(), (float)rotation.y, {0, 1, 0})
    * glm::rotate(glm::identity<glm::mat4x4>(), (float)rotation.z, {0, 0, 1});
    
    program.use();
    program.uniformMat4("MVP", camera.view() * model);
    for (const auto& mesh : meshes){
        mesh.draw();
    }
}