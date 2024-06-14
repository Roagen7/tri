#include "Cubemap.h"

#include <stb_image.h>
#include <cassert>
#include <iostream>

Cubemap::Cubemap(CubemapLayout layout): Cubemap(std::vector({
    layout.right,
    layout.left,
    layout.top,
    layout.bottom,
    layout.front,
    layout.back
})){

}


void Cubemap::loadCubemap(const std::vector<std::string>& imagePaths) {
    glGenTextures(1, &cubemap);
    bind();

    int width, height, nrChannels;
    unsigned int channelMap[5] = {0, 0, 0, GL_RGB, GL_RGBA};
    int i = 0;
    for(const auto& path : imagePaths){
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        assert(data);
        assert(nrChannels >= 3);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, channelMap[nrChannels], width, height, 0, channelMap[nrChannels], GL_UNSIGNED_BYTE, data);
        
        stbi_image_free(data);
        i++;
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

Cubemap::Cubemap(const std::vector<std::string>& imagePaths) : paths(imagePaths){
    loadCubemap(imagePaths);
}

void Cubemap::bind() const {
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
}

void Cubemap::unbind() const{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

Cubemap::~Cubemap(){
    glDeleteTextures(1, &cubemap);
}

Cubemap::Cubemap(const Cubemap& other): paths(other.paths) {
    loadCubemap(other.paths);
}

Cubemap& Cubemap::operator=(const Cubemap& other) {
    if (this == &other) return *this;
    paths = other.paths;
    loadCubemap(other.paths);
    return *this;
}

Cubemap::Cubemap(Cubemap&& other) noexcept 
    : cubemap(other.cubemap), paths(other.paths) {
    other.cubemap = 0;
    other.paths = {};
}

Cubemap& Cubemap::operator=(Cubemap&& other) noexcept {
    if (this == &other) return *this;
    cubemap = other.cubemap;
    paths = other.paths;
    other.cubemap = 0;
    other.paths = {};
    return *this;
}
