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


        // source: https://learnopengl.com/code_viewer_gh.php?code=src/8.guest/2021/2.csm/shadow_mapping.cpp
        inline std::vector<glm::vec4> getFrustumCornersWorldSpace(const glm::mat4& projview){
                const auto inv = glm::inverse(projview);

                std::vector<glm::vec4> frustumCorners;
                for (unsigned int x = 0; x < 2; ++x){
                    for (unsigned int y = 0; y < 2; ++y){
                        for (unsigned int z = 0; z < 2; ++z){
                            const glm::vec4 pt = inv * glm::vec4(2.0f * x - 1.0f, 2.0f * y - 1.0f, 2.0f * z - 1.0f, 1.0f);
                            frustumCorners.push_back(pt / pt.w);
                        }
                    }
                }
                return frustumCorners;
        }

        inline glm::mat4x4 get_lightspace_matrix(DirectionalLight dir, Camera& camera){
            // float farPlane = config::CAMERA_FAR_PLANE;
            // float nearPlane = config::CAMERA_NEAR_PLANE;
            // const auto corners = getFrustumCornersWorldSpace(camera.view());

            // glm::vec3 center = glm::vec3(0, 0, 0);
            // for (const auto& v : corners){
            //     center += glm::vec3(v);
            // }
            // center /= corners.size();

            // const auto lightView = glm::lookAt(center + dir.direction, center, UP);

            // float minX = std::numeric_limits<float>::max();
            // float maxX = std::numeric_limits<float>::lowest();
            // float minY = std::numeric_limits<float>::max();
            // float maxY = std::numeric_limits<float>::lowest();
            // float minZ = std::numeric_limits<float>::max();
            // float maxZ = std::numeric_limits<float>::lowest();
            // for (const auto& v : corners){
            //     const auto trf = lightView * v;
            //     minX = std::min(minX, trf.x);
            //     maxX = std::max(maxX, trf.x);
            //     minY = std::min(minY, trf.y);
            //     maxY = std::max(maxY, trf.y);
            //     minZ = std::min(minZ, trf.z);
            //     maxZ = std::max(maxZ, trf.z);
            // }

            // // Tune this parameter according to the scene
            // constexpr float zMult = 1.0f;
            // if (minZ < 0){
            //     minZ *= zMult;
            // } else {
            //     minZ /= zMult;
            // }
            // if (maxZ < 0){
            //     maxZ /= zMult;
            // } else
            // {
            //     maxZ *= zMult;
            // }

            // const glm::mat4 lightProjection = glm::ortho(minX, maxX, minY, maxY, minZ, maxZ);
            // return lightProjection * lightView;

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



