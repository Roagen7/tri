/*
    this scene demonstrates shadows
*/

#include <tricore/tricore.h>
#include <triutil/triutil.h>
#include <triextra/triextra.h>


using namespace tri::core;
using namespace tri::core::materials;
using namespace tri::core::meshes;
using namespace tri::extra;
using namespace tri::util;

static constexpr auto width = 480;
static constexpr auto height = 480;

int main(){
    Window window("scene4", width, height);    
    Camera camera(width, height, {0, 0, 3.0}, {0, 0, -1.0f});
    
    ParticleGenerator generator;
    Renderer renderer(*window.get(), camera);
    renderer
        .setPostprocessing<postprocess::InvertPostprocess>()
        .setSkybox(Cubemap({
            .right = "examples/data/skybox/space/right.png",
            .left = "examples/data/skybox/space/left.png",
            .top = "examples/data/skybox/space/top.png",
            .bottom = "examples/data/skybox/space/bottom.png",
            .front = "examples/data/skybox/space/front.png",
            .back = "examples/data/skybox/space/back.png"
        }))
        .add([](){
            auto floor = std::make_shared<Model>();
            floor->setMesh(Plane())
                .setMaterial(TextureMaterialBuilder()
                    .setShininess(1024)
                    .setTexture(std::move(Texture("examples/data/textures/brickwall.jpg")))
                    .setNormalMap(std::move(Texture("examples/data/textures/brickwall_normal.jpg")))
                    .build()
                ).setScaleXYZ({20, 20, 20})
                .setTranslation({0, 0, 0})
                .enableCastShadow()
                .enableReceiveShadow()
                ;
            return floor;
        }())
        .addLightSource(light::make_dir({
            .direction = {-1, -1, 0},
            .color = {1, 1, 1},
            .intensity = 1
        }))
    ;

    static constexpr auto R = 5.0;
    while (!glfwWindowShouldClose(window.get()))
    {
        renderer.render();
        camera.poll(window.get());
    }
}