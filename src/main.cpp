#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <tri/Renderer.h>
#include <tri/program/Program.h>
#include <tri/program/programs/DefaultProgram.h>
#include <util/files.h>
#include <iostream>
#include <tri/model/Mesh.h>
#include <tri/Camera.h>
#include <tri/model/Model.h>


std::vector<glm::vec3> vertices = {
    glm::vec3(-0.5f, -0.5f, -0.5f), // 0
    glm::vec3( 0.5f, -0.5f, -0.5f), // 1
    glm::vec3( 0.5f,  0.5f, -0.5f), // 2
    glm::vec3(-0.5f,  0.5f, -0.5f), // 3
    glm::vec3(-0.5f, -0.5f,  0.5f), // 4
    glm::vec3( 0.5f, -0.5f,  0.5f), // 5
    glm::vec3( 0.5f,  0.5f,  0.5f), // 6
    glm::vec3(-0.5f,  0.5f,  0.5f)  // 7
};


std::vector<glm::ivec3> indices = {
    // Front face
    glm::ivec3(4, 5, 6),
    glm::ivec3(6, 7, 4),

    // Back face
    glm::ivec3(0, 1, 2),
    glm::ivec3(2, 3, 0),

    // Left face
    glm::ivec3(0, 3, 7),
    glm::ivec3(7, 4, 0),

    // Right face
    glm::ivec3(1, 5, 6),
    glm::ivec3(6, 2, 1),

    // Top face
    glm::ivec3(3, 2, 6),
    glm::ivec3(6, 7, 3),

    // Bottom face
    glm::ivec3(0, 1, 5),
    glm::ivec3(5, 4, 0)
};


const std::vector<glm::vec3> colors = {
    {1.f, 0.f, 0.f},
    {0.f, 1.f, 0.f},
    {0.f, 0.f, 1.f},
    {0.f, 0.f, 1.f}
};

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
int main(void){
    GLFWwindow* window;
    Renderer renderer(*window);
    

    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

    DefaultProgram prg;
    auto program = prg.program;

    int width, height;
        
    glfwGetFramebufferSize(window, &width, &height);
    Camera camera(width, height, {0, 0, 3.0}, {0, 0, -1.0f});
    Model model;
    Mesh mesh;
    //mesh.setVertices(vertices).setColors(colors).setIndices(indices);
    mesh.setVertices(vertices).setIndices(indices);

    model.add(mesh);

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glm::mat4x4 m, p, mvp;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        model.draw(prg, camera);
 
        glfwSwapBuffers(window);
        glfwPollEvents();
        camera.poll(window);
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}