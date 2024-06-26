#pragma once

#include <tricore/program/Program.h>
#include <tricore/texture/Texture.h>
#include <tricore/texture/TextureResourceManager.h>
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

            if(texture){
                glActiveTexture(GL_TEXTURE0);
                texture->bind();
            }
            
            if(specularMap){
                glActiveTexture(GL_TEXTURE1);
                specularMap->bind();
            }
          
            if(normalMap){
                glActiveTexture(GL_TEXTURE2);
                normalMap->bind();
            }

            if(heightMap){
                glActiveTexture(GL_TEXTURE3);
                heightMap->bind();
            }
        }

    public:
        TextureMaterial(float diffuse = 1.0, float specular = 1.0, float shininess = 1.0): SolidMaterial({1, 1, 1}, diffuse, specular, shininess){
            uniformInt("hasTexture", 0);
            uniformInt("hasSpecularMap", 0);
            uniformInt("hasNormalMap", 0);
            uniformInt("hasHeightMap", 0);
        }

        void setTexture(texid_t id){
            uniformInt("hasTexture", 1);
            texture = &TextureResourceManager::texture(id);
            glActiveTexture(GL_TEXTURE0);
            texture->bind();
            uniformInt("texture0", 0);
            texture->unbind();
        }

        void setSpecularMap(texid_t id){
            uniformInt("hasSpecularMap", 1);
            specularMap = &TextureResourceManager::texture(id);
            glActiveTexture(GL_TEXTURE1);
            specularMap->bind();
            uniformInt("specularMap", 1);
            specularMap->unbind();
        }


        void setNormalMap(texid_t id){
            uniformInt("hasNormalMap", 1);
            normalMap = &TextureResourceManager::texture(id);
            glActiveTexture(GL_TEXTURE2);
            normalMap->bind();
            uniformInt("normalMap", 2);
            normalMap->unbind();
        }

        void setHeightMap(texid_t id, float heightScale){
            uniformInt("hasHeightMap", 1);
            uniformFloat("height_scale", heightScale);
            heightMap = &TextureResourceManager::texture(id);
            glActiveTexture(GL_TEXTURE3);
            heightMap->bind();
            uniformInt("heightMap", 3);
            heightMap->unbind();
        }

        Texture* texture{};
        Texture* specularMap{};
        Texture* normalMap{};
        Texture* heightMap{};
    };

    class TextureMaterialBuilder{

    public:
        TextureMaterialBuilder() : textureMaterial(new TextureMaterial()) {
  
        }

        TextureMaterialBuilder& setShininess(float shiny){
            textureMaterial->uniformFloat("uShininess", shiny);
            return *this;
        }

        TextureMaterialBuilder& setTexture(texid_t texture){
            textureMaterial->setTexture(texture);
            return *this;
        }

        TextureMaterialBuilder& setSpecularMap(texid_t texture){
            textureMaterial->setSpecularMap(texture);
            return *this;
        }


        TextureMaterialBuilder& setNormalMap(texid_t texture){
            textureMaterial->setNormalMap(texture);
            return *this;
        }

        TextureMaterialBuilder& setHeightMap(texid_t texture, float heightScale){
            textureMaterial->setHeightMap(texture, heightScale);
            return *this;
        }

        std::unique_ptr<TextureMaterial>&& build(){
            return std::move(textureMaterial);
        }

    private:
        std::unique_ptr<TextureMaterial> textureMaterial;

    };
}