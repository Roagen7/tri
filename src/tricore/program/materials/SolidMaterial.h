#pragma once

#include <tricore/program/Program.h>
#include <fmt/format.h>

#include "shader_path.h"

namespace {
    static constexpr auto SOLID = "solid";
    static constexpr auto CALCULATE_NORMALS = "calculate_normals";
}

namespace tri::core::materials {
    class SolidMaterialShaderNormals : public Program {
    public:
        SolidMaterialShaderNormals():Program(
            fmt::format("{}/{}/vs.glsl", SHADER_PATH, CALCULATE_NORMALS), 
            fmt::format("{}/{}/fs.glsl", SHADER_PATH, CALCULATE_NORMALS),
            fmt::format("{}/{}/gs.glsl", SHADER_PATH, CALCULATE_NORMALS)
            ) {}
    };

    class SolidMaterial : public Program {
    public:
        SolidMaterial(glm::vec3 color, float diffuse=1.0, float specular=1.0, float shininess=1.0):Program(
            fmt::format("{}/{}/vs.glsl", SHADER_PATH, SOLID), 
            fmt::format("{}/{}/fs.glsl", SHADER_PATH, SOLID)
        ) {
            uniformVec3("uColor", color);
            uniformFloat("uDiffuse", diffuse);
            uniformFloat("uSpecular", specular);
            uniformFloat("uShininess", shininess);
            uniformInt("hasTexture", 0);
            uniformInt("hasSpecularMap", 0);
            uniformInt("hasDiffuseMap", 0);
        }
    };
}