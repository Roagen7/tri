#pragma once
#include <tricore/model/SpatialIfc.h>
#include <tricore/Camera.h>
#include <tricore/texture/Texture.h>
#include <memory>
#include <tricore/program/Program.h>
#include <glm/vec3.hpp>

namespace tri::extra {
    class Sprite : public tri::core::SpatialIfc {
        public:
            Sprite(tri::core::Texture&& texture); 
            void draw(const tri::core::Camera& camera);
            const tri::core::Program& getMaterial();
            bool castsShadow() override { return false; }
            bool hasTransparency() override { return true; }
            bool isOnScreenPlane() const override { return true; }
            
            ~Sprite() override;
        private:
            std::unique_ptr<tri::core::Program> shader;
            GLuint VAO, VBO;
    };
}