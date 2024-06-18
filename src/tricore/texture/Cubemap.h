#pragma once

#include <vector>
#include <string>
#include <glad/glad.h>

namespace tri::core {

    struct CubemapLayout {
        std::string right, left, top, bottom, front, back;
    };

    class Cubemap {
    public:
        Cubemap() = default;

        Cubemap(CubemapLayout layout);

        Cubemap(const Cubemap& other);
        Cubemap& operator=(const Cubemap& other);
        Cubemap(Cubemap&& other) noexcept;
        Cubemap& operator=(Cubemap&& other) noexcept;

        void bind() const;
        void unbind() const;

        ~Cubemap();

    private:
        Cubemap(const std::vector<std::string>& imagePaths);

        GLuint cubemap;
        std::vector<std::string> paths;

        void loadCubemap(const std::vector<std::string>& paths);
    };
}