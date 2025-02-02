#pragma once 

#include "global/core.h"

class Camera {

protected:
    glm::vec3 m_position{0.0f, 0.0f, 0.0f};
    glm::vec3 m_up{0.0f, 1.0f, 0.0f};
    glm::vec3 m_right{1.0f, 0.0f, 0.0f};
    float m_scale{1.0};

public:

    Camera(const glm::vec3 &position, const glm::vec3 &up, const glm::vec3 &right);
    ~Camera();

    [[nodiscard]] glm::vec3 position() const;
    [[nodiscard]] glm::vec3 up() const;
    [[nodiscard]] glm::vec3 down() const;
    [[nodiscard]] glm::vec3 right() const;
    [[nodiscard]] glm::vec3 left() const;
    [[nodiscard]] glm::vec3 front() const;
    [[nodiscard]] glm::vec3 back() const;

    [[nodiscard]] glm::vec3& position();
    [[nodiscard]] glm::vec3& up();
    [[nodiscard]] glm::vec3& right();

    glm::mat4 get_view_matrix() const;
    virtual glm::mat4 get_projection_matrix() const = 0;
    virtual void adjust_scale(float delta_scale) = 0;
    void translate(const glm::vec3 &direction, float distance);
    void translate(const glm::vec3 &translation);
    void rotate(float angle, const glm::vec3& axis);
    void pitch(float angle);
    void yaw(float angle);
};