#pragma once 

#include "global/core.h"

class Camera {

protected:
    glm::vec3 m_position{0.0f, 0.0f, 0.0f};
    glm::vec3 m_up{0.0f, 1.0f, 0.0f};
    glm::vec3 m_right{1.0f, 0.0f, 0.0f};

public:

    Camera();
    ~Camera();

    [[nodiscard]] glm::vec3 get_position() const;
    [[nodiscard]] glm::vec3 get_up() const;
    [[nodiscard]] glm::vec3 get_down() const;
    [[nodiscard]] glm::vec3 get_right() const;
    [[nodiscard]] glm::vec3 get_left() const;
    [[nodiscard]] glm::vec3 get_front() const;
    [[nodiscard]] glm::vec3 get_back() const;

    glm::mat4 get_view_matrix() const;
    virtual glm::mat4 get_projection_matrix() const;

    void translate(const glm::vec3 &translation);
    void pitch(float angle);
    void yaw(float angle);
    
};