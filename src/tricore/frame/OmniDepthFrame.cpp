#include "OmniDepthFrame.h"
#include "config.h"

using namespace tri::core;
        
GLuint OmniDepthFrame::getDepthMap(){
    return depth;
}
        
void OmniDepthFrame::setup(int width, int height) {
    Frame::setup(width, height);

    glGenTextures(1, &depth); 
    glBindTexture(GL_TEXTURE_CUBE_MAP, depth);

    for(auto i = 0u; i < 6; i++){
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, config::SHADOW_RESOLUTION.w, config::SHADOW_RESOLUTION.h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);    
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  
    }
    
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
}

void OmniDepthFrame::cleanup() {
    Frame::cleanup();
    glDeleteTextures(1, &depth);
}
