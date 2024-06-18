#pragma once

#include <vector>
#include <memory>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "./model/Model.h"
#include "./light/LightSource.h"
#include "./model/meshes/VertexCube.h"
#include "./texture/Cubemap.h"

static constexpr auto MAX_POINT_LIGHTS = 10;
static constexpr auto MAX_DIR_LIGHTS = 3;
static constexpr auto SKYBOX_SCALE = 10000;

namespace tri::core {

class Renderer {
    public:
        Renderer(GLFWwindow& window, Camera& camera): window(window), camera(camera) {
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_DEPTH_CLAMP);
            glEnable(GL_STENCIL_TEST);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
            
            skybox.setMesh(meshes::VertexCube());
            skybox.setScaleXYZ({SKYBOX_SCALE, SKYBOX_SCALE, SKYBOX_SCALE});
        };
        void render();
        Renderer& add(std::shared_ptr<Model> model);

        Renderer& addLightSource(std::shared_ptr<PointLight> light);
        Renderer& addLightSource(std::shared_ptr<DirectionalLight> light);
        Renderer& setAmbientLight(std::shared_ptr<AmbientLight> light);
        
        // for now only solid color
        Renderer& setSkybox(glm::vec3 color);
        Renderer& setSkybox(Cubemap&& cubemap);

    private:
        void renderModels();
        void renderModelsWithAlpha();
        void renderModel(Model* model);
        void setupLights(const Program& material);

        GLFWwindow& window;
        Camera& camera;

        // TODO: change everything to shared ptrs i.e. models, pointLights, etc.
        std::vector<std::shared_ptr<Model>> models;

        Model skybox;
        glm::vec3 bgColor{};

        std::vector<std::shared_ptr<PointLight>> pointLights;
        std::vector<std::shared_ptr<DirectionalLight>> directionalLights;
        std::shared_ptr<AmbientLight> ambientLight;
    };
}