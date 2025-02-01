#pragma once

#include "global/core.h"
#include "application/input.h"
#include "application/camera/type/camera.h"

#include <memory>

class Camera_control { 
protected:

    std::shared_ptr<Camera> m_camera{};

public:

    Camera_control(const std::shared_ptr<Camera> &camera) { m_camera = camera; }
    ~Camera_control() = default;

    std::shared_ptr<Camera> camera() { return m_camera; }
    virtual void update() = 0;
};