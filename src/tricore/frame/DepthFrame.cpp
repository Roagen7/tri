#include "DepthFrame.h"
#include "config.h"

using namespace tri::core;

void DepthFrame::setup(int width, int height) {
    Frame::setup(width, height);

    glGenTextures(1, &depth); 
    glBindTexture(GL_TEXTURE_2D_ARRAY, depth);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT32F, config::SHADOW_RESOLUTION.w, config::SHADOW_RESOLUTION.h, shadowCascadeLevels, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    static constexpr float borderColor[] = {1.f, 1.f, 1.f, 1.f};
    glTexParameterfv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, borderColor);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth, 0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
}
void DepthFrame::cleanup(){
    Frame::cleanup();
    glDeleteTextures(1, &depth);
};

GLuint DepthFrame::getDepthMap(){
    return depth;
}

void DepthFrame::setCascadeLevels(int levels){
    shadowCascadeLevels = levels;
    setup(0, 0);
}