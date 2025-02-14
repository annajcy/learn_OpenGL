#pragma once

#include "global/core.h"

#include "application/input.h"
#include "graphics/camera/camera.h"

class Camera_control { 
protected:
    std::shared_ptr<Camera> m_camera;

    float m_pitch_sensitivity {0.1f};
    float m_yaw_sensitivity {0.1f};
    float m_tranlate_sensitivity {0.001f};
    float m_scale_sensitivity {0.01f};

public:
    explicit Camera_control(const std::shared_ptr<Camera> &camera);
    virtual ~Camera_control() = default;

    std::shared_ptr<Camera> camera();

    virtual void update() = 0;

    [[nodiscard]] float get_pitch_sensitivity() const;
    [[nodiscard]] float get_yaw_sensitivity() const;
    [[nodiscard]] float get_translate_sensitivity() const;
    [[nodiscard]] float get_scale_sensitivity() const;

    float& pitch_sensitivity();
    float& yaw_sensitivity();
    float& translate_sensitivity();
    float& scale_sensitivity();
};
