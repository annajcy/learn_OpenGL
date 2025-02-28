#pragma once

#include "material.h"
#include "graphics/texture.h"

class Cube_map_material : public Material
{
private:
    std::shared_ptr<Texture> m_cube_map;
public:
    std::shared_ptr<Texture>& cube_map();

    Cube_map_material();
    ~Cube_map_material() override;

    void update_uniform(const std::shared_ptr<Node>& node, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) override;
    void before_geometry_draw() override;
    void after_geometry_draw() override;
};


