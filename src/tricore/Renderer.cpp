#include "Renderer.h"

#include <fmt/format.h>

#include <tricore/program/materials/SkyboxMaterial.h>
#include <tricore/model/meshes/Plane.h>
#include <algorithm>
#include <limits>
#include <boost/range/adaptor/reversed.hpp>
  
using namespace tri::core;
using namespace tri::core::materials;

void Renderer::render(){
    int width, height;
    glfwGetFramebufferSize(&window, &width, &height);
    
    setupFBs(width, height);
    glViewport(0, 0, width, height);

    windowWidth = width;
    windowHeight = height;

    glClearColor(0, 0, 0, 1.0f);
    glStencilMask(0xFF);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glDepthFunc(GL_LEQUAL);
    skybox.draw(camera);

    glDepthFunc(GL_LESS); 

    // /*
    // * TODO: shadow mapping
    // */
    // // renderShadows()

    renderModels();
    renderModelsWithAlpha();

    postprocess();

    glfwSwapBuffers(&window);
    glfwPollEvents();
}

void Renderer::setupFBs(int width, int height){
    if(width != windowWidth || height != windowHeight){
        renderFrame.setup(width, height);
        postprocessOp->setup(renderFrame);
    }

    renderFrame.bind();
}


void Renderer::postprocess(){
    renderFrame.unbind();
    glDisable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
    framePlane.draw(camera, *postprocessOp);
    glEnable(GL_DEPTH_TEST);
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



void Renderer::setupLights(const Program& material){
    material.uniformVec3("viewDir", camera.getDir());

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

void Renderer::renderModels(){
    for(const auto& model : this->models){
        if(model->hasTransparency()){
            continue;
        }
        renderModel(model.get());
    }
}
 

void Renderer::renderModelsWithAlpha(){
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