#pragma once

#include <tricore/program/Program.h>
#include "SolidMaterial.h"
#include <fmt/format.h>

#include "shader_path.h"

namespace tri::core::materials {
    class DefaultMaterial : public SolidMaterial {
    public:
        DefaultMaterial():SolidMaterial({1, 1, 1}, 1.0, 0.0, 1.0){}
    };
}