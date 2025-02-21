#pragma once

#include "global/core.h"
#include "utils/math_utils.h"

class Node : public std::enable_shared_from_this<Node>
{
public:
    enum class Node_type {
        OBJECT,
        MESH,
        INSTANCED_MESH,
        SCENE,
        LIGHT,
        CAMERA
    };

protected:
    Node_type m_type{};

    glm::vec3 m_position = glm::zero<glm::vec3>();
    glm::vec3 m_scale = glm::one<glm::vec3>();
    glm::quat m_rotation = glm::identity<glm::quat>();

    std::vector<std::shared_ptr<Node>> m_children{};
    std::shared_ptr<Node> m_parent{};

public:
    explicit Node(Node_type type = Node_type::OBJECT);
    virtual ~Node() = default;

    std::shared_ptr<Node>& parent();
    std::vector<std::shared_ptr<Node>>& children();

    void add_child(const std::shared_ptr<Node>& node);
    void erase_child(const std::shared_ptr<Node> &node);
    void clear_children();

    [[nodiscard]] Node_type type() const;

    [[nodiscard]] glm::vec3 position() const;
    [[nodiscard]] glm::quat rotation() const;
    [[nodiscard]] glm::vec3 rotation_euler() const;
    [[nodiscard]] glm::vec3 scale() const;

    [[nodiscard]] glm::vec3 up() const;
    [[nodiscard]] glm::vec3 down() const;
    [[nodiscard]] glm::vec3 right() const;
    [[nodiscard]] glm::vec3 left() const;
    [[nodiscard]] glm::vec3 front() const;
    [[nodiscard]] glm::vec3 back() const;

    glm::quat& rotation();
    glm::vec3& scale();
    glm::vec3& position();

    [[nodiscard]] glm::mat4 model_matrix() const;

    Node world_node() const;

    void look_at_direction(const glm::vec3& target_direction);
    void look_at_point(const glm::vec3& target_point);
    void translate(const glm::vec3 &direction, float distance);
    void rotate(float angle, const glm::vec3& axis);
    void pitch(float angle);
    void yaw(float angle);
    void roll(float angle);
};
