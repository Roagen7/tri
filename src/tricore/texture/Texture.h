#pragma once

#include <string>
#include <glad/glad.h>

namespace tri::core {
    class Texture {
    public:
        Texture() = default;
        Texture(const std::string& imagePath, bool doCleanup=true);

        Texture(const Texture& other);
        Texture& operator=(const Texture& other);
        Texture(Texture&& other) noexcept;
        Texture& operator=(Texture&& other) noexcept;

        void bind() const;
        void unbind() const;

        void cleanup();

        ~Texture();

    private:
        GLuint texture{};
        std::string path;
        int width, height, numChannels;
        bool doCleanup;

        void loadTexture(const std::string& path);
    };
}