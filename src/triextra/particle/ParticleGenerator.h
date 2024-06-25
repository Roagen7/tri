#include <tricore/model/SpatialIfc.h>
#include <tricore/Camera.h>
#include <tricore/program/Program.h>
#include <glm/vec3.hpp>

namespace tri::extra {
    class ParticleGenerator : public tri::core::SpatialIfc {
        public:
            void draw(const tri::core::Camera& camera) {}
            void draw(tri::core::Program& material) {}
            glm::vec3 getWorldPosition() const {}
            const tri::core::Program& getMaterial() {}
            bool castsShadow() { return false; }
            bool hasTransparency() { return true; }
    };
}