#pragma once

#include "material.h"

class Depth_material : public Material
{
public:
    Depth_material();
    ~Depth_material() override;

    void update_uniform(const std::shared_ptr<Node>& node, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) override;
};


