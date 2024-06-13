#include <tri/model/Mesh.h>

class Plane : public PredefinedMesh {
public:
    Plane(){
        vertices = std::vector<glm::vec3>({
            {0, 0, 0},
            {0, 0, 1},
            {1, 0, 0},
            {1, 0, 1}
        });

        indices = std::vector<glm::ivec3>({
            {0, 1, 2},
            {1, 2, 3}
        });

        normals = std::vector<glm::vec3>({
            {0, 1, 0},
            {0, 1, 0},
            {0, 1, 0},
            {0, 1, 0}
        });

        texture = std::vector<glm::vec2>({
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
        });

        setup();
    }

};