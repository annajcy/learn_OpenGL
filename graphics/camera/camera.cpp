#include "camera.h"

Camera::Camera(float near_bound, float far_bound) : 
Node(Node::Node_type::CAMERA), m_near_bound(near_bound), m_far_bound(far_bound) { };

Camera::~Camera() = default;

glm::mat4 Camera::view_matrix() const {
    glm::vec3 center = m_position + front();
    return glm::lookAt(m_position, center, up());
}

float Camera::near_bound() const { return m_near_bound; }
float Camera::far_bound() const { return m_far_bound; }

float& Camera::near_bound() { return m_near_bound; }
float& Camera::far_bound() { return m_far_bound; }