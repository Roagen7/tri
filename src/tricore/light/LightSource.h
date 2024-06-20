#pragma once
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <memory>
#include <config.h>


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

        inline glm::mat4x4 get_lightspace_matrix(PointLight point){
            auto shadowWidth = config::SHADOW_RESOLUTION.w;
            auto shadowHeight = config::SHADOW_RESOLUTION.h;
            return glm::perspective(glm::radians(45.0f), 
            (GLfloat)shadowWidth / (GLfloat)shadowHeight, 
            config::CAMERA_NEAR_PLANE, 
            config::CAMERA_FAR_PLANE);
        }

        inline glm::mat4x4 get_lightspace_matrix(DirectionalLight dir){
            static constexpr auto lightScale = 5.f;

            auto shadowWidth = config::SHADOW_RESOLUTION.w;
            auto shadowHeight = config::SHADOW_RESOLUTION.h;
            auto lightProjection = glm::perspective(glm::radians(45.0f), 
            (GLfloat)shadowWidth / (GLfloat)shadowHeight, 
            config::CAMERA_NEAR_PLANE, 
            config::CAMERA_FAR_PLANE);

            // TODO: make dependent on camera pos
            lightProjection = glm::ortho(-30.0f, 30.0f, -30.0f, 30.0f, -30.0f, 30.f);
            auto lightView = glm::lookAt(-dir.direction * lightScale, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));   
            return lightProjection * lightView;
        }
    }
}



