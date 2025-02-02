#pragma once

#include "camera_control.h"

class Trackball_camera_control : public Camera_control {
public:
    explicit Trackball_camera_control(const std::shared_ptr<Camera> &camera);
    ~Trackball_camera_control() override = default;

    void pitch(float angle);
    void yaw(float angle);
    void update() override;
};
