#pragma once

#include <vector>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "./model/Model.h"
#include "./light/LightSource.h"
#include "./model/meshes/VertexCube.h"
#include "./texture/Cubemap.h"

static constexpr auto MAX_POINT_LIGHTS = 10;
static constexpr auto SKYBOX_SCALE = 10000;


class Renderer {

public:
    Renderer(GLFWwindow& window, Camera& camera): window(window), camera(camera) {
        skybox.setMesh(VertexCube());
        skybox.setScaleXYZ({SKYBOX_SCALE, SKYBOX_SCALE, SKYBOX_SCALE});
    };
    void render();
    void add(Model& model);
    void add(PointLight ptLight);

    void addLightSource(PointLight light);
    void setAmbientLight(AmbientLight light);

    // for now only solid color
    void setSkybox(glm::vec3 color);
    void setSkybox(Cubemap&& cubemap);

    // TODO
    void setSkybox(/*cubemap*/);
private:

    void setupLights(const Program& material);

    GLFWwindow& window;
    Camera& camera;

    // TODO: change everything to shared ptrs i.e. models, pointLights, etc.
    std::vector<Model*> models;

    Model skybox;
    glm::vec3 bgColor{};

    std::vector<PointLight> pointLights;
    AmbientLight ambientLight;

};