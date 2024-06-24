#pragma once

#include "Frame.h"

namespace tri::core {
    class DepthFrame : public Frame {
    public:
        DepthFrame()  {}
        
        void setCascadeLevels(int levels);
        GLuint getDepthMap();
        void setup(int width, int height) override;
        void cleanup() override;
        
    private:
        GLuint depth;
        int shadowCascadeLevels{1};
    };
}



