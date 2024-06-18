#include <glad/glad.h>
#include "glfwinclude.h"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <tricore/Renderer.h>
#include <tricore/program/Program.h>
#include <tricore/program/materials/SolidMaterial.h>
#include <tricore/program/materials/LightMaterial.h>
#include <tricore/program/materials/SkyboxMaterial.h>
#include <tricore/program/materials/DebugMaterial.h>
#include <tricore/model/meshes/Cube.h>
#include <tricore/model/meshes/Plane.h>
#include <tricore/model/meshes/Sphere.h>

#include <tricore/model/meshes/VertexCube.h>
#include <triutil/files.h>
#include <iostream>
#include <tricore/model/Mesh.h>
#include <tricore/Camera.h>
#include <tricore/model/Model.h>
#include <triutil/window_init.h>
#include <tricore/texture/Texture.h>
#include <tricore/program/materials/TextureMaterial.h>
#include <tricore/texture/Cubemap.h>

/*
small TODO list:
> add heightmap model
> add postprocessing operation
> add sprites
> add shadows
> add hdr
> add bloom
> split to examples
> add cel shader material
...
> add entity tree
*/


int main(void){
    /*
    IN THE FUTURE
    entry point for engine's gui 
    */
}