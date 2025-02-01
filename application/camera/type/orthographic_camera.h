#pragma once

#include "camera.h"

class Orthographic_camera : public Camera
{
private:

    float m_up_bound{};
    float m_down_bound{};
    float m_left_bound{};
    float m_right_bound{};
    float m_near_bound{};
    float m_far_bound{};

public:

    [[nodiscard]] float up_bound() const;
    [[nodiscard]] float down_bound() const;
    [[nodiscard]] float left_bound() const;
    [[nodiscard]] float right_bound() const;
    [[nodiscard]] float near_bound() const;
    [[nodiscard]] float far_bound() const;

    [[nodiscard]] float& up_bound();
    [[nodiscard]] float& down_bound();
    [[nodiscard]] float& left_bound();
    [[nodiscard]] float& right_bound();
    [[nodiscard]] float& near_bound();
    [[nodiscard]] float& far_bound();

    Orthographic_camera(float up_bound, float down_bound, float left_bound, float right_bound, float near_bound, float far_bound, const glm::vec3 &position, const glm::vec3 &up, const glm::vec3 &right);
    ~Orthographic_camera();
    glm::mat4 get_projection_matrix() const override;
};
