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

    glm::mat4 parent_tranform = glm::identity<glm::mat4>();

    if (m_parent != nullptr) {
        parent_tranform = m_parent->model_matrix();
    }

    glm::mat4 transform = glm::identity<glm::mat4>();

    transform = glm::scale(transform, m_scale);

    // pitch -> yaw -> roll
    transform = glm::rotate(transform, glm::radians(m_rotation_euler.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(m_rotation_euler.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(m_rotation_euler.z), glm::vec3(0.0f, 0.0f, 1.0f));

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
