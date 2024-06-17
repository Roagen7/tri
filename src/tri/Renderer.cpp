#include "Renderer.h"

#include <fmt/format.h>

#include <tri/program/materials/SkyboxMaterial.h>
  
void Renderer::render(){
    int width, height;
    glfwGetFramebufferSize(&window, &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDepthFunc(GL_LESS); 
    for(auto model : this->models){
        const auto& material = model->getMaterial();
        
        
        setupLights(material);
        model->draw(camera);
    }
    glDepthFunc(GL_LEQUAL);
    skybox.draw(camera);

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