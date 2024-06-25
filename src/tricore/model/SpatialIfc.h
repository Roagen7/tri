#pragma once
#include <tricore/Camera.h>
#include <tricore/program/Program.h>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace tri::core {
    class SpatialIfc {
    public:
        virtual void draw(const Camera& camera) = 0;
        virtual void draw(Program& material) = 0;
        virtual glm::vec3 getWorldPosition() const = 0;
        virtual const Program& getMaterial() = 0;
        virtual bool castsShadow() = 0;
        virtual bool hasTransparency() = 0;

    protected:
        void setupSpaceMatrices(const Program& shader){
            shader.uniformMat4("rotation", glm::rotate(glm::identity<glm::mat4x4>(), (float)rotation.x, {1, 0, 0})
            * glm::rotate(glm::identity<glm::mat4x4>(), (float)rotation.y, {0, 1, 0})
            * glm::rotate(glm::identity<glm::mat4x4>(), (float)rotation.z, {0, 0, 1}));
            shader.uniformMat4("transform", glm::translate(glm::identity<glm::mat4x4>(), translation) * glm::scale(glm::identity<glm::mat4x4>(), scale));
        }


        glm::vec3 rotation{};
        glm::vec3 translation{0, 0, 0};
        glm::vec3 scale{1, 1, 1};
    };
}

