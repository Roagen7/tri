#pragma once
#include <tricore/model/Mesh.h>

namespace tri::core::meshes {
    inline Mesh Plane(){
        Mesh mesh;
        mesh.setVertices({ {-0.5, 0, -0.5},
                {-0.5, 0, 0.5},
                {0.5, 0, -0.5},
                {0.5, 0, 0.5}
            }).setIndices({{0, 1, 2},
                {1, 2, 3}
            }).setNormals({
                {0, 1, 0},
                {0, 1, 0},
                {0, 1, 0},
                {0, 1, 0}
            }).setTextureUnits({
                {0, 0},
                {0, 1},
                {1, 0},
                {1, 1}
            });
        return mesh;
    }
}

