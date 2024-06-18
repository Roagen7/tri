#pragma once
#include <glm/vec3.hpp>
#include <memory>



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
        inline std::shared_ptr<AmbientLight> make_ambient(AmbientLight ambient){
            auto ptr = std::make_shared<AmbientLight>();
            ptr->intensity = ambient.intensity;
            ptr->color = ambient.color;
            return ptr;
        }

        inline std::shared_ptr<PointLight> make_point(PointLight point){
            auto ptr =  std::make_shared<PointLight>();
            ptr->pos = point.pos;
            ptr->attentuation = point.attentuation;
            ptr->color = point.color;
            return ptr;
        }

        inline std::shared_ptr<DirectionalLight> make_dir(DirectionalLight dir){
            auto ptr =  std::make_shared<DirectionalLight>();
            ptr->direction = dir.direction;
            ptr->color = dir.color;
            ptr->intensity = dir.intensity;
            return ptr;
        }
    }
}



