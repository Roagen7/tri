#pragma once

#include <tri/program/Program.h>
#include <fmt/format.h>

#include "shader_path.h"

static constexpr auto DEBUG_PATH = "debug";

class DebugMaterial : public Program {
public:
    DebugMaterial():Program(
        fmt::format("{}/{}/vs.glsl", SHADER_PATH, DEBUG_PATH), 
        fmt::format("{}/{}/fs.glsl", SHADER_PATH, DEBUG_PATH)
        ) {
    }

};
