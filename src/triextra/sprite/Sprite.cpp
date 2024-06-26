#include "Sprite.h"    
#include "shader_path.h"
#include <fmt/format.h>

using namespace tri::extra;
using namespace tri::core;
        
static constexpr auto SPRITE = "sprite";

class SpriteProgram : public Program {
public:
    SpriteProgram(Texture&& texture) : Program(
        fmt::format("{}/{}/vs.glsl", SHADER_PATH, SPRITE), 
        fmt::format("{}/{}/fs.glsl", SHADER_PATH, SPRITE)
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


Sprite::Sprite(Texture&& texture) : shader(std::make_unique<SpriteProgram>(std::move(texture))){
  float quad[] = {
    //      vertices   |  textures
        -0.5f, 0.5f, 0.0, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.0, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0, 1.0f, 0.0f
    }; 
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glBindVertexArray(0);
}

void Sprite::draw(const Camera& camera){
    shader->use();
    setupSpaceMatrices(*shader);
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
 
const Program& Sprite::getMaterial(){
    return *shader;
}
            
Sprite::~Sprite() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
