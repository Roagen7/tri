#include "Renderer.h"

#include <fmt/format.h>

#include <tricore/program/materials/SkyboxMaterial.h>
#include <algorithm>
#include <limits>
#include <boost/range/adaptor/reversed.hpp>
  
using namespace tri::core;
using namespace tri::core::materials;

void Renderer::render(){
    int width, height;
    glfwGetFramebufferSize(&window, &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(0, 0, 0, 1.0f);
    glStencilMask(0xFF);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glDepthFunc(GL_LEQUAL);
    skybox.draw(camera);

    glDepthFunc(GL_LESS); 
    
    // blending requirement
    renderModels();
    renderModelsWithAlpha();

    glfwSwapBuffers(&window);
    glfwPollEvents();
}

void Renderer::setupLights(const Program& material){
    material.uniformVec3("viewDir", camera.getDir());
    material.uniformVec3("ambientColor", ambientLight->color);
    material.uniformFloat("ambientIntensity", ambientLight->intensity);

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