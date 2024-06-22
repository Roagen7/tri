#pragma once

#include "Frame.h"

namespace tri::core {
    class OmniDepthFrame : public Frame {
    public:
        OmniDepthFrame() = default;
        
        GLuint getDepthMap();
        void setup(int width, int height) override;
        void cleanup() override;
        
    private:
        GLuint depth;
    };
}



