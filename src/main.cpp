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
> refactor (namespaces + better names for libs + example targets)
> add heightmap model
> add postprocessing operation
> add sprites
> add shadows
> add hdr
> add bloom
> split to examples
> add cel shader material
...
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

    model->setMesh(Sphere())
    .setMaterial(TextureMaterialBuilder()
        .setShininess(32.0)
        .setTexture(std::move(Texture("examples/textures/container2.png")))
        .setSpecularMap(std::move(Texture("examples/textures/container2_specular.png")))
        .build()
    );

    model2->setMaterial(TextureMaterialBuilder()
        .setShininess(1024)
        .setTexture(std::move(Texture("examples/textures/bricks.jpg")))
        .setNormalMap(std::move(Texture("examples/textures/bricks_normal.jpg")))
        .setHeightMap(std::move(Texture("examples/textures/bricks_heightmap.jpg")), 0.05f)
        .build()
    ).setBorder({0, 1, 0}, 0.10);

    model3->setMaterial(TextureMaterialBuilder()
        .setShininess(32.0)
        .setTexture(std::move(Texture("examples/textures/container2.png")))
        .setSpecularMap(std::move(Texture("examples/textures/container2_specular.png")))
        .build()
    ).setBorder({1, 0, 0}, 0.05);

    auto amb = light::make_ambient({
        .intensity = 0.1,
        .color = {1.f, 1.f, 1.f}
    });
    Renderer renderer(*window.get(), camera);
    renderer
        .setSkybox(std::move(cubemap))
        .add(model)
        .add([](){
            auto lightModel = std::make_shared<Model>();
            lightModel->setMesh(Cube()).setMaterial<LightMaterial>(glm::vec3{1.0, 1.0, 1.0});
            lightModel->setTranslation({0, 0.0, -4.0});
            lightModel->setScaleXYZ({0.3, 0.3, 0.3});
            return lightModel;
        }())
        .add([](){
            auto lightModel = std::make_shared<Model>();
            lightModel->setMesh(Cube()).setMaterial<LightMaterial>(glm::vec3{0.0, 0.0, 1.0}).setTranslation(glm::vec3{0, 7.0, -4.0}).setScaleXYZ({0.3, 0.3, 0.3});
            return lightModel;
        }())
        .add(model2)
        .add(model3)
        .add([](){
            auto wallModel = std::make_shared<Model>();
            wallModel->setMesh(Plane())
                .setMaterial(TextureMaterialBuilder()
                    .setShininess(1024)
                    .setTexture(std::move(Texture("examples/textures/brickwall.jpg")))
                    .setNormalMap(std::move(Texture("examples/textures/brickwall_normal.jpg")))
                    .build()
                ).setScaleXYZ({20, 20, 20})
                .setTranslation({-5, -2, -10});
            return wallModel;
        }())
        .add([](){
            auto grassModel = std::make_shared<Model>();
            grassModel->setMesh(Plane())
                .setMaterial(TextureMaterialBuilder()
                    .setTexture(std::move(Texture("examples/textures/grass.png")))
                    .build()
                )
                .setRotationXYZ({M_PI/2, 0, 0})
                .setTranslation({-5, -1, -10})
                .setScaleXYZ({5, 5, 5}).enableTransparency();
            return grassModel;
        }())
        .add([](){
            auto grassModel = std::make_shared<Model>();
            grassModel->setMesh(Plane())
                .setMaterial(TextureMaterialBuilder()
                    .setTexture(std::move(Texture("examples/textures/grass.png")))
                    .build()
                )
                .setRotationXYZ({M_PI/2, 0, 0})
                .setTranslation({-5, -1, -12})
                .setScaleXYZ({5, 5, 5}).enableTransparency();
            return grassModel;
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
        .addLightSource(light::make_point({
            .pos = {0, 7.0, -4.0},
            .color = {0, 0, 1},
            .attentuation = {
                .constant = 1.0,
                .linear = 0.0,
                .quadratic = 0.5
            }
        }))
        .addLightSource(light::make_dir({
            .direction = {0.0, -1.0, -1.0},
            .color = {1.f, 1.f, 1.f},
            .intensity = 0.1
        }))
        .setAmbientLight(amb);

    static constexpr auto R = 3.0;

    model2->setScaleXYZ({10, 10, 10});
    model2->setTranslation({-2.5, 3, -5.0});
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