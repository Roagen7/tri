#pragma once
#include "Model.h"
#include <tricore/program/Program.h>
#include <tricore/texture/Texture.h>

namespace tri::core {
    class HeightmapModel : public Model {
    public:
        HeightmapModel(Texture&& heighmap, float heightScale);

   

    };
}