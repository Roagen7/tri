#pragma once

#include <tricore/program/Program.h>
#include <fmt/format.h>

#include "shader_path.h"

static constexpr auto DEBUG_PATH = "debug";

namespace tri::core::materials {
    class DebugMaterial : public Program {
    public:
        DebugMaterial():Program(
            fmt::format("{}/{}/vs.glsl", SHADER_PATH, DEBUG_PATH), 
            fmt::format("{}/{}/fs.glsl", SHADER_PATH, DEBUG_PATH)
            ) {
        }

    };
}


