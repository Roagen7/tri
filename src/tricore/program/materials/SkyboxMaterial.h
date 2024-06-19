#pragma once

#include <tricore/program/Program.h>
#include <tricore/texture/Cubemap.h>
#include "SolidMaterial.h"
#include <fmt/format.h>

#include "shader_path.h"

namespace {
    static constexpr auto SKYBOX = "skybox";
}


namespace tri::core::materials {
    class SkyboxMaterial : public Program {
    public:
        SkyboxMaterial(Cubemap&& cubemap): Program(
            fmt::format("{}/{}/vs.glsl", SHADER_PATH, SKYBOX), 
            fmt::format("{}/{}/fs.glsl", SHADER_PATH, SKYBOX)
        ), cubemap(std::move(cubemap)), solidColor{false} {
            glActiveTexture(GL_TEXTURE0);
            cubemap.bind();
            uniformInt("skybox", 0);
            uniformInt("solidColor", 0);
            uniformVec3("uColor", {0, 0, 0});
        }

        SkyboxMaterial(glm::vec3 color): Program(
            fmt::format("{}/{}/vs.glsl", SHADER_PATH, SKYBOX), 
            fmt::format("{}/{}/fs.glsl", SHADER_PATH, SKYBOX)
        ),
        color(color), solidColor{true}{
            uniformInt("solidColor", 1);
            uniformVec3("uColor", color);
        }

        void use() const override {
            Program::use();
            if(!solidColor){
                glActiveTexture(GL_TEXTURE0);

                cubemap.bind();
            }
        }
    private:
        Cubemap cubemap;
        glm::vec3 color;
        bool solidColor{false};
    };
}