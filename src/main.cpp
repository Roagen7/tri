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
#include <tri/program/materials/SolidMaterial.h>
#include <tri/program/materials/LightMaterial.h>
#include <tri/program/materials/SkyboxMaterial.h>
#include <tri/model/meshes/Cube.h>
#include <tri/model/meshes/Plane.h>
#include <tri/model/meshes/VertexCube.h>
#include <util/files.h>
#include <iostream>
#include <tri/model/Mesh.h>
#include <tri/Camera.h>
#include <tri/model/Model.h>
#include <util/window_init.h>
#include <tri/texture/Texture.h>
#include <tri/program/materials/TextureMaterial.h>
#include <tri/texture/Cubemap.h>

/*
small TODO list:
> add cubemaps (skybox)
> add different light type (directional)
> add diffuse and specular map support
> add loading mesh from file
> add debug material
> add default material
> add sprites
> add entity tree
*/

int main(void){

    static constexpr auto width = 640;
    static constexpr auto height = 480;

    Window window("example", width, height);
            
    Camera camera(width, height, {0, 0, 3.0}, {0, 0, -1.0f});
    auto model = std::make_shared<Model>();
    auto model2 = std::make_shared<Model>();
    auto lightModel = std::make_shared<Model>();
    auto lightModel2 = std::make_shared<Model>();

    Cubemap cubemap({
        .right = "examples/skybox/right.jpg",
        .left = "examples/skybox/left.jpg",
        .top = "examples/skybox/top.jpg",
        .bottom = "examples/skybox/bottom.jpg",
        .front = "examples/skybox/front.jpg",
        .back = "examples/skybox/back.jpg"
    });

    model->setMesh(Cube());
    model2->setMesh(Plane());
    
    model2->setMaterial<TextureMaterial>(std::move(Texture("examples/textures/wall.jpg")), 1.0, 1.0, 1024.0);
    
    model->setMaterial<SolidMaterial>(glm::vec3{1.0, 0.0, 1.0}, 1.0, 1.0, 32.0);

    lightModel->setMesh(Cube());
    lightModel->setMaterial<LightMaterial>(glm::vec3{1.0, 1.0, 1.0});
    lightModel2->setMesh(Cube());
    lightModel2->setMaterial<LightMaterial>(glm::vec3{1.0, 0.0, 0.0});
    
    Renderer renderer(*window.get(), camera);
        renderer.setSkybox(std::move(cubemap));

    // renderer.setSkybox({0.2, 0.2, 0.2});
    renderer.add(model);
    renderer.add(lightModel);
    renderer.add(lightModel2);
    renderer.add(model2);

    renderer.addLightSource({
        .pos = {0, 0, -4.0},
        .color = {1, 1, 1},
        .attentuation = {
            .constant = 1.0,
            .linear = 0.0,
            .quadratic = 0.5
        }
    });

    renderer.addLightSource({
        .pos = {0, 7.0, -4.0},
        .color = {1, 0, 0},
        .attentuation = {
            .constant = 1.0,
            .linear = 0.0,
            .quadratic = 0.5
        }
    });

    renderer.setAmbientLight({
        .intensity = 0.1,
        .color = {1.f, 1.f, 1.f}
    });

    static constexpr auto R = 3.0;

    lightModel->setTranslation({0, 0.0, -4.0});
    lightModel->setScaleXYZ({0.3, 0.3, 0.3});

    lightModel2->setTranslation({0, 7.0, -4.0});
    lightModel2->setScaleXYZ({0.3, 0.3, 0.3});

    model2->setScaleXYZ({20, 20, 20});
    model2->setTranslation({-5.0, 10, -7.0});
    model2->setRotationXYZ({M_PI/2, 0, 0});

    while (!glfwWindowShouldClose(window.get()))
    {
        renderer.render();
        auto theta = glfwGetTime();
        model->setRotationXYZ({theta, 0, theta});
        model->setTranslation({R * sin(theta), 2 * R * cos(theta), -5.0});
        
        camera.poll(window.get());
    }
}