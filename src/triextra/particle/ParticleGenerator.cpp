#include "ParticleGenerator.h"
#include <fmt/format.h>
#include "shader_path.h"
#include <glm/gtc/matrix_transform.hpp>


using namespace tri::core;
using namespace tri::extra;

static constexpr auto PARTICLE = "particle";

class ParticleProgram : public Program {
public:
    ParticleProgram(Texture&& texture) : Program(
        fmt::format("{}/{}/vs.glsl", SHADER_PATH, PARTICLE), 
        fmt::format("{}/{}/fs.glsl", SHADER_PATH, PARTICLE)
    ), texture(std::move(texture)){
        glActiveTexture(GL_TEXTURE0);
        this->texture.bind();
        uniformInt("sprite", 0);
    }

    void use() const override {
        Program::use();
        glActiveTexture(GL_TEXTURE0);
        texture.bind();   
    }
private:
    Texture texture;
};

ParticleGenerator::ParticleGenerator(Texture&& texture, unsigned int particleCount) : shader(std::make_unique<ParticleProgram>(std::move(texture))){
    float particle_quad[] = {
        0.0f, 1.0f, 0.0, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0, 1.0f, 0.0f
    }; 
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glBindVertexArray(0);

    this->particles = std::vector<Particle>(particleCount);
}

ParticleGenerator::~ParticleGenerator(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void ParticleGenerator::draw(const Camera& camera){
    shader->use();
    // TODO: move it to SpatialIfc
    shader->uniformMat4("projection", camera.view());
    setupSpaceMatrices(*shader);
   
    shader->uniformFloat("scale", 0.5);
    shader->uniformVec3("cameraUp", tri::core::UP);
    shader->uniformVec3("cameraRight", glm::cross(camera.getDir(), tri::core::UP));
    
    for(const auto& particle : particles){
        if(particle.life < 0.f) continue;
        shader->uniformVec3("offset", particle.position);
        shader->uniformVec3("particleColor", particle.color);
        glBindVertexArray(this->VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
}

glm::vec3 ParticleGenerator::getWorldPosition() const {
    return translation;
}

const tri::core::Program& ParticleGenerator::getMaterial() {
    return *shader;
}
