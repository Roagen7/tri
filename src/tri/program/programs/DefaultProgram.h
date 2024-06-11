#pragma once

#include <tri/program/Program.h>
#include <fmt/format.h>

#include "shader_path.h"

static constexpr auto DEFAULT_PATH = "default";

class DefaultProgram : public Program {
public:
    DefaultProgram():Program(
        fmt::format("{}/{}/vs.glsl", SHADER_PATH, DEFAULT_PATH), 
        fmt::format("{}/{}/fs.glsl", SHADER_PATH, DEFAULT_PATH)) {}

};