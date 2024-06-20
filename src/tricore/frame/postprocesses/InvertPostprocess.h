#pragma once
#include "shader_path.h"
#include <tricore/frame/BasePostprocess.h>
#include <fmt/format.h>

namespace {
    static constexpr auto INVERT = "invert";
}

namespace tri::core::postprocess {
    
    class InvertPostprocess : public BasePostprocess {
    public:
        InvertPostprocess() : BasePostprocess(fmt::format("{}/{}/{}.glsl", SHADER_PATH, POSTPROCESS, INVERT)){}

    };
}

