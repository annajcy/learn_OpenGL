#pragma once

#include "material.h"

class Edge_material : public Material
{
public:
    Edge_material();
    ~Edge_material() override = default;

    void update_uniform(const std::shared_ptr<Node>& node, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) override;
};