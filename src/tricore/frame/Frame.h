#pragma once
#include <glad/glad.h>
#include <memory>

namespace tri::core {
    class Frame {
    public:
        Frame(GLuint colorAttachmentsCount, bool depthAttachment): colorAttachmentsCount(colorAttachmentsCount), depthAttachment{depthAttachment} {
            color = std::unique_ptr<GLuint>(new GLuint[colorAttachmentsCount]);
        }

        void setup(int width, int height);
        void bind();
        void unbind();

        GLuint* getColorAttachments();
        GLuint getColorAttachmentsCount();

        GLuint getDepthMap();

        ~Frame();
    private:
        void cleanup();
        GLuint fbo, rbo; 
        std::unique_ptr<GLuint> color{};
        GLuint depth;
        GLuint colorAttachmentsCount{};
        bool depthAttachment;

    };
}