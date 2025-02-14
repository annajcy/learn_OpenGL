#include "camera.h"

Camera::Camera() : Node(Node::Node_type::CAMERA) { };
Camera::~Camera() = default;

glm::mat4 Camera::view_matrix() const {
    glm::vec3 center = m_position + front();
    return glm::lookAt(m_position, center, up());
}
