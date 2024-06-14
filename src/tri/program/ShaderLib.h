#pragma once
#include <glad/glad.h>
#include <vector>

static constexpr auto LIB_PATH_FS = "lib/fragment";
static constexpr auto LIB_PATH_VS = "lib/vertex";

static constexpr auto FILES_FS = {
    "test.glsl"
};

static constexpr auto FILES_VS = {
    "test.glsl"
};


/*
    lazy-loaded library of generic glsl functions
*/
class ShaderLib {

public:
    ~ShaderLib();

    static void attach(GLint program);

private:
    ShaderLib();

    std::vector<GLint> fragmentShaders;
    std::vector<GLint> vertexShaders;
};
