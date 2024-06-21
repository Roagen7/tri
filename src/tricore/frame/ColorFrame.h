#pragma once

#include "Frame.h"
#include <glad/glad.h>
#include <memory>

namespace tri::core {
    class ColorFrame : public Frame {
    public:
        ColorFrame(GLuint colorAttachmentsCount);
        
        GLuint* getColorAttachments();
        GLuint getColorAttachmentsCount();
        void setup(int width, int height) override;
        void cleanup() override;
        
    private:
        GLuint colorAttachmentsCount;
        GLuint rbo;
        std::unique_ptr<GLuint> color{};
    };
}
