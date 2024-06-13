#pragma once

#include <string>
#include <glad/glad.h>

class Texture {
public:
    Texture() = default;
    Texture(const std::string& imagePath);

    Texture(const Texture& other);
    Texture& operator=(const Texture& other);
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    void bind() const;
    void unbind() const;

    ~Texture();

private:
    GLuint texture;
    std::string path;
    int width, height, numChannels;

    void loadTexture(const std::string& path);
};