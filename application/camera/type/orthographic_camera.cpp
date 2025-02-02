#include "orthographic_camera.h"

Orthographic_camera::Orthographic_camera(float up_bound, float down_bound, float left_bound, float right_bound, float near_bound, float far_bound, float scale, const glm::vec3 &position, const glm::vec3 &up, const glm::vec3 &right) : Camera(position, up, right) {
    m_up_bound = up_bound;
    m_down_bound = down_bound;
    m_left_bound = left_bound;
    m_right_bound = right_bound;
    m_near_bound = near_bound;
    m_far_bound = far_bound;
    m_scale = scale;
}

Orthographic_camera::~Orthographic_camera() = default;

float Orthographic_camera::up_bound() const {
    return m_up_bound;
}

float Orthographic_camera::down_bound() const {
    return m_down_bound;
}

float Orthographic_camera::left_bound() const {
    return m_left_bound;
}

float Orthographic_camera::right_bound() const {
    return m_right_bound;
}

float Orthographic_camera::near_bound() const {
    return m_near_bound;
}

float Orthographic_camera::far_bound() const {
    return m_far_bound;
}

float& Orthographic_camera::up_bound() {
    return m_up_bound;
}

float& Orthographic_camera::down_bound() {
    return m_down_bound;
}

float& Orthographic_camera::left_bound() {
    return m_left_bound;
}

float& Orthographic_camera::right_bound() {
    return m_right_bound;
}

float& Orthographic_camera::near_bound() {
    return m_near_bound;
}

float& Orthographic_camera::far_bound() {
    return m_far_bound;
}

glm::mat4 Orthographic_camera::get_projection_matrix() const {
    return glm::ortho(m_left_bound * m_scale, m_right_bound * m_scale, m_down_bound * m_scale, m_up_bound * m_scale, m_near_bound, m_far_bound );
}

void Orthographic_camera::adjust_scale(float delta_scale) {
    m_scale += delta_scale;
}