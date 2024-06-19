#include "Frame.h"

#include <cassert>

using namespace tri::core;

void Frame::setup(int width, int height){
    cleanup();
    glGenFramebuffers(1, &fbo);
    glGenTextures(1, &color);
    glGenRenderbuffers(1, &rbo);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glBindTexture(GL_TEXTURE_2D, color);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
}

GLuint Frame::getTexture(){
    return color;
}


void Frame::cleanup(){
    glDeleteRenderbuffers(1, &rbo);
    glDeleteTextures(1, &color);
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
