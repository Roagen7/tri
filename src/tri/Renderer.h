#pragma once

#include <vector>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "./model/Model.h"
#include "./program/programs/DefaultProgram.h"

class Renderer {

public:
    Renderer(GLFWwindow& window, Camera& camera): window(window), camera(camera) {};
    void render();
    void add(Model& model);

private:
    DefaultProgram program;
    GLFWwindow& window;
    Camera& camera;
    std::vector<Model*> models;

};