#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <cassert>
#include <iostream>

void Texture::loadTexture(const std::string& path){
    glGenTextures(1, &texture);
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &numChannels, 0);
    assert(data);
    assert(numChannels >= 3);

    // make parameters dependent on numChannels
    unsigned int channelMap[5] = {0, 0, 0, GL_RGB, GL_RGBA};
    glTexImage2D(GL_TEXTURE_2D, 0, channelMap[numChannels], width, height, 0, channelMap[numChannels], GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}


Texture::Texture(const std::string& imagePath): path(imagePath) {
    loadTexture(imagePath);
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::unbind() const{
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture(){
    glDeleteTextures(1, &texture);
}

Texture::Texture(const Texture& other): width(other.width), height(other.height), path(other.path) {
    loadTexture(other.path);
}

Texture& Texture::operator=(const Texture& other) {
    if (this == &other) return *this;
    path = other.path;
    width = other.width;
    height = other.height;
    numChannels = other.numChannels;
    path = other.path;
    loadTexture(other.path);
    return *this;

}

Texture::Texture(Texture&& other) noexcept 
    : texture(other.texture), width(other.width), height(other.height), numChannels(other.numChannels), path(other.path) {
    other.texture = 0;
    other.width = 0;
    other.height = 0;
    other.numChannels = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept {
    if (this == &other) return *this;
    texture = other.texture;
    width = other.width;
    height = other.height;
    numChannels = other.numChannels;
    path = other.path;
    other.texture = 0;
    other.width = 0;
    other.height = 0;
    other.numChannels = 0;
    return *this;
}
