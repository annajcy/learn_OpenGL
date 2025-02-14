#pragma once 

#include "global/core.h"
#include "graphics/node.h"

class Camera : public Node {

public:

    Camera();
    ~Camera();

    glm::mat4 view_matrix() const;
    virtual glm::mat4 projection_matrix() const = 0;
    virtual void adjust_zoom(float delta_zoom) = 0;
    
};