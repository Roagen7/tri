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
#include "./frame/Frame.h"
#include "./model/meshes/Plane.h"
#include "./frame/BasePostprocess.h"
#include "./frame/postprocesses/BloomPostprocess.h"

static constexpr auto MAX_POINT_LIGHTS = 10;
static constexpr auto MAX_DIR_LIGHTS = 3;
static constexpr auto SKYBOX_SCALE = 10000;

namespace tri::core {

class Renderer {
    public:
        Renderer(GLFWwindow& window, Camera& camera);
        void render();
        Renderer& add(std::shared_ptr<Model> model);

        Renderer& addLightSource(std::shared_ptr<PointLight> light);
        Renderer& addLightSource(std::shared_ptr<DirectionalLight> light);
        Renderer& setAmbientLight(std::shared_ptr<AmbientLight> light);
        
        // for now only solid color
        Renderer& setSkybox(glm::vec3 color);
        Renderer& setSkybox(Cubemap&& cubemap);

        Renderer& wireframe();
        Renderer& culling();

        template<typename T, typename... A>
        Renderer& setPostprocessing(A&&... args){
            postprocessOp = std::make_unique<T>(std::forward<A>(args)...);
            return *this;
        }


        ~Renderer();
    private:
        void renderToFrame(Frame& frame);
        void copyToFrame(Frame* frame, postprocess::BasePostprocess& op);

        void renderModels();
        void renderModelsWithAlpha();
        void renderModel(Model* model);
        void setupLights(const Program& material);

        void postprocess();
        void addBloom();

        void setupFBs(int width, int height);

        GLFWwindow& window;
        Camera& camera;

        // TODO: change everything to shared ptrs i.e. models, pointLights, etc.
        std::vector<std::shared_ptr<Model>> models;

        Model skybox;
        glm::vec3 bgColor{};

        std::vector<std::shared_ptr<PointLight>> pointLights;
        std::vector<std::shared_ptr<DirectionalLight>> directionalLights;
        std::shared_ptr<AmbientLight> ambientLight;

        int windowWidth{}, windowHeight{};

        Frame postprocessFrame;
        Model framePlane;

        std::unique_ptr<postprocess::BasePostprocess> postprocessOp{};

        struct {
            Frame bloomFrame0 = Frame(2);
            Frame bloomFrame1 = Frame(2);
            postprocess::VerticalBlurPostprocess bloom0;
            postprocess::HorizontalBlurPostprocess bloom1;
            unsigned int bloomPasses{10};
        } bloomUtils;
    };
}