#pragma once
#include "shader_path.h"
#include <tricore/frame/BasePostprocess.h>
#include <fmt/format.h>

namespace {
    static constexpr auto GRAYSCALE = "grayscale";
}

namespace tri::core::postprocess {
    
    class GrayscalePostprocess : public BasePostprocess {
    public:
        GrayscalePostprocess() : BasePostprocess(fmt::format("{}/{}/{}.glsl", SHADER_PATH, POSTPROCESS, GRAYSCALE)){}

    };
}

