#pragma once
#include <tricore/model/Mesh.h>

#include <tricore/model/Mesh.h>


namespace tri::core::meshes {
    inline Mesh VertexCube(){
        Mesh mesh;


        mesh.setVertices({
            {-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f,  0.5f, -0.5f},
            {0.5f,  0.5f, -0.5f}, {-0.5f,  0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f},

            {-0.5f, -0.5f,  0.5f},{ 0.5f, -0.5f,  0.5f},{0.5f,  0.5f,  0.5f},
            {0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f},{-0.5f, -0.5f,  0.5f},

            {-0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f},
            { -0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f,  0.5f},{ -0.5f,  0.5f,  0.5f},

            {0.5f,  0.5f,  0.5f}, {0.5f,  0.5f, -0.5f}, {0.5f, -0.5f, -0.5f},
            {0.5f, -0.5f, -0.5f}, {0.5f, -0.5f,  0.5f}, {0.5f,  0.5f,  0.5f},

            {-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f, -0.5f,  0.5f},
            {0.5f, -0.5f,  0.5f}, {-0.5f, -0.5f,  0.5f}, {-0.5f, -0.5f, -0.5f},

            {-0.5f,  0.5f, -0.5f}, {0.5f,  0.5f, -0.5f}, {0.5f,  0.5f,  0.5f},
            { 0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f, -0.5f}
        }).setNormals({
            {0.0f,  0.0f, -1.0f},
            {0.0f,  0.0f, -1.0f},
            {0.0f,  0.0f, -1.0f},
            {0.0f,  0.0f, -1.0f},
            {0.0f,  0.0f, -1.0f},
            {0.0f,  0.0f, -1.0f},
            {0.0f,  0.0f, 1.0f},
            {0.0f,  0.0f, 1.0f},
            {0.0f,  0.0f, 1.0f},
            {0.0f,  0.0f, 1.0f},
            {0.0f,  0.0f, 1.0f},
            {0.0f,  0.0f, 1.0f},
            {-1.0f,  0.0f,  0.0f},
            {-1.0f,  0.0f,  0.0f},
            {-1.0f,  0.0f,  0.0f},
            {-1.0f,  0.0f,  0.0f},
            {-1.0f,  0.0f,  0.0f},
            {-1.0f,  0.0f,  0.0f},
            { 1.0f,  0.0f,  0.0f},
            { 1.0f,  0.0f,  0.0f},
            { 1.0f,  0.0f,  0.0f},
            { 1.0f,  0.0f,  0.0f},
            { 1.0f,  0.0f,  0.0f},
            { 1.0f,  0.0f,  0.0f},
            {0.0f, -1.0f,  0.0f}, 
            {0.0f, -1.0f,  0.0f},
            {0.0f, -1.0f,  0.0f}, 
            {0.0f, -1.0f,  0.0f}, 
            {0.0f, -1.0f,  0.0f}, 
            {0.0f, -1.0f,  0.0f}, 
            {0.0f,  1.0f,  0.0f},
            {0.0f,  1.0f,  0.0f},
            {0.0f,  1.0f,  0.0f},
            {0.0f,  1.0f,  0.0f},
            {0.0f,  1.0f,  0.0f},
            {0.0f,  1.0f,  0.0f}
        }).setTextureUnits({
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f},
            {0.0f, 0.0f},

            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f},
            {0.0f, 0.0f},

            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f},
            {0.0f, 1.0f},
            {0.0f, 0.0f},
            {1.0f, 0.0f},

            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f},
            {0.0f, 1.0f},
            {0.0f, 0.0f},
            {1.0f, 0.0f},

            {0.0f, 1.0f},
            {1.0f, 1.0f},
            {1.0f, 0.0f},
            {1.0f, 0.0f},
            {0.0f, 0.0f},
            {0.0f, 1.0f},

            {0.0f, 1.0f},
            {1.0f, 1.0f},
            {1.0f, 0.0f},
            {1.0f, 0.0f},
            {0.0f, 0.0f},
            {0.0f, 1.0f}
        });

        return mesh;
    }
}
