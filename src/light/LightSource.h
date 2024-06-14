#include <glm/vec3.hpp>

struct PointLight {
    glm::vec3 pos;
    glm::vec3 color;

    struct {
        float constant{1};
        float linear{0};
        float quadratic{0};
    } attentuation;

};

struct AmbientLight {
    float intensity{0.0};
    glm::vec3 color{0,0,0};
};