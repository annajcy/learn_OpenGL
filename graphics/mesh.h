#pragma once

#include "global/core.h"

#include "graphics/geometry.h"
#include "graphics/material/material.h"
#include "graphics/node.h"

#include <memory>

class Mesh : public Node
{   
private:
    std::shared_ptr<Geometry> m_geometry{};
    std::shared_ptr<Material> m_material{};

public:
    Mesh(const std::shared_ptr<Geometry>& geometry, const std::shared_ptr<Material>& material);
    ~Mesh() override = default;

    std::shared_ptr<Geometry>& geometry();
    std::shared_ptr<Material>& material();
};
