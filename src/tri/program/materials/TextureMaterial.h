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
        uniformInt("hasSpecularMap", 0);

        glActiveTexture(GL_TEXTURE0);
        texture.bind();
        uniformInt("texture0", 0);
    }

    TextureMaterial(Texture&& texture, float diffuse, Texture&& specularMap, float shininess) :  SolidMaterial({1, 1, 1}, diffuse, 0.0, shininess), texture(std::move(texture)), specularMap(std::move(specularMap)){
        uniformInt("hasTexture", 1);
        uniformInt("hasSpecularMap", 1);

        glActiveTexture(GL_TEXTURE0);
        texture.bind();
        uniformInt("texture0", 0);
        glActiveTexture(GL_TEXTURE1);
        specularMap.bind();
        uniformInt("texture1", 1);
    }

    void use() const override {
        glActiveTexture(GL_TEXTURE0);
        texture.bind();
        glActiveTexture(GL_TEXTURE1);
        specularMap.bind();
        SolidMaterial::use();
    }

private:
    Texture texture;
    Texture diffuseMap;
    Texture specularMap;

};