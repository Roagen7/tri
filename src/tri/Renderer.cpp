#include "Renderer.h"
  
void Renderer::render(){
    int width, height;
    glfwGetFramebufferSize(&window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    for(auto model : this->models){
        model->draw(program, camera);
    }

    glfwSwapBuffers(&window);
    glfwPollEvents();
}

void Renderer::add(Model& model){
    models.push_back(&model);
}