#pragma once


// TODO: change from static to editable during runtime
namespace tri::config {
    static constexpr auto CAMERA_FAR_PLANE = 300.f;
    static constexpr auto CAMERA_NEAR_PLANE = 0.1f;
    static constexpr struct {
        unsigned int w = 1024;
        unsigned int h = 1024;
    } SHADOW_RESOLUTION;
}

