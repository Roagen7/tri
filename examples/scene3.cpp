/*
    this scene demonstrates:
    > shadows
    > bloom
*/

#include <tricore/tricore.h>
#include <triutil/triutil.h>


using namespace tri::core;
using namespace tri::core::materials;
using namespace tri::core::meshes;
using namespace tri::util;

static constexpr auto width = 480;
static constexpr auto height = 480;

int main(){
    Window window("scene3", width, height);    
    Camera camera(width, height, {0, 0, 3.0}, {0, 0, -1.0f});

    Renderer renderer(*window.get(), camera);

    auto light = light::make_point({
            .pos = {0, 0, -4.0},
            .color = {1, 1, 1},
            .attentuation = {
                .constant = 1.0,
                .linear = 0.0,
                .quadratic = 0.0
            }
    });

    static constexpr glm::vec3 secondLightPos = {-5, 1, -5};

    auto lightModel = std::make_shared<Model>();
        lightModel->setMesh(Sphere())
        .setMaterial<LightMaterial>(glm::vec3{1.0, 1.0, 1.0})
        .setTranslation({0, 4.0, -4.0})
        .setScaleXYZ({0.3, 0.3, 0.3});

    auto dirLight = light::make_dir({
            .direction = {-1, -1, 0},
            .color = {1, 1, 1},
            .intensity = 1
    });

    renderer
        // .setPostprocessing<postprocess::InvertPostprocess>()
        .setSkybox(Cubemap({
            .right = "examples/data/skybox/space/right.png",
            .left = "examples/data/skybox/space/left.png",
            .top = "examples/data/skybox/space/top.png",
            .bottom = "examples/data/skybox/space/bottom.png",
            .front = "examples/data/skybox/space/front.png",
            .back = "examples/data/skybox/space/back.png"
        }))
        .add([](){
            auto cubeModel = std::make_shared<Model>();
            cubeModel->setMesh(VertexCube())
            .enableCastShadow()
            .enableReceiveShadow()
            .setMaterial<SolidMaterial>(glm::vec3{1.0, 0.0, 0.0})
            .setTranslation({2, 0.5, 1})
            ;
            return cubeModel;
        }())
        .add([](){
            auto capsule = std::make_shared<Model>();
            capsule->setMesh(Mesh::fromFile("examples/data/mesh/textured_with_normals.obj"))
            .enableCastShadow()
            .enableReceiveShadow()
            .setMaterial<SolidMaterial>(glm::vec3{0.0, 0.0, 1.0}, 1.0, 0.3, 1.0)
            .setTranslation({0.0f, 1.5f, 0.0})
            ;
            return capsule;
        }())
        .add([](){
            auto lightModel = std::make_shared<Model>();
            lightModel->setMesh(Cube())
            .setMaterial<LightMaterial>(glm::vec3{1.0, 1.0, 1.0})
            .setTranslation(secondLightPos)
            .setScaleXYZ({0.3, 0.3, 0.3});
            return lightModel;
        }())
        .add(lightModel)
        .add([](){
            auto floor = std::make_shared<Model>();
            floor->setMesh(Plane())
                .enableCastShadow()
                .enableReceiveShadow()
                .setMaterial(TextureMaterialBuilder()
                    .setShininess(1024)
                    .setTexture(TextureResourceManager::texture("examples/data/textures/brickwall.jpg"))
                    .setNormalMap(TextureResourceManager::texture("examples/data/textures/brickwall_normal.jpg"))
                    .build()
                ).setScaleXYZ({20, 20, 20})
                .setTranslation({0, 0, 0})
                ;
            return floor;
        }())
        .addLightSource(light)
        // .addLightSource(light::make_point({
        //     .pos = secondLightPos,
        //     .color = {1, 1, 1},
        //     .attentuation = {
        //         .constant = 1.0,
        //         .linear = 0.0,
        //         .quadratic = 0.0
        //     }
        // }))
        // .addLightSource(dirLight)
        // .addLightSource(light::make_dir({
        //     .direction = {-1, -1, 0},
        //     .color = {1, 1, 1},
        //     .intensity = 1
        // }))
        // .addLightSource(light::make_dir({
        //     .direction = {1, -1, 0},
        //     .color = {1, 1, 1},
        //     .intensity = 1
        // }))
        ;

    static constexpr auto R = 5.0;
    while (!glfwWindowShouldClose(window.get()))
    {
        renderer.render();
        camera.poll(window.get());
        auto theta = glfwGetTime();
        glm::vec3 pos = glm::vec3{R * sin(theta), 3.0,  R * cos(theta)};
        dirLight->direction = glm::vec3({sin(theta), -1.0, cos(theta)});
        light->pos = pos;
        lightModel->setTranslation(pos);
    }
}