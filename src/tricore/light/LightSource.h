#pragma once
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <memory>
#include <config.h>
#include <array>
#include <tricore/Camera.h>


namespace tri::core {
    struct PointLight {
        glm::vec3 pos;
        glm::vec3 color;

        struct {
            float constant{1};
            float linear{0};
            float quadratic{0};
        } attentuation;

    };

    struct DirectionalLight {
        glm::vec3 direction{0, 0, 0};
        glm::vec3 color{0, 0, 0};
        float intensity{0};
    };

    struct AmbientLight {
        float intensity{0.0};
        glm::vec3 color{0,0,0};
    };

    namespace light {
        std::shared_ptr<AmbientLight> make_ambient(AmbientLight ambient);
        std::shared_ptr<PointLight> make_point(PointLight point);
        std::shared_ptr<DirectionalLight> make_dir(DirectionalLight dir);

        std::array<glm::mat4x4, 6> get_lightspace_matrices(PointLight point);
        glm::mat4x4 get_lightspace_matrix(DirectionalLight dir, Camera& camera, float nearPlane=0.1, float farPlane=25.0);
    }
}



