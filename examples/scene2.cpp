/*
    this scene shows tesselation
*/
#include <tricore/tricore.h>
#include <triutil/triutil.h>

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
    
     
    auto amb = light::make_ambient({
        .intensity = 0.1,
        .color = {1.f, 1.f, 1.f}
    });

    auto skybox = Cubemap({
            .right = "examples/data/skybox/right.jpg",
            .left = "examples/data/skybox/left.jpg",
            .top = "examples/data/skybox/top.jpg",
            .bottom = "examples/data/skybox/bottom.jpg",
            .front = "examples/data/skybox/front.jpg",
            .back = "examples/data/skybox/back.jpg"
    });



    Renderer renderer(*window.get(), camera);
    renderer
        .setSkybox(std::move(skybox))
        .add([](){
            auto heightmapModel = std::make_shared<HeightmapModel>(std::move(Texture("examples/data/textures/iceland_heightmap.png")), 0.5);
            heightmapModel->setScaleXYZ({100, 100, 100}).setTranslation({0, -4.0, 0.0});
            
            return heightmapModel;
        }())
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