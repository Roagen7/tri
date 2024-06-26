#pragma once
#include "Model.h"
#include <tricore/program/Program.h>
#include <tricore/texture/Texture.h>
#include <tricore/texture/TextureResourceManager.h>

namespace tri::core {
    class HeightmapModel : public Model {
    public:
        HeightmapModel(texid_t heighmap, float heightScale);

   

    };
}