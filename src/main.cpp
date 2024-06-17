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
#include <tri/program/materials/DebugMaterial.h>
#include <tri/model/meshes/Cube.h>
#include <tri/model/meshes/Plane.h>
#include <tri/model/meshes/Sphere.h>

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
> add parallax mapping
> add transparency
> add cel shader material
> add CubemapMaterial
> add sprites
> add shadows
> add hdr
> add bloom
> add entity tree
*/

int main(void){

    static constexpr auto width = 640;
    static constexpr auto height = 480;

    Window window("example", width, height);
            
    Camera camera(width, height, {0, 0, 3.0}, {0, 0, -1.0f});
    auto model = std::make_shared<Model>();
    auto model2 = std::make_shared<Model>();
    auto model3 = std::make_shared<Model>();
    auto lightModel = std::make_shared<Model>();
    auto lightModel2 = std::make_shared<Model>();

    Cubemap cubemap({
        .right = "examples/skybox/space/right.png",
        .left = "examples/skybox/space/left.png",
        .top = "examples/skybox/space/top.png",
        .bottom = "examples/skybox/space/bottom.png",
        .front = "examples/skybox/space/front.png",
        .back = "examples/skybox/space/back.png"
    });

    //model->setMesh(Mesh::fromFile("examples/mesh/textured_with_normals.obj"));
    model2->setMesh(Plane());
    model3->setMesh(VertexCube());

    model->setMesh(Sphere()).setMaterial(TextureMaterialBuilder()
        .setShininess(32.0)
        .setTexture(std::move(Texture("examples/textures/container2.png")))
        .setSpecularMap(std::move(Texture("examples/textures/container2_specular.png")))
        .build()
    );

    model2->setMaterial(TextureMaterialBuilder()
        .setShininess(1024)
        .setTexture(std::move(Texture("examples/textures/wall.jpg"))).build()
    );

    model3->setMaterial(TextureMaterialBuilder()
        .setShininess(32.0)
        .setTexture(std::move(Texture("examples/textures/container2.png")))
        .setSpecularMap(std::move(Texture("examples/textures/container2_specular.png")))
        .build()
    );

    lightModel->setMesh(Cube());
    lightModel->setMaterial<LightMaterial>(glm::vec3{1.0, 1.0, 1.0});
    lightModel2->setMesh(Cube());
    lightModel2->setMaterial<LightMaterial>(glm::vec3{1.0, 0.0, 0.0});
    
    Renderer renderer(*window.get(), camera);
    renderer.setSkybox(std::move(cubemap));
    //renderer.setSkybox({0.2, 0.2, 0.2});
    
    renderer
        .add(model)
        .add(lightModel)
        .add(lightModel2)
        .add(model2)
        .add(model3);

    renderer.addLightSource(light::make_point({
        .pos = {0, 0, -4.0},
        .color = {1, 1, 1},
        .attentuation = {
            .constant = 1.0,
            .linear = 0.0,
            .quadratic = 0.0
        }
    }));

    renderer.addLightSource(light::make_point({
        .pos = {0, 7.0, -4.0},
        .color = {1, 0, 0},
        .attentuation = {
            .constant = 1.0,
            .linear = 0.0,
            .quadratic = 0.5
        }
    }));

    auto amb = light::make_ambient({
        .intensity = 0.1,
        .color = {1.f, 1.f, 1.f}
    });

    renderer.addLightSource(light::make_dir({
        .direction = {0.0, -1.0, -1.0},
        .color = {1.f, 1.f, 1.f},
        .intensity = 0.1
    }));

    renderer.setAmbientLight(amb);

    static constexpr auto R = 3.0;

    lightModel->setTranslation({0, 0.0, -4.0});
    lightModel->setScaleXYZ({0.3, 0.3, 0.3});

    lightModel2->setTranslation({0, 7.0, -4.0});
    lightModel2->setScaleXYZ({0.3, 0.3, 0.3});

    model2->setScaleXYZ({20, 20, 20});
    model2->setTranslation({-5.0, 10, -7.0});
    model2->setRotationXYZ({M_PI/2, 0, 0});

    model3->setScaleXYZ({2, 2, 2});

    while (!glfwWindowShouldClose(window.get()))
    {
        renderer.render();
        auto theta = glfwGetTime();
        //amb->intensity = (1 + sin(theta))/2 * 0.4;
        model->setRotationXYZ({theta, 0, theta});
        model3->setRotationXYZ({theta, theta, 0});
        model->setTranslation({R * sin(theta), 2 * R * cos(theta), -5.0});
        
        camera.poll(window.get());
    }
}