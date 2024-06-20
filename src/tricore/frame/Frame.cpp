#include "Frame.h"

#include <cassert>

using namespace tri::core;

void Frame::setup(int width, int height){
    cleanup();
    glGenFramebuffers(1, &fbo);
    glGenTextures(colorAttachmentsCount, color.get());
    glGenRenderbuffers(1, &rbo);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

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

GLuint* Frame::getColorAttachments(){
    return color.get();
}

GLuint Frame::getColorAttachmentsCount(){
    return colorAttachmentsCount;
}


void Frame::cleanup(){
    glDeleteRenderbuffers(1, &rbo);
    if(color){
        glDeleteTextures(colorAttachmentsCount, color.get());
    }
    glDeleteRenderbuffers(1, &rbo);
}


Frame::~Frame(){
   cleanup();
}

void Frame::bind(){
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
}

void Frame::unbind(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

