#pragma once
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <memory>
#include <config.h>
#include <array>


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

        inline std::array<glm::mat4x4, 6> get_lightspace_matrices(PointLight point){
            auto shadowWidth = config::SHADOW_RESOLUTION.w;
            auto shadowHeight = config::SHADOW_RESOLUTION.h;
            auto perspective = glm::perspective(
                glm::radians(90.0f), 
                (GLfloat)config::SHADOW_RESOLUTION.w / 
                (GLfloat)config::SHADOW_RESOLUTION.h, 
                config::POINT_LIGHT_SHADOW_PLANES.near, 
                config::POINT_LIGHT_SHADOW_PLANES.far);

            return {
                perspective * glm::lookAt(point.pos, point.pos + glm::vec3{1.f, 0.f, 0.f}, {0.f, -1.f, 0.f}),
                perspective * glm::lookAt(point.pos, point.pos + glm::vec3{-1.f, 0.f, 0.f}, {0.f, -1.f, 0.f}),
                perspective * glm::lookAt(point.pos, point.pos + glm::vec3{0.f, 1.f, 0.f}, {0.f, 0.f, 1.f}),
                perspective * glm::lookAt(point.pos, point.pos + glm::vec3{0.f, -1.f, 0.f}, {0.f, 0.f, -1.f}),
                perspective * glm::lookAt(point.pos, point.pos + glm::vec3{0.f, 0.f, 1.f}, {0.f, -1.f, 0.f}),
                perspective * glm::lookAt(point.pos, point.pos + glm::vec3{0.f, 0.f, -1.f}, {0.f, -1.f, 0.f})
            };
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

        inline glm::mat4x4 get_lightspace_matrix(DirectionalLight dir, Camera& camera, float nearPlane=0.1, float farPlane=25.0){
            auto pv = glm::perspective(glm::radians(camera.getFov()), 
            camera.getAspectRatio(), nearPlane, farPlane) * glm::lookAt(camera.getPos(), camera.getPos() + camera.getDir(), UP);

            const auto corners = getFrustumCornersWorldSpace(pv);

            glm::vec3 center = glm::vec3(0, 0, 0);
            for (const auto& v : corners){
                center += glm::vec3(v);
            }
            center /= corners.size();

            const auto lightView = glm::lookAt(center - dir.direction, center, UP);

            float minX = std::numeric_limits<float>::max();
            float maxX = std::numeric_limits<float>::lowest();
            float minY = std::numeric_limits<float>::max();
            float maxY = std::numeric_limits<float>::lowest();
            float minZ = std::numeric_limits<float>::max();
            float maxZ = std::numeric_limits<float>::lowest();
            for (const auto& v : corners){
                const auto trf = lightView * v;
                minX = std::min(minX, trf.x);
                maxX = std::max(maxX, trf.x);
                minY = std::min(minY, trf.y);
                maxY = std::max(maxY, trf.y);
                minZ = std::min(minZ, trf.z);
                maxZ = std::max(maxZ, trf.z);
            }

            // Tune this parameter according to the scene
            constexpr float zMult = 1.f;
            if (minZ < 0){
                minZ *= zMult;
            } else {
                minZ /= zMult;
            }
            if (maxZ < 0){
                maxZ /= zMult;
            } else {
                maxZ *= zMult;
            }

            const glm::mat4 lightProjection = glm::ortho(minX, maxX, minY, maxY, minZ, maxZ);
            return lightProjection * lightView;
        }
    }
}



