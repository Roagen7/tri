#include "ColorFrame.h"


using namespace tri::core;

ColorFrame::ColorFrame(GLuint colorAttachmentsCount): colorAttachmentsCount(colorAttachmentsCount){
    color = std::unique_ptr<GLuint>(new GLuint[colorAttachmentsCount]);
}
    
GLuint* ColorFrame::getColorAttachments(){
    return color.get();
}

GLuint ColorFrame::getColorAttachmentsCount(){
    return colorAttachmentsCount;
}

void ColorFrame::setup(int width, int height) {
    Frame::setup(width, height);
    glGenTextures(colorAttachmentsCount, color.get());
    glGenRenderbuffers(1, &rbo);
    
    for(auto i = 0u; i < colorAttachmentsCount; i++){
        glBindTexture(GL_TEXTURE_2D, color.get()[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, color.get()[i], 0);
    }

    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
}

void ColorFrame::cleanup() {
    Frame::cleanup();
    if(color){
        glDeleteTextures(colorAttachmentsCount, color.get());
    }
    glDeleteRenderbuffers(1, &rbo);
}
