#pragma once

#include "../Camera.h"

#include "SpatialIfc.h"
#include "Mesh.h"
#include <tricore/program/materials/DefaultMaterial.h>
#include <tricore/program/materials/LightMaterial.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <map>

namespace tri::core {
    class Model : public SpatialIfc {
    public:
        Model() {
            setMaterial<materials::DefaultMaterial>();
        };

        Model& setRotationXYZ(glm::vec3 rotation);
        Model& setScaleXYZ(glm::vec3 scale);
        Model& setScale(glm::vec3 scale);
        Model& setTranslation(glm::vec3 translation);
        glm::vec3 getWorldPosition() const override;

        Model& enableTransparency();
        
        Model& setMesh(const Mesh& mesh);
        Model& setBorder(glm::vec3 color, float thickness);
        Model& removeBorder();

        Model& enableCastShadow();
        Model& enableReceiveShadow();

        bool castsShadow() override;

        bool hasTransparency() override;

        const Program& getMaterial() override;

        template<typename T, typename... A>
        Model& setMaterial(A&&... args){
            this->material = std::make_unique<T>(std::forward<A>(args)...);
            return *this;
        }

        Model& setMaterial(std::unique_ptr<Program>&& material);

        void draw(const Camera& camera) override;
        void draw(const Camera&, Program& material);
        void draw(glm::mat4 projection, Program& material);
        void draw(Program& material) override;

    protected:
        Mesh mesh;

    private:
    
        void drawBorder(const Camera& camera);
        void borderPrehook();
        // TODO: change to quaternion
       
        bool transparency{false}, castShadow{false}, receiveShadow{false};
        std::unique_ptr<Program> material{};

        struct {
            std::unique_ptr<materials::LightMaterial> material{};
            float thickness;
        } border;
        
    };
}