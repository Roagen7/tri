#pragma once
#include <tricore/model/Mesh.h>

namespace tri::core::meshes {
    inline Mesh VertexPlane(){
        Mesh mesh;
        mesh.setVertices({ 
            {5.0f, -0.5f,  5.0f},
            {-5.0f, -0.5f,  5.0f},
            {-5.0f, -0.5f, -5.0f},  
            {5.0f, -0.5f,  5.0f},  
            {-5.0f, -0.5f, -5.0f}, 
            {5.0f, -0.5f, -5.0f},  
        }).setTextureUnits({
                {2.0f, 0.0f},
                {0.0f, 0.0f},
                {0.0f, 2.0f},
                {2.0f, 0.0f},
                {0.0f, 2.0f},
                {2.0f, 2.0f}
        });

        return mesh;
    }
}

