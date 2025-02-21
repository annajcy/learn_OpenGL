#pragma once

#include "material.h"
#include "phong_material.h"
#include "graphics/texture.h"

class Phong_specular_mask_material : public Phong_material
{
private:
    std::shared_ptr<Texture> m_specular_mask_texture{};
public:
    Phong_specular_mask_material();
    ~Phong_specular_mask_material() override;

    std::shared_ptr<Texture>& specular_mask_texture();

    void update_uniform(const std::shared_ptr<Node>& node, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) override;
    void before_geometry_draw() override;
    void after_geometry_draw() override;
    void load_from_assimp(const aiScene* scene, const aiMaterial* assimp_material) override;
};
