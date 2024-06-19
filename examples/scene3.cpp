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

    static constexpr glm::vec3 secondLightPos = {-10, 1, -10};

    auto lightModel = std::make_shared<Model>();
        lightModel->setMesh(Sphere())
        .setMaterial<LightMaterial>(glm::vec3{1.0, 1.0, 1.0})
        .setTranslation({0, 4.0, -4.0})
        .setScaleXYZ({0.3, 0.3, 0.3});

    renderer
        .setPostprocessing<postprocess::GrayscalePostprocess>()
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
            .setMaterial<SolidMaterial>(glm::vec3{1.0, 0.0, 0.0})
            .setTranslation({-7, -0.5, -10});
            return cubeModel;
        }())
        .add([](){
            auto capsule = std::make_shared<Model>();
            capsule->setMesh(Mesh::fromFile("examples/data/mesh/textured_with_normals.obj"))
            .setMaterial<SolidMaterial>(glm::vec3{0.0, 0.0, 1.0}, 1.0, 0.3, 1.0)
            .setTranslation({-5, -0.5, -5});
            return capsule;
        }())
        .add([](){
            auto lightModel = std::make_shared<Model>();
            lightModel->setMesh(Sphere())
            .setMaterial<LightMaterial>(glm::vec3{1.0, 1.0, 1.0})
            .setTranslation(secondLightPos)
            .setScaleXYZ({0.3, 0.3, 0.3});
            return lightModel;
        }())
        .add(lightModel)
        .add([](){
            auto floor = std::make_shared<Model>();
            floor->setMesh(Plane())
                .setMaterial(TextureMaterialBuilder()
                    .setShininess(1024)
                    .setTexture(std::move(Texture("examples/data/textures/brickwall.jpg")))
                    .setNormalMap(std::move(Texture("examples/data/textures/brickwall_normal.jpg")))
                    .build()
                ).setScaleXYZ({20, 20, 20})
                .setTranslation({-5, -2, -10});
            return floor;
        }())
        .addLightSource(light)
        .addLightSource(light::make_point({
            .pos = secondLightPos,
            .color = {1, 1, 1},
            .attentuation = {
                .constant = 1.0,
                .linear = 0.1,
                .quadratic = 0.0
            }
        }));

    static constexpr auto R = 5.0;
    while (!glfwWindowShouldClose(window.get()))
    {
        renderer.render();
        camera.poll(window.get());
        auto theta = glfwGetTime();
        glm::vec3 pos = glm::vec3{R * sin(theta), 3.0,  R * cos(theta)};
        light->pos = pos;
        lightModel->setTranslation(pos);
    }
}