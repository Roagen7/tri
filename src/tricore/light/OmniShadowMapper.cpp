#include "OmniShadowMapper.h"
#include <fmt/format.h>

using namespace tri::core::shadow;
using namespace tri::core;

static constexpr auto OMNI_DEPTH = "depth/omni";

class OmniShadowProgram : public Program {
public:
    OmniShadowProgram() : Program(
        fmt::format("{}/{}/vs.glsl", SHADER_PATH, OMNI_DEPTH), 
        fmt::format("{}/{}/fs.glsl", SHADER_PATH, OMNI_DEPTH),
        fmt::format("{}/{}/gs.glsl", SHADER_PATH, OMNI_DEPTH)
        )
        {}
};

OmniShadowMapper::OmniShadowMapper(){
    program = std::make_unique<OmniShadowProgram>();
}

void OmniShadowMapper::setup(int width, int height, unsigned int lightCount) {
    for(auto i = 0u; i < lightCount; i++){
        frame[i].setup(width, height);
    }
}

void OmniShadowMapper::populate(std::vector<std::shared_ptr<Model>>& models, std::vector<std::shared_ptr<PointLight>>& lights){
    for(auto i = 0u; i < lights.size(); i++){
        frame[i].bind();
        auto projectionMatrices = light::get_lightspace_matrices(*lights[i]);
        program->uniformMat4("shadowMatrices[0]", projectionMatrices[0]);
        program->uniformMat4("shadowMatrices[1]", projectionMatrices[1]);
        program->uniformMat4("shadowMatrices[2]", projectionMatrices[2]);
        program->uniformMat4("shadowMatrices[3]", projectionMatrices[3]);
        program->uniformMat4("shadowMatrices[4]", projectionMatrices[4]);
        program->uniformMat4("shadowMatrices[5]", projectionMatrices[5]);
        program->uniformVec3("lightPos", lights[i]->pos);
        program->uniformFloat("far_plane", config::POINT_LIGHT_SHADOW_PLANES.far);
        cast(models);
        frame[i].unbind();
    }
}

void OmniShadowMapper::attach(const Program& material, std::vector<std::shared_ptr<PointLight>>& lights) {
    /*  
        NOTE: 
        for samplerCube arrays opengl forces filling every cubemap
        for dynamic indexing to work
        source: https://stackoverflow.com/questions/55171423/array-of-samplercube
    */ 
    static constexpr auto pointShadowMapBegin = 20;
    material.uniformFloat("pointLightFarPlane", config::POINT_LIGHT_SHADOW_PLANES.far);
    for(auto i = 0u; i < tri::config::MAX_POINT_LIGHTS; i++){
        glActiveTexture(GL_TEXTURE0 + pointShadowMapBegin + i);
        glBindTexture(GL_TEXTURE_CUBE_MAP, frame[i].getDepthMap());
        material.uniformInt(fmt::format("shadowCube[{}]", i), pointShadowMapBegin + i);
    }
}
