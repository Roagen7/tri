#include "FountainParticleGenerator.h"

using namespace tri::core;
using namespace tri::extra;


int findUnusedParticle(std::vector<Particle>& particles, int& lastUsedParticle){
    for (int i = lastUsedParticle; i<particles.size(); i++){
            if (particles[i].life < 0){
                lastUsedParticle = i;
                return i;
            }
    }

	for (int i = 0; i<particles.size(); i++){
		if (particles[i].life < 0){
			lastUsedParticle = i;
			return i;
		}
	}
	return 0;
}

float randFloat(){
    return std::rand() / static_cast<float>(RAND_MAX);
}

Particle resurrectParticle(){
    const float radius = 3.0;
    const float height = 10.0;
    const float initialVel = 1.0;
    float angle = randFloat() * 2 * M_PI;

    glm::vec3 pos = {radius * cos(angle), 0, radius * sin(angle)};
    glm::vec3 dir = initialVel * (glm::vec3{0, 1, 0} * height - pos);


    return {
        .velocity = dir,
        .position =  pos,
        .color = {1, 1, 1},
        .life = 3 * randFloat()
    };
}


void FountainParticleGenerator::update(float dt) {
    const float gravity = 9.81f * 0.01;


     for(auto& particle : particles){
        if(particle.life > 0.f) continue;
        particle = resurrectParticle();
    }

    for(auto& particle : particles){
        if(particle.life < 0.f) continue;
        particle.position += particle.velocity * dt;
        particle.life -= std::rand() / static_cast<float>(RAND_MAX) * dt;
        particle.velocity -= gravity * glm::vec3{0, 1, 0};
    }
}