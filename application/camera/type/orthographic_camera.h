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

    float m_scale{1.0};

public:

    [[nodiscard]] float up_bound() const;
    [[nodiscard]] float down_bound() const;
    [[nodiscard]] float left_bound() const;
    [[nodiscard]] float right_bound() const;
    [[nodiscard]] float near_bound() const;
    [[nodiscard]] float far_bound() const;
    [[nodiscard]] float scale() const;

    float& up_bound();
    float& down_bound();
    float& left_bound();
    float& right_bound();
    float& near_bound();
    float& far_bound();
    float& scale();


    Orthographic_camera(float up_bound, float down_bound, float left_bound, float right_bound, float near_bound, float far_bound, const glm::vec3 &position, const glm::vec3 &up, const glm::vec3 &right);
    ~Orthographic_camera();
    glm::mat4 projection_matrix() const override;
    void adjust_scale(float delta_scale) override;
};
