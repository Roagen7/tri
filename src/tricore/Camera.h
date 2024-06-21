#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


namespace tri::core {
    static constexpr glm::vec3 UP = {0.0f,1.0f,0.0f};

    class Camera {
    public:
        Camera(int w, int h, glm::vec3 pos, glm::vec3 dir): w(w), h(h), pos(pos), dir(dir), sens(100.f), speed(.5f), fov(90.0) {}
        void poll(GLFWwindow* window);
        glm::vec3 getDir();
        glm::vec3 getPos();
        float getAspectRatio();
        float getFov();
        glm::mat4 view() const;

    private:
        glm::vec3 pos, dir;
        float w, h, fov, speed, sens;
        bool firstClick = true;

    };
}