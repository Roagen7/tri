#pragma once

#include "Frame.h"

namespace tri::core {
    class DepthFrame : public Frame {
    public:
        DepthFrame() = default;
        
        GLuint getDepthMap();
        void setup(int width, int height) override;
        void cleanup() override;
        
    private:
        GLuint depth;
    };
}



