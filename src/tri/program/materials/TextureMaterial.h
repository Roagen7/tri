#pragma once

#include <tri/program/Program.h>
#include <tri/texture/Texture.h>
#include "SolidMaterial.h"
#include <fmt/format.h>

#include "shader_path.h"




class TextureMaterial : public SolidMaterial {
    friend class TextureMaterialBuilder;
public:
    void use() const override {
        glActiveTexture(GL_TEXTURE0);
        texture.bind();
        glActiveTexture(GL_TEXTURE1);
        specularMap.bind();
        glActiveTexture(GL_TEXTURE2);
        normalMap.bind();
        glActiveTexture(GL_TEXTURE3);
        parallaxMap.bind();
        SolidMaterial::use();
    }

private:
    TextureMaterial(float diffuse = 1.0, float specular = 1.0, float shininess = 1.0): SolidMaterial({1, 1, 1}, diffuse, specular, shininess){
        uniformInt("hasTexture", 0);
        uniformInt("hasSpecularMap", 0);
        uniformInt("hasNormalMap", 0);
        uniformInt("hasParallaxMap", 0);
    }

    Texture texture;
    Texture specularMap;
    Texture normalMap;
    Texture parallaxMap;
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
        textureMaterial->uniformInt("specularMap", 1);

        return *this;
    }


    TextureMaterialBuilder& setNormalMap(Texture&& texture){
        textureMaterial->uniformInt("hasNormalMap", 1);
        textureMaterial->normalMap = std::move(texture);
        glActiveTexture(GL_TEXTURE2);
        textureMaterial->normalMap.bind();
        textureMaterial->uniformInt("normalMap", 2);

        return *this;
    }

    std::unique_ptr<TextureMaterial>&& build(){
        return std::move(textureMaterial);
    }
private:
    std::unique_ptr<TextureMaterial> textureMaterial;
};