#include "node.h"

Node::Node(Node_type type) : m_type(type) {}
Node::Node_type Node::type() const { return m_type; }

glm::mat4 Node::model_matrix() const {

    glm::mat4 parent_tranform = glm::identity<glm::mat4>();

    if (m_parent != nullptr) {
        parent_tranform = m_parent->model_matrix();
    }

    glm::mat4 transform = glm::identity<glm::mat4>();

    transform = glm::scale(transform, m_scale);
    transform *= glm::mat4_cast(m_rotation);
    transform = glm::translate(glm::identity<glm::mat4>(), m_position) * transform;

    return parent_tranform * transform;
}

void Node::clear_children() {
    for (auto &child : m_children) {
        child->parent() = nullptr;
    }

    m_children.clear();
}

void Node::erase_child(const std::shared_ptr<Node> &node) {
    auto it = std::find_if(m_children.begin(), m_children.end(), 
    [&node](const std::shared_ptr<Node>& child) {
        return child.get() == node.get(); // Compare the shared_ptr directly
    });

    // If the node is found, remove it from the vector
    if (it != m_children.end()) {
        // Set the parent of the node to nullptr
        (*it)->parent() = nullptr;
        
        // Erase the node from the children vector
        m_children.erase(it);
    }
}

void Node::add_child(const std::shared_ptr<Node>& node) {
    m_children.push_back(node);
    node->parent() = shared_from_this();
}

std::shared_ptr<Node>& Node::parent() {
    return m_parent;
}

std::vector<std::shared_ptr<Node>>& Node::children() {
    return m_children;
}

//Yaw-Pitch-Roll order
glm::vec3 Node::rotation_euler() const { return glm::degrees(glm::eulerAngles(m_rotation)); }

glm::vec3 Node::position() const { return m_position; }
glm::vec3 Node::scale() const { return m_scale; }
glm::quat Node::rotation() const { return m_rotation; }

glm::vec3& Node::position() { return m_position; }
glm::vec3& Node::scale() { return m_scale; }
glm::quat& Node::rotation() { return m_rotation; }

glm::vec3 Node::up() const { return glm::rotate(m_rotation, glm::vec3(0.0f, 1.0f, 0.0f)); }
glm::vec3 Node::down() const { return -up(); }
glm::vec3 Node::right() const { return glm::rotate(m_rotation, glm::vec3(1.0f, 0.0f, 0.0f)); }
glm::vec3 Node::left() const { return -right(); }
glm::vec3 Node::front() const { return glm::cross(right(), up()); }
glm::vec3 Node::back() const { return -front(); }

void Node::translate(const glm::vec3 &direction, float distance) {
    m_position += direction * distance;
}

void Node::rotate(float angle, const glm::vec3& axis) {
    glm::quat rotation = glm::angleAxis(glm::radians(angle), axis);  // Convert angle-axis to quaternion
    m_rotation = rotation * m_rotation;  // Apply the rotation to the current rotation
}

void Node::pitch(float angle) {
    rotate(angle, up());
}

void Node::yaw(float angle) {
    rotate(angle, right());
}

void Node::roll(float angle) {
    rotate(angle, front());
}
