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

void Node::look_at_point(const glm::vec3& target_point) {
    glm::vec3 direction = glm::normalize(target_point - m_position);
    look_at_direction(direction);
}

void Node::look_at_direction(const glm::vec3& target_direction) {
    glm::vec3 direction = glm::normalize(target_direction);
    glm::vec3 current_front = front();

    // 避免方向向量过小，防止除零错误
    if (glm::length(direction) < 1e-6f) {
        return;
    }

    // 检查当前前向量和目标方向是否几乎平行
    if (glm::length(glm::cross(current_front, direction)) < 1e-6f) {
        // 如果它们是相反方向，则绕 up 轴旋转 180 度
        if (glm::dot(current_front, direction) < 0) {
            m_rotation = glm::rotate(m_rotation, glm::radians(180.0f), up());
        }
        return;
    }

    // 计算旋转四元数：从 current_front 旋转到 direction
    glm::quat rotation_quat = glm::rotation(current_front, direction);

    // 更新 m_rotation
    m_rotation = rotation_quat * m_rotation;
}

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

Node Node::world_node() const {
    Node world_node(type());  // Create a new node with the same type

    // Start with the current node's local transformations
    glm::vec3 world_position = m_position;
    glm::quat world_rotation = m_rotation;
    glm::vec3 world_scale = m_scale;

    // Traverse up the parent hierarchy to accumulate transformations
    std::shared_ptr<Node> current_parent = m_parent;
    while (current_parent) {
        
        world_position = current_parent->rotation() * (world_position * current_parent->scale()) + current_parent->position();
        world_rotation = current_parent->rotation() * world_rotation;
        world_scale *= current_parent->scale();

        current_parent = current_parent->parent();
    }

    // Assign the computed world-space transformations
    world_node.position() = world_position;
    world_node.rotation() = world_rotation;
    world_node.scale() = world_scale;

    return world_node;
}

