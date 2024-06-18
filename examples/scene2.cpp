/*
    This scene presents the following features:
    > basic engine features
    > specular maps, parallax maps, normal maps
    > transparency
    > light sources
    > outlines
    > skybox
*/

#include <glad/glad.h>
#include "glfwinclude.h"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <tricore/Renderer.h>
#include <tricore/program/Program.h>
#include <tricore/program/materials/SolidMaterial.h>
#include <tricore/program/materials/LightMaterial.h>
#include <tricore/program/materials/SkyboxMaterial.h>
#include <tricore/program/materials/DebugMaterial.h>
#include <tricore/model/meshes/Cube.h>
#include <tricore/model/meshes/Plane.h>
#include <tricore/model/meshes/Sphere.h>

#include <tricore/model/meshes/VertexCube.h>
#include <triutil/files.h>
#include <iostream>
#include <tricore/model/Mesh.h>
#include <tricore/Camera.h>
#include <tricore/model/Model.h>
#include <triutil/window_init.h>
#include <tricore/texture/Texture.h>
#include <tricore/program/materials/TextureMaterial.h>
#include <tricore/texture/Cubemap.h>

using namespace tri::core;
using namespace tri::core::materials;
using namespace tri::core::meshes;
using namespace tri::util;

int main(void){
    static constexpr auto width = 640;
    static constexpr auto height = 480;

    Window window("example", width, height);
            
    Camera camera(width, height, {0, 0, 3.0}, {0, 0, -1.0f});
    auto model = std::make_shared<Model>();
     
    model->setMesh(Sphere())
    .setMaterial(TextureMaterialBuilder()
        .setShininess(32.0)
        .setTexture(std::move(Texture("examples/data/textures/container2.png")))
        .setSpecularMap(std::move(Texture("examples/data/textures/container2_specular.png")))
        .build()
    );

    auto amb = light::make_ambient({
        .intensity = 0.1,
        .color = {1.f, 1.f, 1.f}
    });
    Renderer renderer(*window.get(), camera);
    renderer
        .setSkybox(Cubemap({
            .right = "examples/data/skybox/right.jpg",
            .left = "examples/data/skybox/left.jpg",
            .top = "examples/data/skybox/top.jpg",
            .bottom = "examples/data/skybox/bottom.jpg",
            .front = "examples/data/skybox/front.jpg",
            .back = "examples/data/skybox/back.jpg"
        }))
        .add(model)
        .add([](){
            auto lightModel = std::make_shared<Model>();
            lightModel->setMesh(Cube()).setMaterial<LightMaterial>(glm::vec3{1.0, 1.0, 1.0});
            lightModel->setTranslation({0, 0.0, -4.0});
            lightModel->setScaleXYZ({0.3, 0.3, 0.3});
            return lightModel;
        }())
        .addLightSource(light::make_point({
            .pos = {0, 0, -4.0},
            .color = {1, 1, 1},
            .attentuation = {
                .constant = 1.0,
                .linear = 0.1,
                .quadratic = 0.0
            }
        }))
        .setAmbientLight(light::make_ambient({
            .intensity = 0.1,
            .color = {1.f, 1.f, 1.f}
        }));

    static constexpr auto R = 3.0;

    while (!glfwWindowShouldClose(window.get()))
    {
        renderer.render();
        auto theta = glfwGetTime();
        model->setRotationXYZ({theta, 0, theta});
        model->setTranslation({R * sin(theta), 2 * R * cos(theta), -5.0});
        
        camera.poll(window.get());
    }
}