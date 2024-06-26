#include "Camera.h"
#include "config.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>


using namespace tri::core;

glm::mat4 Camera::view() const{
    return glm::perspective(glm::radians(fov), w/h, config::CAMERA_NEAR_PLANE, config::CAMERA_FAR_PLANE) * glm::lookAt(pos, pos + dir, UP);
}

glm::vec3 Camera::getDir() const {
    return dir;
}

glm::vec3 Camera::getPos(){
    return pos;
}

float Camera::getAspectRatio(){
    return w / h;
}


float Camera::getFov(){
    return fov;
}

std::pair<float, float> Camera::getScreenDimensions() const {
    return {w, h};
}

void Camera::poll(GLFWwindow *window) {
    int iWidth, iHeight;
    glfwGetWindowSize(window, &iWidth, &iHeight);
    w = iWidth; h = iHeight;

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        pos += dir * speed;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        pos += -dir * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        pos += speed * -glm::normalize(glm::cross(dir, UP));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        pos += speed * glm::normalize(glm::cross(dir, UP));
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        pos += speed * UP;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        pos += speed * -UP;
    }


    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        if(firstClick){
            glfwSetCursorPos(window, w/2, h/2);
            firstClick = false;
        }
        double mouseX;
        double mouseY;
        // Fetches the coordinates of the cursor
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotX = sens * (float)(mouseY - (h / 2)) / h;
        float rotY = sens * (float)(mouseX - (w / 2)) / w;

        glm::vec3 newOrientation = glm::rotate(dir, glm::radians(-rotX), glm::normalize(glm::cross(dir, UP)));

        if (abs(glm::angle(newOrientation, UP) - glm::radians(90.0f)) <= glm::radians(85.0f)){
            dir = newOrientation;
        }
        dir = glm::rotate(dir, glm::radians(-rotY), UP);
        glfwSetCursorPos(window,(w/2), h/2);

    } else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE){

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}