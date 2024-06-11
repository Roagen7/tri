#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "linmath.h"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <tri/Renderer.h>
#include <tri/program/Program.h>
#include <tri/program/programs/DefaultProgram.h>
#include <tri/buffers/Buffer.h>
#include <tri/buffers/Array.h>
#include <util/files.h>
#include <iostream>
#include <tri/Mesh.h>

struct sample
{
    float r, g, b;
};

std::vector<glm::vec3> vertices = {
    {-0.5f, 0, 0},
    {0, 0, 0.5f}, 
    {0, 0.5f, 0},
    {0.5f, 0, 0}
};

std::vector<glm::ivec3> indices = {
    {0, 1, 2},
    {1, 2, 3}
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
    Mesh mesh;
    mesh.setVertices(vertices).setColors(colors).setIndices(indices);
    
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glm::mat4x4 m, p, mvp;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        m = glm::identity<glm::mat4x4>();
        mvp = glm::rotate(m, (float) glfwGetTime(), {0, 0, 1.0});

        prg.use();
        prg.uniformMat4("MVP", mvp);
        mesh.draw();


   
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}