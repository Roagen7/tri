#include "DepthFrame.h"
#include "config.h"

using namespace tri::core;

void DepthFrame::setup(int width, int height) {
    Frame::setup(width, height);

    glGenTextures(1, &depth); 
    glBindTexture(GL_TEXTURE_2D, depth);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, config::SHADOW_RESOLUTION.w, config::SHADOW_RESOLUTION.h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth, 0);
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
