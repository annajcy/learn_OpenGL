#pragma once

#include "global/core.h"

class Node : public std::enable_shared_from_this<Node>
{
public:
    enum class Node_type {
        OBJECT,
        MESH,
        INSTANCED_MESH,
        SCENE,
        LIGHT,
    };

protected:
    Node_type m_type{};
    glm::vec3 m_position = glm::zero<glm::vec3>();
    glm::vec3 m_scale = glm::one<glm::vec3>();
    glm::vec3 m_rotation_euler = glm::zero<glm::vec3>();

    std::vector<std::shared_ptr<Node>> m_children{};
    std::shared_ptr<Node> m_parent{};

public:
    explicit Node(Node_type type = Node_type::OBJECT);
    virtual ~Node() = default;

    glm::vec3& rotation_euler();
    glm::vec3& scale();
    glm::vec3& position();

    std::shared_ptr<Node>& parent();
    std::vector<std::shared_ptr<Node>>& children();

    void add_child(const std::shared_ptr<Node>& node);
    void erase_child(const std::shared_ptr<Node> &node);
    void clear_children();
    [[nodiscard]] Node_type type() const;
    [[nodiscard]] glm::vec3 position() const;
    [[nodiscard]] glm::vec3 rotation_euler() const;
    [[nodiscard]] glm::vec3 scale() const;

    [[nodiscard]] glm::mat4 model_matrix() const;
};
