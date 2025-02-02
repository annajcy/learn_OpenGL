#pragma once

#include "camera_control.h"
#include "application/input.h"
#include <memory>

class Game_camera_control : public Camera_control
{
private:
    

public:
    explicit Game_camera_control(const std::shared_ptr<Camera> &camera);
    ~Game_camera_control() override = default;

    void update() override;

};
