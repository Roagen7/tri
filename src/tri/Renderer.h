#pragma once

#include <GLFW/glfw3.h>

class Renderer {

public:
    Renderer(const GLFWwindow& window): window(window) {
        
    };

private:
    const GLFWwindow& window;

};