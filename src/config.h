#pragma once

#include <vector>

// TODO: change from static to editable during runtime
namespace tri::config {
    static constexpr auto CAMERA_FAR_PLANE = 300.f;
    static constexpr auto CAMERA_NEAR_PLANE = 0.1f;
    static constexpr struct {
        unsigned int w = 1024;
        unsigned int h = 1024;
    } SHADOW_RESOLUTION;

    static constexpr struct {
        float far = 25.f;
        float near = 0.1f;
    } POINT_LIGHT_SHADOW_PLANES;

    static constexpr auto MAX_POINT_LIGHTS = 10;
    static constexpr auto MAX_DIR_LIGHTS = 3;
    static constexpr auto SKYBOX_SCALE = 10000;
    static constexpr std::initializer_list<std::pair<float, float>> CSM_LAYERS = {{0.1f, 15.f}, {15.f, 20.f}, {20.f, 30.f}, {30.f, 40.f}, {40.f, 50.f}, {50.f, 100.f}, {100.f, 300.f}};
    static constexpr auto CSM_MAX_CASCADES = 16;
}

