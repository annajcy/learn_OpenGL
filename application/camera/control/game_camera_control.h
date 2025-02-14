#pragma once

#include "camera_control.h"
#include "application/input.h"

class Game_camera_control : public Camera_control
{

public:
    explicit Game_camera_control(const std::shared_ptr<Camera> &camera);
    ~Game_camera_control() override = default;

    void update() override;

};
