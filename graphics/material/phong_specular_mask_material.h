#pragma once

#include "material.h"
#include "phong_material.h"

class Phong_specular_mask_material : public Phong_material
{
private:
    std::shared_ptr<Texture> m_specular_mask_texture{};
public:
    Phong_specular_mask_material() : 
    Phong_material(
        Material_type::PHONG_SPECULAR_MASK, 
        Shader_program::create_shader_program(
            "assets/shaders/phong_specular_mask/phong_specular_mask.vert", 
            "assets/shaders/phong_specular_mask/phong_specular_mask.frag")) { }

    ~Phong_specular_mask_material() override = default;

    std::shared_ptr<Texture>& specular_mask_texture() { return m_specular_mask_texture; }

    void update_uniform(const std::shared_ptr<Node>& node, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) override {
        Phong_material::update_uniform(node, camera, light_setting);
        m_shader->set_uniform<int>("specular_mask_sampler", 1);
    }
 
};
