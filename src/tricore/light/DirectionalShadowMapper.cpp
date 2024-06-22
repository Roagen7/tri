#include "DirectionalShadowMapper.h"
#include <fmt/format.h>

using namespace tri::core::shadow;
using namespace tri::core;

static constexpr auto DEPTH = "depth/map2d";

class ShadowProgram : public Program {
public:
    ShadowProgram() : Program(
        fmt::format("{}/{}/vs.glsl", SHADER_PATH, DEPTH), 
        fmt::format("{}/{}/fs.glsl", SHADER_PATH, DEPTH)){}
};

DirectionalShadowMapper::DirectionalShadowMapper(){
    program = std::make_unique<ShadowProgram>();
}

void DirectionalShadowMapper::setup(int width, int height, unsigned int lightCount) {
    for(auto i = 0u; i < lightCount; i++){
        frame[i].setup(width, height);
    }
}

void DirectionalShadowMapper::populate(std::vector<std::shared_ptr<Model>>& models, std::vector<std::shared_ptr<DirectionalLight>>& lights, Camera& camera){
    for(auto i = 0u; i < lights.size(); i++){
        frame[i].bind();
        program->uniformMat4("projection", light::get_lightspace_matrix(*lights[i], camera));
        cast(models);
        frame[i].unbind();
    }
}

void DirectionalShadowMapper::attach(const Program& material, std::vector<std::shared_ptr<DirectionalLight>>& lights, Camera& camera) {
    static constexpr auto directionalShadowMapBegin = 10;
    material.use();

    for(auto i = 0u; i < lights.size(); i++){
        glActiveTexture(GL_TEXTURE0 + directionalShadowMapBegin + i);
        glBindTexture(GL_TEXTURE_2D, frame[i].getDepthMap());
        material.uniformInt(fmt::format("shadowMap[{}]", i), directionalShadowMapBegin + i);
        material.uniformMat4(fmt::format("shadowSpaceMatrix[{}]", i), light::get_lightspace_matrix(*lights[i].get(), camera));
    }
}
