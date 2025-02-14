#pragma once

#include "camera.h"

class Perspective_camera : public Camera
{
private:

    float m_fov{};
    float m_aspect{};

public:

    [[nodiscard]] float fov() const;
    [[nodiscard]] float aspect() const;

    float& fov();
    float& aspect();

    Perspective_camera(float fov, float aspect, float near_bound, float far_bound);
    ~Perspective_camera();
    glm::mat4 projection_matrix() const override;
    void adjust_zoom(float delta_zoom) override;
};
