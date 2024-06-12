#include <glad/glad.h>
#include "glfwinclude.h"
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
#include <util/window_init.h>


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

int main(void){

    static constexpr auto width = 640;
    static constexpr auto height = 480;

    Window window("example", width, height);
            
    Camera camera(width, height, {0, 0, 3.0}, {0, 0, -1.0f});
    Model model;
    Mesh mesh;
    //mesh.setVertices(vertices).setColors(colors).setIndices(indices);
    mesh.setVertices(vertices).setIndices(indices);
    model.add(mesh);

    Renderer renderer(*window.get(), camera);
    renderer.add(model);

    static constexpr auto R = 3.0;

    while (!glfwWindowShouldClose(window.get()))
    {
        renderer.render();
        auto theta = glfwGetTime();
        model.setRotationXYZ({theta, theta, 0});
        model.setTranslation({R * sin(theta), R * cos(theta), 0});
        camera.poll(window.get());
    }
}