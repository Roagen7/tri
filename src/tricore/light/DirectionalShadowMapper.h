#pragma once
#include "ShadowMapper.h"
#include <tricore/light/LightSource.h>
#include <tricore/frame/DepthFrame.h>
#include "config.h"

namespace tri::core::shadow {
    class DirectionalShadowMapper : public ShadowMapper {
    public:
        DirectionalShadowMapper(const std::vector<std::pair<float, float>>& cascadeLayers);
        void setup(int width, int height, unsigned int lightCount) override;
        void populate(std::vector<std::shared_ptr<tri::core::Model>>& models, std::vector<std::shared_ptr<tri::core::DirectionalLight>>& light, tri::core::Camera& camera);
        void attach(const Program& material, std::vector<std::shared_ptr<DirectionalLight>>& lights, Camera& camera);
    private:
        tri::core::DepthFrame frame[tri::config::MAX_DIR_LIGHTS];
        std::vector<std::pair<float, float>> cascadeLayers;
    };
}
