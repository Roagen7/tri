#pragma once
#include <tricore/model/SpatialIfc.h>
#include <tricore/Camera.h>
#include <tricore/texture/Texture.h>
#include <memory>
#include <tricore/program/Program.h>
#include <glm/vec3.hpp>

namespace tri::extra {
    struct Particle;

    class ParticleGenerator : public tri::core::SpatialIfc {
        public:
            ParticleGenerator(tri::core::Texture&& texture, unsigned int particleCount=500); 
            virtual void update(float dt) = 0;
            void draw(const tri::core::Camera& camera);
            void draw(tri::core::Program& material) {}
            glm::vec3 getWorldPosition() const;
            const tri::core::Program& getMaterial();
            bool castsShadow() { return false; }
            bool hasTransparency() { return true; }

            ~ParticleGenerator();

        protected:
            std::vector<Particle> particles;

        private:

            std::unique_ptr<tri::core::Program> shader;
            GLuint VAO, VBO;
    };

    struct Particle {
        glm::vec3 velocity{};
        glm::vec3 position{0, 1, 0};
        glm::vec3 color{1, 1, 1};
        float life{};
    };
}