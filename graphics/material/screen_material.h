#pragma once

#include "material.h"
#include "graphics/texture.h"

class Screen_material : public Material
{
public:
    std::shared_ptr<Texture> m_screen_texture{};

    Screen_material();
    ~Screen_material() override;

    void update_uniform(
        const std::shared_ptr<Node>& node, 
        const std::shared_ptr<Camera>& camera, 
        const std::shared_ptr<Light_setting>& light_setting) override;

    void before_geometry_draw() override;
    void after_geometry_draw() override;
    void load_from_assimp(const aiScene* scene, const aiMaterial* assimp_material) override;

    std::shared_ptr<Texture>& screen_texture();
};


