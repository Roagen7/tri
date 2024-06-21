#include "Frame.h"

#include <cassert>
#include "config.h"

using namespace tri::core;

void Frame::setup(int width, int height){
    cleanup();
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Frame::cleanup(){
    glDeleteFramebuffers(1, &fbo);
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

