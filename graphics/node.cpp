#include "node.h"

Node::Node(Node_type type) : m_type(type) {}

glm::vec3& Node::rotation_euler() { return m_rotation_euler; }
glm::vec3& Node::scale() { return m_scale; }
glm::vec3& Node::position() { return m_position; }

Node::Node_type Node::type() const { return m_type; }
glm::vec3 Node::position() const { return m_position; }
glm::vec3 Node::rotation_euler() const { return m_rotation_euler; }
glm::vec3 Node::scale() const { return m_scale; }

glm::mat4 Node::model_matrix() const {
    glm::mat4 transform = glm::identity<glm::mat4>();

    transform = glm::scale(transform, m_scale);

    // pitch -> yaw -> roll
    transform = glm::rotate(transform, glm::radians(m_rotation_euler.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(m_rotation_euler.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(m_rotation_euler.z), glm::vec3(0.0f, 0.0f, 1.0f));

    transform = glm::translate(glm::identity<glm::mat4>(), m_position) * transform;

    return transform;
}
