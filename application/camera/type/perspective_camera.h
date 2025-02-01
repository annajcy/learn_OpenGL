#pragma once

#include "camera.h"

class Perspective_camera : public Camera
{
private:

    float m_fov{};
    float m_aspect{};
    float m_near_bound{};
    float m_far_bound{};

public:

    float fov() const;
    float aspect() const;
    float near_bound() const;
    float far_bound() const;

    float& fov();
    float& aspect();
    float& near_bound();
    float& far_bound();

    Perspective_camera(float fov, float aspect, float near_bound, float far_bound, const glm::vec3 &position, const glm::vec3 &up, const glm::vec3 &right);
    ~Perspective_camera();
    glm::mat4 get_projection_matrix() const override;
};
