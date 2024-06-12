#pragma once

#include "../glfwinclude.h"

#include <string>

class Window{
public:
    Window(const std::string& title, int width, int height);
    GLFWwindow* get();
    ~Window();
private:
    GLFWwindow* window;
};