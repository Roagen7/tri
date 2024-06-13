#include "Renderer.h"

#include <fmt/format.h>
  
void Renderer::render(){
    int width, height;
    glfwGetFramebufferSize(&window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(auto model : this->models){
        const auto& material = model->getMaterial();
        
        
        setupLights(material);
        model->draw(camera);
    }

    glfwSwapBuffers(&window);
    glfwPollEvents();
}

void Renderer::setupLights(const Program& material){
    material.uniformVec3("viewDir", camera.getDir());
    material.uniformVec3("ambientColor", ambientLight.color);
    material.uniformFloat("ambientIntensity", ambientLight.intensity);

    material.uniformInt("uNumPointLights", pointLights.size());
    for(auto i = 0u; i < pointLights.size(); i++){
        const auto& light = pointLights[i];
        auto prefix = fmt::format("uPointLights[{}]", i);

        material.uniformVec3(fmt::format("{}.position", prefix), light.pos);
        material.uniformVec3(fmt::format("{}.color", prefix), light.color);
        material.uniformFloat(fmt::format("{}.constant", prefix), light.attentuation.constant);
        material.uniformFloat(fmt::format("{}.linear", prefix), light.attentuation.linear);
        material.uniformFloat(fmt::format("{}.quadratic", prefix), light.attentuation.quadratic);
    }
}


void Renderer::add(Model& model){
    models.push_back(&model);
}

void Renderer::addLightSource(PointLight light){
    if(pointLights.size() == MAX_POINT_LIGHTS) return;
    pointLights.push_back(light);
}

void Renderer::setAmbientLight(AmbientLight light){
    ambientLight = light;
}