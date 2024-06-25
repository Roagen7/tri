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
#include "./frame/DepthFrame.h"
#include "./frame/ColorFrame.h"
#include "./frame/OmniDepthFrame.h"
#include "./model/meshes/Plane.h"
#include "./model/SpatialIfc.h"
#include "./frame/BasePostprocess.h"
#include "./frame/postprocesses/BloomPostprocess.h"
#include "./light/OmniShadowMapper.h"
#include "./light/DirectionalShadowMapper.h"
#include "config.h"

namespace tri::core {

class Renderer {
    public:
        Renderer(GLFWwindow& window, Camera& camera);
        void render();
        Renderer& add(std::shared_ptr<SpatialIfc> spatial);

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
        void populateShadowmaps();

        void renderSpatials();
        void renderSpatialsWithAlpha();
        void renderSpatial(SpatialIfc* spatial);
        void setupLights(const Program& material);
        void setupShadows(const Program& material);

        void postprocess();
        void addBloom();

        void setupFBs(int width, int height);

        GLFWwindow& window;
        Camera& camera;

        std::vector<std::shared_ptr<SpatialIfc>> spatials;

        Model skybox;
        glm::vec3 bgColor{};
        
        shadow::DirectionalShadowMapper directionalMaps;
        shadow::OmniShadowMapper omniDirectionalMaps;
        std::vector<std::shared_ptr<PointLight>> pointLights;
        std::vector<std::shared_ptr<DirectionalLight>> directionalLights;
        std::shared_ptr<AmbientLight> ambientLight;

        int windowWidth{}, windowHeight{};

        ColorFrame postprocessFrame;
        Model framePlane;

        std::unique_ptr<postprocess::BasePostprocess> postprocessOp{};

        struct {
            ColorFrame bloomFrame0 = ColorFrame(2);
            ColorFrame bloomFrame1 = ColorFrame(2);
            postprocess::VerticalBlurPostprocess bloom0;
            postprocess::HorizontalBlurPostprocess bloom1;
            unsigned int bloomPasses{10};
        } bloomUtils;

    };
}