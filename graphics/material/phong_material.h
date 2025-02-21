#pragma once

#include "material.h"
#include "graphics/texture.h"
#include "application/assimp_utils.h"

class Phong_material : public Material
{
protected:
    float m_kd{1.0f};
    float m_ks{1.0f};
    float m_ka{1.0f};
    float m_shiness{16.0f};

    std::shared_ptr<Texture> m_main_texture{};
    
public:
    Phong_material();
    Phong_material(Material_type type, const std::shared_ptr<Shader_program>& shader);
    virtual ~Phong_material() override = default;

    [[nodiscard]] float kd() const;
    [[nodiscard]] float ks() const;
    [[nodiscard]] float ka() const;
    [[nodiscard]] float shiness() const;

    float& kd();
    float& ks();
    float& ka();
    float& shiness();

    std::shared_ptr<Texture>& main_texture();

    virtual void before_geometry_draw() override;
    virtual void after_geometry_draw() override;
    virtual void load_from_assimp(const aiScene* scene, const aiMaterial* assimp_material) override;

    virtual void update_uniform(const std::shared_ptr<Node>& node, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) override;
    
};
