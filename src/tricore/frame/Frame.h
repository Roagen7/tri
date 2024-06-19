#pragma once
#include <glad/glad.h>

namespace tri::core {
    class Frame {
    public:
        Frame() = default;

        void setup(int width, int height);
        void bind();
        void unbind();

        GLuint getTexture();

        ~Frame();
    private:
        void cleanup();
        GLuint fbo, rbo, color;

    };
}