#pragma once
#include "shader_path.h"
#include <tricore/frame/BasePostprocess.h>
#include <fmt/format.h>

namespace {
    static constexpr auto BLOOM = "bloom";
}

namespace tri::core::postprocess {
    
    class VerticalBlurPostprocess : public BasePostprocess {
    public:
        VerticalBlurPostprocess() : BasePostprocess(fmt::format("{}/{}/{}/vertical.glsl", SHADER_PATH, POSTPROCESS, BLOOM)){}
    };

    class HorizontalBlurPostprocess : public BasePostprocess {
    public:
        HorizontalBlurPostprocess() : BasePostprocess(fmt::format("{}/{}/{}/horizontal.glsl", SHADER_PATH, POSTPROCESS, BLOOM)){}
    };
}

