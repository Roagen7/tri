#pragma once
#include <glad/glad.h>
#include <memory>

namespace tri::core {
    class Frame {
    public:
        Frame(GLuint colorAttachmentsCount): colorAttachmentsCount(colorAttachmentsCount) {
            color = std::unique_ptr<GLuint>(new GLuint[colorAttachmentsCount]);
        }

        void setup(int width, int height);
        void bind();
        void unbind();

        GLuint* getColorAttachments();
        GLuint getColorAttachmentsCount();

        ~Frame();
    private:
        void cleanup();
        GLuint fbo, rbo; 
        std::unique_ptr<GLuint> color{};
        GLuint colorAttachmentsCount{};

    };
}