#pragma once

#include <tricore/program/Program.h>
#include <tricore/texture/Texture.h>
#include "SolidMaterial.h"
#include <fmt/format.h>

#include "stb_image.h"

#include "shader_path.h"

namespace tri::core::materials {
    class TextureMaterial : public SolidMaterial {
        friend class TextureMaterialBuilder;
    public:
        void use() const override {
            SolidMaterial::use();

            glActiveTexture(GL_TEXTURE0);
            texture.bind();
            glActiveTexture(GL_TEXTURE1);
            specularMap.bind();
            glActiveTexture(GL_TEXTURE2);
            normalMap.bind();
            // glActiveTexture(GL_TEXTURE3);
            // heightMap.bind();
        }

    public:
        TextureMaterial(float diffuse = 1.0, float specular = 1.0, float shininess = 1.0): SolidMaterial({1, 1, 1}, diffuse, specular, shininess){
            uniformInt("hasTexture", 0);
            uniformInt("hasSpecularMap", 0);
            uniformInt("hasNormalMap", 0);
            uniformInt("hasHeightMap", 0);
        }

        void setTexture(Texture&& texture){
            uniformInt("hasTexture", 1);
            this->texture = std::move(texture);
            glActiveTexture(GL_TEXTURE0);
            this->texture.bind();
            uniformInt("texture0", 0);
            this->texture.unbind();
        }

        void setSpecularMap(Texture&& texture){
            uniformInt("hasSpecularMap", 1);
            specularMap = std::move(texture);
            glActiveTexture(GL_TEXTURE1);
            specularMap.bind();
            uniformInt("specularMap", 1);
            this->specularMap.unbind();
        }


        void setNormalMap(Texture&& texture){
            uniformInt("hasNormalMap", 1);
            normalMap = std::move(texture);
            glActiveTexture(GL_TEXTURE2);
            normalMap.bind();
            uniformInt("normalMap", 2);
            this->normalMap.unbind();
        }

        void setHeightMap(Texture&& texture, float heightScale){
            uniformInt("hasHeightMap", 1);
            uniformFloat("height_scale", heightScale);
            heightMap = std::move(texture);
            glActiveTexture(GL_TEXTURE3);
            heightMap.bind();
            uniformInt("heightMap", 3);
            this->heightMap.unbind();
        }

        Texture texture;
        Texture specularMap;
        Texture normalMap;
        Texture heightMap;
    };

    class TextureMaterialBuilder{

    public:
        TextureMaterialBuilder() : textureMaterial(new TextureMaterial()) {
  
        }

        TextureMaterialBuilder& setShininess(float shiny){
            textureMaterial->uniformFloat("uShininess", shiny);
            return *this;
        }

        TextureMaterialBuilder& setTexture(Texture&& texture){
            textureMaterial->setTexture(std::move(texture));
            return *this;
        }

        TextureMaterialBuilder& setSpecularMap(Texture&& texture){
            textureMaterial->setSpecularMap(std::move(texture));
            return *this;
        }


        TextureMaterialBuilder& setNormalMap(Texture&& texture){
            textureMaterial->setNormalMap(std::move(texture));
            return *this;
        }

        TextureMaterialBuilder& setHeightMap(Texture&& texture, float heightScale){
            textureMaterial->setHeightMap(std::move(texture), heightScale);
            return *this;
        }

        std::unique_ptr<TextureMaterial>&& build(){
            return std::move(textureMaterial);
        }

   
    private:
        // HACK: for some reason without this texture the framebuffer refuses to work
        Texture texture;
        std::unique_ptr<TextureMaterial> textureMaterial;

    };
}