#include "perspective_camera.h"

Perspective_camera::~Perspective_camera() = default;
Perspective_camera::Perspective_camera(float fov, float aspect, float near_bound, float far_bound) : 
Camera(near_bound, far_bound) , m_fov(fov), m_aspect(aspect) { }

float Perspective_camera::fov() const { return m_fov; }
float Perspective_camera::aspect() const { return m_aspect; }

float& Perspective_camera::fov() { return m_fov; }
float& Perspective_camera::aspect() { return m_aspect; }


void Perspective_camera::adjust_zoom(float delta_zoom) { translate(front(), delta_zoom); }

glm::mat4 Perspective_camera::projection_matrix() const {
    return glm::perspective(glm::radians(m_fov), m_aspect, m_near_bound, m_far_bound);
}

