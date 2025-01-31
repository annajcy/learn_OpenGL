#include "camera.h"

Camera::Camera() = default;
Camera::~Camera() = default;

[[nodiscard]] glm::vec3 Camera::get_position() const { return m_position; }
[[nodiscard]] glm::vec3 Camera::get_up() const { return m_up; }
[[nodiscard]] glm::vec3 Camera::get_down() const { return -m_up; }
[[nodiscard]] glm::vec3 Camera::get_right() const { return m_right; }
[[nodiscard]] glm::vec3 Camera::get_left() const { return -m_right; }
[[nodiscard]] glm::vec3 Camera::get_front() const { return glm::cross(m_up, m_right); }
[[nodiscard]] glm::vec3 Camera::get_back() const { return -get_front(); }

glm::mat4 Camera::get_view_matrix() const {
    glm::vec3 front = get_front();
    glm::vec3 center = m_position + front;
    return glm::lookAt(m_position, center, m_up);
}

glm::mat4 Camera::get_projection_matrix() const {
    return glm::identity<glm::mat4>();
}

void Camera::translate(const glm::vec3 &translation) {
    m_position += translation;
}

void Camera::pitch(float angle) {
    glm::mat4 rotation = glm::rotate(glm::identity<glm::mat4>(), angle, m_right);
    m_up = glm::vec3(rotation * glm::vec4(m_up, 1.0f));
}

void Camera::yaw(float angle) {
    glm::mat4 rotation = glm::rotate(glm::identity<glm::mat4>(), angle, m_up);
    m_right = glm::vec3(rotation * glm::vec4(m_right, 1.0f));
}
