#pragma once
#include <tricore/Camera.h>
#include <tricore/program/Program.h>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace tri::core {
    class SpatialIfc {
    public:
        virtual void draw(const Camera& camera) {};
        virtual void draw(Program& material) {};
        virtual const Program& getMaterial() = 0;
        virtual bool castsShadow() = 0;
        virtual bool hasTransparency() = 0;
        virtual bool isOnScreenPlane() const { return false; };


        SpatialIfc& setRotationXYZ(glm::vec3 rotation);
        SpatialIfc& setScaleXYZ(glm::vec3 scale);
        SpatialIfc& setTranslation(glm::vec3 translation);
        glm::vec3 getWorldPosition() const;

        virtual ~SpatialIfc() {}

    protected:
        void setupSpaceMatrices(const Program& shader);
       

        glm::vec3 rotation{};
        glm::vec3 translation{0, 0, 0};
        glm::vec3 scale{1, 1, 1};
    };
}

