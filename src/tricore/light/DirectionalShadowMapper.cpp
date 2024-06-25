#include "DirectionalShadowMapper.h"
#include <fmt/format.h>

using namespace tri::core::shadow;
using namespace tri::core;

static constexpr auto DEPTH = "depth/map2d";

class ShadowProgram : public Program {
public:
    ShadowProgram() : Program(
        fmt::format("{}/{}/vs.glsl", SHADER_PATH, DEPTH), 
        fmt::format("{}/{}/fs.glsl", SHADER_PATH, DEPTH),
        fmt::format("{}/{}/gs.glsl", SHADER_PATH, DEPTH)
        ){}
};

DirectionalShadowMapper::DirectionalShadowMapper(const std::vector<std::pair<float, float>>& cascadeLayers) : cascadeLayers(cascadeLayers) {
    program = std::make_unique<ShadowProgram>();
    assert(cascadeLayers.size() <= config::CSM_MAX_CASCADES);
    for(auto& fr : frame){
        fr.setCascadeLevels(cascadeLayers.size());
    }
}

void DirectionalShadowMapper::setup(int width, int height, unsigned int lightCount) {
    for(auto i = 0u; i < lightCount; i++){
        frame[i].setup(width, height);
    }
}

void DirectionalShadowMapper::populate(std::vector<std::shared_ptr<SpatialIfc>>& models, std::vector<std::shared_ptr<DirectionalLight>>& lights, Camera& camera){
    for(auto i = 0u; i < lights.size(); i++){
        frame[i].bind();
        for(auto j = 0; j < cascadeLayers.size(); j++){
            const auto& [near, far] = cascadeLayers[j];
            program->uniformMat4(fmt::format("lightSpaceMatrices[{}]", j), light::get_lightspace_matrix(*lights[i], camera, near, far));
        }
        cast(models);
        frame[i].unbind();
    }
}

void DirectionalShadowMapper::attach(const Program& material, std::vector<std::shared_ptr<DirectionalLight>>& lights, Camera& camera) {
    static constexpr auto directionalShadowMapBegin = 10;
    material.use();
    material.uniformInt("cascadeCount", cascadeLayers.size());
    
    if(lights.size() == 0) return;
    for(auto i = 0u; i < cascadeLayers.size(); i++){
        material.uniformFloat(fmt::format("cascadePlaneDistances[{}]", i), cascadeLayers[i].second);
    }

    for(auto i = 0u; i < config::MAX_DIR_LIGHTS; i++){
        glActiveTexture(GL_TEXTURE0 + directionalShadowMapBegin + i);
        glBindTexture(GL_TEXTURE_2D_ARRAY, frame[i].getDepthMap());
        material.uniformInt(fmt::format("shadowMap[{}]", i), directionalShadowMapBegin + i);
        if(i >= lights.size()) continue;
        for(auto j = 0u; j < cascadeLayers.size(); j++){
            const auto& [near, far] = cascadeLayers[j];
            material.uniformMat4(fmt::format("shadowSpaceMatrix[{}]", i * config::CSM_MAX_CASCADES + j), light::get_lightspace_matrix(*lights[i].get(), camera, near, far));
        }
    }
}
