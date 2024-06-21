#pragma once
#include <glad/glad.h>
#include <memory>

namespace tri::core {
    class Frame {
    public:
        Frame() = default;
        virtual void setup(int width, int height);
        void bind();
        void unbind();
        virtual ~Frame();

    protected:
        GLuint fbo;
        virtual void cleanup();

    };
}