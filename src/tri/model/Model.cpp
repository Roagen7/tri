#include "Model.h"

#include <glm/gtc/matrix_transform.hpp>
#include "../program/Program.h"

void Model::setRotation(glm::vec3 rotation){
    this->rotation = rotation;
}

void Model::setTranslation(glm::vec3 translation){
    this->translation = translation;
}

void Model::add(const Mesh& mesh){
    meshes.push_back(mesh);
}


void Model::draw(const Program& program, const Camera& camera){        
    auto model = glm::translate(glm::identity<glm::mat4x4>(), glm::vec3(0.0f, 0.0f, -glfwGetTime())) 
    * glm::rotate(glm::identity<glm::mat4x4>(), (float) glfwGetTime(), {1.0, 0.3, .5f});
    
    program.use();
    program.uniformMat4("MVP", camera.view() * model);
    for (const auto& mesh : meshes){
        mesh.draw();
    }
}