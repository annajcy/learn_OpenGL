#include "camera.h"

Camera::Camera(const glm::vec3 &position, const glm::vec3 &up, const glm::vec3 &right) {
    m_position = position;
    m_up = glm::normalize(up);
    m_right = glm::normalize(right);
};

Camera::~Camera() = default;

[[nodiscard]] glm::vec3 Camera::position() const { return m_position; }
[[nodiscard]] glm::vec3 Camera::up() const { return m_up; }
[[nodiscard]] glm::vec3 Camera::down() const { return -m_up; }
[[nodiscard]] glm::vec3 Camera::right() const { return m_right; }
[[nodiscard]] glm::vec3 Camera::left() const { return -m_right; }
[[nodiscard]] glm::vec3 Camera::front() const { return glm::cross(m_right, m_up); }
[[nodiscard]] glm::vec3 Camera::back() const { return -front(); }


[[nodiscard]] glm::vec3& Camera::position() { return m_position; }
[[nodiscard]] glm::vec3& Camera::up() { return m_up; }
[[nodiscard]] glm::vec3& Camera::right() { return m_right; }


glm::mat4 Camera::get_view_matrix() const {
    glm::vec3 center = m_position + front();
    return glm::lookAt(m_position, center, m_up);
}

void Camera::translate(const glm::vec3 &translation) {
    m_position += translation;
}

void Camera::translate(const glm::vec3 &direction, float distance) {
    m_position += direction * distance;
}

void Camera::rotate(float angle, const glm::vec3& axis) {
    glm::mat4 rotation = glm::rotate(glm::identity<glm::mat4>(), glm::radians(angle), axis);
    m_position = glm::vec3(rotation * glm::vec4(m_position, 1.0f));
}

void Camera::pitch(float angle) {
    glm::mat4 rotation = glm::rotate(glm::identity<glm::mat4>(), glm::radians(angle), m_right);
    m_up = glm::vec3(rotation * glm::vec4(m_up, 0.0f));
}

void Camera::yaw(float angle) {
    glm::mat4 rotation = glm::rotate(glm::identity<glm::mat4>(), glm::radians(angle), m_up);
    m_right = glm::vec3(rotation * glm::vec4(m_right, 0.0f));
}
