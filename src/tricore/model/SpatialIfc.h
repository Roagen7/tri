#pragma once
#include <tricore/Camera.h>
#include <tricore/program/Program.h>

namespace tri::core {
    class SpatialIfc {
    public:
        virtual void draw(const Camera& camera) = 0;
        virtual void draw(Program& material) = 0;
        virtual glm::vec3 getWorldPosition() const = 0;
        virtual const Program& getMaterial() = 0;
        virtual bool castsShadow() = 0;
        virtual bool hasTransparency() = 0;
    };
}

