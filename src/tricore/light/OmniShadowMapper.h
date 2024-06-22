#pragma once
#include "ShadowMapper.h"
#include <tricore/light/LightSource.h>
#include <tricore/frame/OmniDepthFrame.h>

namespace tri::core::shadow {
    class OmniShadowMapper : public ShadowMapper {
    public:
        OmniShadowMapper();
        void setup(int width, int height, unsigned int lightCount) override;
        void populate(std::vector<std::shared_ptr<tri::core::Model>>& models, std::vector<std::shared_ptr<tri::core::PointLight>>& light);
        void attach(const Program& material, std::vector<std::shared_ptr<PointLight>>& lights);
    private:
        tri::core::OmniDepthFrame frame[tri::config::MAX_POINT_LIGHTS];
    };
}
