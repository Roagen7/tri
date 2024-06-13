#pragma once

#include <tri/program/Program.h>
#include "SolidMaterial.h"
#include <fmt/format.h>

#include "shader_path.h"

class DefaultMaterial : public SolidMaterial {
public:
    DefaultMaterial():SolidMaterial({1, 1, 1}, 1.0, 0.0, 1.0){}
};