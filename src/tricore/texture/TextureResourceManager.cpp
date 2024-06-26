#include "TextureResourceManager.h"
      
#include <random>

using namespace tri::core;

texid_t TextureResourceManager::texture(std::string path){
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis(0, std::numeric_limits<uint64_t>::max());
    auto id = dis(gen);

    instance().textureMap[id] = Texture(path, false);
    return id;
}

Texture& TextureResourceManager::texture(texid_t id){
    return instance().textureMap[id];
}

TextureResourceManager& TextureResourceManager::instance(){
    static TextureResourceManager trm;
    return trm;
}

