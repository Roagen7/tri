#include "ParticleGenerator.h"

/*
    Effect inspired by Fire V1.5 by David Bucciarelli 
    that somehow made its way to the packages on my distribution
*/
namespace tri::extra {
    class FountainParticleGenerator : public ParticleGenerator {
    public:
        FountainParticleGenerator(tri::core::Texture&& texture) : ParticleGenerator(std::move(texture), 500) {}
        void update(float dt) override;

    private:
        int lastUsedParticle{0};
    };
}