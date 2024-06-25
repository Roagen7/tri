#pragma once
#include <glad/glad.h>
#include <tricore/light/LightSource.h>
#include <vector>
#include <tricore/model/Model.h>


namespace tri::core::shadow {
    class ShadowMapper {
    public:
        virtual void setup(int width, int height, unsigned int lightCount) = 0;

        const GLuint operator[](size_t index) const {
            return shadowMaps[index];
        }

        GLuint operator[](size_t index) {
            return shadowMaps[index];
        }

    protected:
        void cast(std::vector<std::shared_ptr<tri::core::SpatialIfc>>& spatials) {
            glEnable(GL_DEPTH_TEST);
            glClear(GL_DEPTH_BUFFER_BIT);
            glDepthFunc(GL_LESS);
            // TODO: transparency might not work
            for(const auto& model : spatials){
                if(!model->castsShadow()) continue;
                model->draw(*program);
            }
        }
    std::unique_ptr<tri::core::Program> program;

    private:
        GLuint* shadowMaps;
      
    };
}
