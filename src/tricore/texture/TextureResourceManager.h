#pragma once
#include <cstdint>
#include <map>
#include "Texture.h"

namespace tri::core {

    using texid_t = uint64_t;

    class TextureResourceManager {

    public:
        static texid_t texture(std::string path);
        static Texture& texture(texid_t id);

    private:
        TextureResourceManager(){};
        static TextureResourceManager& instance();

        std::map<texid_t, Texture> textureMap;

    };


}

