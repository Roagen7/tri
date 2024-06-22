#pragma once


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
}

