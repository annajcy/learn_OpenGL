#pragma once

#include "camera.h"

class Orthographic_camera : public Camera
{
private:

    float m_up_bound{};
    float m_down_bound{};
    float m_left_bound{};
    float m_right_bound{};

    float m_zoom{1.0};

public:

    [[nodiscard]] float up_bound() const;
    [[nodiscard]] float down_bound() const;
    [[nodiscard]] float left_bound() const;
    [[nodiscard]] float right_bound() const;
    
    [[nodiscard]] float zoom() const;

    float& up_bound();
    float& down_bound();
    float& left_bound();
    float& right_bound();
    
    float& zoom();


    Orthographic_camera(float up_bound, float down_bound, float left_bound, float right_bound, float near_bound, float far_bound);
    ~Orthographic_camera();
    glm::mat4 projection_matrix() const override;
    void adjust_zoom(float delta_zoom) override;
};
