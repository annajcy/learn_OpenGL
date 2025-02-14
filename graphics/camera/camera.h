#pragma once 

#include "global/core.h"
#include "graphics/node.h"

class Camera : public Node {

public:

    Camera(float near_bound, float far_bound);
    ~Camera();

    float m_near_bound{};
    float m_far_bound{};

    float& near_bound();
    float& far_bound();

    [[nodiscard]] float near_bound() const;
    [[nodiscard]] float far_bound() const;

    glm::mat4 view_matrix() const;
    virtual glm::mat4 projection_matrix() const = 0;
    virtual void adjust_zoom(float delta_zoom) = 0;
    
};