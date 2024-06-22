#include "Renderer.h"

#include <fmt/format.h>

#include <tricore/program/materials/SkyboxMaterial.h>
#include <tricore/model/meshes/Plane.h>
#include <algorithm>
#include <limits>
#include <boost/range/adaptor/reversed.hpp>
  
using namespace tri::core;
using namespace tri::core::materials;
using namespace tri::config;

void Renderer::render(){
    int width, height;
    glfwGetFramebufferSize(&window, &width, &height);
    
    setupFBs(width, height);
    windowWidth = width;
    windowHeight = height;

    glViewport(0, 0, 1024, 1024);
    populateShadowmaps();

    glViewport(0, 0, width, height);

    renderToFrame(bloomUtils.bloomFrame0); /* TODO: this should be changed to more meaningful name */

    addBloom();
    postprocess();

    glfwSwapBuffers(&window);
    glfwPollEvents();
}

void Renderer::setupFBs(int width, int height){
    /*
    TODO: 
    execute the same logic as this function, but using specialized frames
    */
    if(width != windowWidth || height != windowHeight){
        directionalMaps.setup(width, height, directionalLights.size());
        omniDirectionalMaps.setup(width, height, pointLights.size());

        postprocessFrame.setup(width, height);

        bloomUtils.bloomFrame0.setup(width, height);
        bloomUtils.bloomFrame1.setup(width, height);

        postprocessOp->setup(postprocessFrame); 
        bloomUtils.bloom0.setup(bloomUtils.bloomFrame0);
        bloomUtils.bloom1.setup(bloomUtils.bloomFrame1);
    }
    
    unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };

    bloomUtils.bloomFrame0.bind();
    glDrawBuffers(2, attachments);

    bloomUtils.bloomFrame1.bind();
    glDrawBuffers(2, attachments);

    bloomUtils.bloomFrame1.unbind();
}


void Renderer::postprocess(){
    copyToFrame(nullptr, *postprocessOp);
}

void Renderer::addBloom(){
    for(auto i = 0u; i < bloomUtils.bloomPasses/2; i++){
        copyToFrame(&bloomUtils.bloomFrame1, bloomUtils.bloom0);
        copyToFrame(&bloomUtils.bloomFrame0, bloomUtils.bloom1);
    }
    copyToFrame(&postprocessFrame, bloomUtils.bloom0);
}

// todo: change name and clarify the logic
void Renderer::copyToFrame(Frame* frame, postprocess::BasePostprocess& op){
    if(frame){
        frame->bind();
    }

    glDisable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
    framePlane.draw(camera, op);
    glEnable(GL_DEPTH_TEST);

    if(frame){
        frame->unbind();
    }
}


Renderer::~Renderer(){
}

Renderer& Renderer::wireframe(){
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    return *this;
}

Renderer& Renderer::culling(){
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);  
    glFrontFace(GL_CW);
    return *this;
}

void Renderer::renderToFrame(Frame& frame){
    frame.bind();
    glClearColor(0, 0, 0, 1.0f);
    glStencilMask(0xFF);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glDepthFunc(GL_LEQUAL);

    skybox.draw(camera);

    renderModels();
    renderModelsWithAlpha();
    frame.unbind();
}

void Renderer::populateShadowmaps(){
    directionalMaps.populate(models, directionalLights, camera);
    omniDirectionalMaps.populate(models, pointLights);
}

void Renderer::renderShadowView(Program& program){
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);
        glDepthFunc(GL_LESS);
        // TODO: transparency might not work
        for(const auto& model : this->models){
            if(!model->castsShadow()) continue;
            model->draw(program);
        }
}

Renderer::Renderer(GLFWwindow& window, Camera& camera): 
    window(window), 
    camera(camera), 
    postprocessFrame(1),
    postprocessOp(std::make_unique<postprocess::BasePostprocess>()) {

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_CLAMP);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
    
    framePlane.setMesh(meshes::Plane());

    skybox.setMesh(meshes::VertexCube());
    skybox.setScaleXYZ({SKYBOX_SCALE, SKYBOX_SCALE, SKYBOX_SCALE});
};


void Renderer::setupLights(const Program& material){
    material.uniformVec3("viewDir", camera.getDir());
    material.uniformVec3("viewPos", camera.getPos());

    if(ambientLight){
        material.uniformVec3("ambientColor", ambientLight->color);
        material.uniformFloat("ambientIntensity", ambientLight->intensity);
    }
    
    material.uniformInt("uNumPointLights", pointLights.size());
    for(auto i = 0u; i < pointLights.size(); i++){
        const auto& light = pointLights[i];
        auto prefix = fmt::format("uPointLights[{}]", i);

        material.uniformVec3(fmt::format("{}.position", prefix), light->pos);
        material.uniformVec3(fmt::format("{}.color", prefix), light->color);
        material.uniformFloat(fmt::format("{}.constant", prefix), light->attentuation.constant);
        material.uniformFloat(fmt::format("{}.linear", prefix), light->attentuation.linear);
        material.uniformFloat(fmt::format("{}.quadratic", prefix), light->attentuation.quadratic);
    }

    material.uniformInt("uNumDirLights", directionalLights.size());
    for(auto i = 0u; i < directionalLights.size(); i++){
        const auto& light = directionalLights[i];
        auto prefix = fmt::format("uDirectionalLights[{}]", i);

        material.uniformVec3(fmt::format("{}.color", prefix), light->color);
        material.uniformVec3(fmt::format("{}.direction", prefix), light->direction);
        material.uniformFloat(fmt::format("{}.intensity", prefix), light->intensity);
    }
}

void Renderer::setupShadows(const Program& material){
    directionalMaps.attach(material, directionalLights, camera);
    omniDirectionalMaps.attach(material, pointLights);
}

void Renderer::renderModels(){
    glDepthFunc(GL_LESS); 

    for(const auto& model : this->models){
        if(model->hasTransparency()){
            continue;
        }
        renderModel(model.get());
    }
}

void Renderer::renderModelsWithAlpha(){
    glDepthFunc(GL_LESS); 

    auto pos = camera.getPos();
    std::map<float, Model*> sorted;

    for(const auto& model : this->models){
        float distance = glm::length(pos - model->getWorldPosition());
        if(!model->hasTransparency()){
            continue;
        } 
        sorted[distance] = model.get();
    }

    for ( const auto& [_, model] : boost::adaptors::reverse(sorted)){
        renderModel(model);
    }

}

void Renderer::renderModel(Model* model){
    const auto& material = model->getMaterial();
    setupLights(material);
    setupShadows(material);
    model->draw(camera);
}

Renderer& Renderer::setSkybox(glm::vec3 color){
    skybox.setMaterial<SkyboxMaterial>(color);
    return *this;
}

Renderer& Renderer::setSkybox(Cubemap&& cubemap){
    skybox.setMaterial<SkyboxMaterial>(std::move(cubemap));
    return *this;
}

Renderer& Renderer::add(std::shared_ptr<Model> model){
    models.push_back(model);
    return *this;
}

Renderer& Renderer::addLightSource(std::shared_ptr<PointLight> light){
    if(pointLights.size() == MAX_DIR_LIGHTS) return *this;
    pointLights.push_back(light);
    return *this;
}

Renderer& Renderer::addLightSource(std::shared_ptr<DirectionalLight> light){
    if(directionalLights.size() == MAX_DIR_LIGHTS) return *this;
    directionalLights.push_back(light);
    return *this;
}


Renderer& Renderer::setAmbientLight(std::shared_ptr<AmbientLight> light){
    ambientLight = light;
    return *this;
}