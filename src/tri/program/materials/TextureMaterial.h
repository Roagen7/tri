#pragma once

#include <tri/program/Program.h>
#include <tri/texture/Texture.h>
#include "SolidMaterial.h"
#include <fmt/format.h>

#include "shader_path.h"




class TextureMaterial : public SolidMaterial {
    friend class TextureMaterialBuilder;
public:

    // TextureMaterial(Texture&& texture, float diffuse, float specular, float shininess): SolidMaterial({1, 1, 1}, diffuse, specular, shininess), texture(std::move(texture)){
    //     uniformInt("hasTexture", 1);
    //     uniformInt("hasSpecularMap", 0);

    //     glActiveTexture(GL_TEXTURE0);
    //     texture.bind();
    //     uniformInt("texture0", 0);
    // }

    // TextureMaterial(Texture&& texture, float diffuse, Texture&& specularMap, float shininess) :  SolidMaterial({1, 1, 1}, diffuse, 0.0, shininess), texture(std::move(texture)), specularMap(std::move(specularMap)){
    //     uniformInt("hasTexture", 1);
    //     uniformInt("hasSpecularMap", 1);

    //     glActiveTexture(GL_TEXTURE0);
    //     texture.bind();
    //     uniformInt("texture0", 0);
    //     glActiveTexture(GL_TEXTURE1);
    //     specularMap.bind();
    //     uniformInt("texture1", 1);
    // }

    void use() const override {
        glActiveTexture(GL_TEXTURE0);
        texture.bind();
        glActiveTexture(GL_TEXTURE1);
        specularMap.bind();
        SolidMaterial::use();
    }

private:
    TextureMaterial(float diffuse = 1.0, float specular = 1.0, float shininess = 1.0): SolidMaterial({1, 1, 1}, diffuse, specular, shininess){
        uniformInt("hasTexture", 0);
        uniformInt("hasSpecularMap", 0);
        uniformInt("hasParallaxMap", 0);
    }

    Texture texture;
    Texture specularMap;
};

class TextureMaterialBuilder{

public:
    TextureMaterialBuilder() : textureMaterial(new TextureMaterial()) {}

    TextureMaterialBuilder& setShininess(float shiny){
        textureMaterial->uniformFloat("uShininess", shiny);
        return *this;
    }

    TextureMaterialBuilder& setTexture(Texture&& texture){
        textureMaterial->uniformInt("hasTexture", 1);
        textureMaterial->texture = std::move(texture);
        glActiveTexture(GL_TEXTURE0);
        textureMaterial->texture.bind();
        textureMaterial->uniformInt("texture0", 0);

        return *this;
    }

    TextureMaterialBuilder& setSpecularMap(Texture&& texture){
        textureMaterial->uniformInt("hasSpecularMap", 1);
        textureMaterial->specularMap = std::move(texture);
        glActiveTexture(GL_TEXTURE1);
        textureMaterial->specularMap.bind();
        textureMaterial->uniformInt("texture1", 1);

        return *this;
    }

    std::unique_ptr<TextureMaterial>&& build(){
        return std::move(textureMaterial);
    }
private:
    std::unique_ptr<TextureMaterial> textureMaterial;
};