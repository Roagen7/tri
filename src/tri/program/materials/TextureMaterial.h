#pragma once

#include <tri/program/Program.h>
#include <tri/texture/Texture.h>
#include "SolidMaterial.h"
#include <fmt/format.h>

#include "shader_path.h"

class TextureMaterial : public SolidMaterial {
public:

    TextureMaterial(Texture&& texture, float diffuse, float specular, float shininess): SolidMaterial({1, 1, 1}, diffuse, specular, shininess), texture(std::move(texture)){
        uniformInt("hasTexture", 1);

        glActiveTexture(GL_TEXTURE0);
        texture.bind();
        uniformInt("texture0", 0);
    }

    // TextureMaterial(Texture&& texture, Texture&& diffuseMap, Texture&& specularMap) :  SolidMaterial({1, 1, 1}, 0, 0, 0), texture(std::move(texture)), diffuseMap(std::move(diffuseMap)), specularMap(std::move(specularMap)){
    //     // TODO: add specular and diffuse maps handling
    // }

    void use() const override {
        glActiveTexture(GL_TEXTURE0);
        texture.bind();
        SolidMaterial::use();
    }

private:
    Texture texture;
    Texture diffuseMap;
    Texture specularMap;

};