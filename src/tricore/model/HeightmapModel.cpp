#include "HeightmapModel.h"

#include "./meshes/Plane.h"
#include <fmt/format.h>
#include <tricore/program/materials/TextureMaterial.h>
#include <tricore/program/ShaderLib.h>
#include <triutil/files.h>

using namespace tri::core;
using namespace tri::core::materials;

static constexpr auto HEIGHTMAPPED_VS = "heightmap";
static constexpr auto NUM_PATCH_PTS = 3;

class HeightmapMaterial : public TextureMaterial {
public:
    HeightmapMaterial(Texture&& heightmap, float heightScale): TextureMaterial(){
        glPatchParameteri(GL_PATCH_VERTICES, NUM_PATCH_PTS);
        GLint maxTessLevel;
        glGetIntegerv(GL_MAX_TESS_GEN_LEVEL, &maxTessLevel);
        std::cout << "Max available tess level: " << maxTessLevel << std::endl;
        readShaders("", "", "", 
            fmt::format("{}/{}/tes.glsl", SHADER_PATH, HEIGHTMAPPED_VS),
            fmt::format("{}/{}/tcs.glsl", SHADER_PATH, HEIGHTMAPPED_VS)
        );
        compileShaders();
        setHeightMap(std::move(heightmap), 0.0);
        uniformFloat("heightScale", heightScale);
        uniformVec3("uColor", {1, 0, 0});
        uniformInt("flatColor", 1);
    }
};


HeightmapModel::HeightmapModel(Texture&& heightmap, float heightScale): Model(){
    setMesh(meshes::Plane());
    setMaterial(std::make_unique<HeightmapMaterial>(std::move(heightmap), heightScale));
    mesh.enableTesselation();
}
