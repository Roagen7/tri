#pragma once
#include <glad/glad.h>
#include <vector>
#include <string>

static constexpr auto LIB_PATH_FS = "lib/fragment";
static constexpr auto LIB_PATH_VS = "lib/vertex";
static constexpr auto LIB_PATH_DECLARATIONS = "lib/declarations.glsl";

static constexpr auto FILES_FS = {
    "test.glsl",
    "pointLight.glsl",
    "dirLight.glsl",
    "parallaxMapping.glsl",
    "shadowCalculation.glsl",
    "omniShadowCalculation.glsl"
};

static constexpr auto FILES_VS = {
    "test.glsl"
};

namespace tri::core {
    /*
        lazy-loaded library of generic glsl functions
    */
    class ShaderLib {

    public:
        ~ShaderLib();

        static std::string include(const std::string& source);
        static void attach(GLint program);

    private:

        std::string include_(const std::string& source);

        static ShaderLib& instance();
        ShaderLib();

        std::vector<GLint> fragmentShaders;
        std::vector<GLint> vertexShaders;
        std::string declarations;
    };
}