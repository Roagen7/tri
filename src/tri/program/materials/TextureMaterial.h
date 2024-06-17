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
        heightMap.bind();
        SolidMaterial::use();
    }

private:
    TextureMaterial(float diffuse = 1.0, float specular = 1.0, float shininess = 1.0): SolidMaterial({1, 1, 1}, diffuse, specular, shininess){
        uniformInt("hasTexture", 0);
        uniformInt("hasSpecularMap", 0);
        uniformInt("hasNormalMap", 0);
        uniformInt("hasHeightMap", 0);
    }

    Texture texture;
    Texture specularMap;
    Texture normalMap;
    Texture heightMap;
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

    TextureMaterialBuilder& setHeightMap(Texture&& texture, float heightScale){
        textureMaterial->uniformInt("hasHeightMap", 1);
        textureMaterial->uniformFloat("height_scale", heightScale);
        textureMaterial->heightMap = std::move(texture);
        glActiveTexture(GL_TEXTURE3);
        textureMaterial->heightMap.bind();
        textureMaterial->uniformInt("heightMap", 3);
        return *this;
    }

    std::unique_ptr<TextureMaterial>&& build(){
        return std::move(textureMaterial);
    }
private:
    std::unique_ptr<TextureMaterial> textureMaterial;
};