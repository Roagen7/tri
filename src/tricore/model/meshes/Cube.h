#pragma once
#include <tricore/model/Mesh.h>

namespace tri::core::meshes {
 
    inline Mesh Cube(){
        Mesh mesh;
        mesh.setVertices({
                {-1.f, -1.f, -1.f}, // 0
                {-1.f, -1.f, 1.f}, // 1
                {-1.f, 1.f, -1.f}, // 2
                {-1.f, 1.f, 1.f}, // 3
                {1.f, -1.f, -1.f}, // 4
                {1.f, -1.f, 1.f}, // 5
                {1.f, 1.f, -1.f}, // 6
                {1.f, 1.f, 1.f}  // 7
            }).setIndices({     // front
                {0, 2, 4},
                {2, 4, 6},
                // back
                {3, 5, 7},
                {1, 3, 5},
                // left
                {0, 2, 3},
                {0, 1, 3},
                // right
                {4, 5, 7},
                {4, 6, 7},
                // top
                {2, 3, 6},
                {3, 6, 7},
                // bottom
                {0, 1, 4},
                {1, 4, 5}
            }).setNormals({{-1, -1, -1}, // 0
                {-1, -1, 1}, // 1
                {-1, 1, -1}, // 2
                {-1, 1, 1}, // 3
                {1, -1, -1}, // 4
                {1, -1, 1}, // 5
                {1, 1, -1}, // 6
                {1, 1, 1}});

        return mesh;
    }
}
