#include "Renderer.h"
  
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
    material.uniformVec3("ambientColor", ambientLight.color);
    material.uniformFloat("ambientIntensity", ambientLight.intensity);
}


void Renderer::add(Model& model){
    models.push_back(&model);
}

void Renderer::addLightSource(PointLight light){
    pointLights.push_back(light);
}

void Renderer::setAmbientLight(AmbientLight light){
    ambientLight = light;
}