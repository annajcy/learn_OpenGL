#pragma once

#include "material.h"
#include "phong_material.h"

class Phong_opacity_mask_material : public Phong_material
{
private:
    std::shared_ptr<Texture> m_opacity_mask_texture{};
public:
    Phong_opacity_mask_material() : 
    Phong_material(
        Material_type::PHONG_OPACITY_MASK, 
        Shader_program::create_shader_program(
            "assets/shaders/phong_opacity_mask/phong_opacity_mask.vert", 
            "assets/shaders/phong_opacity_mask/phong_opacity_mask.frag")) { 
                m_color_blend_setting = Color_blend_setting::enable_setting();
                m_depth_test_setting = Depth_test_setting::disable_write_setting();
            }

    ~Phong_opacity_mask_material() override = default;

    std::shared_ptr<Texture>& opcacity_mask_texture() { return m_opacity_mask_texture; }

    void update_uniform(const std::shared_ptr<Node>& node, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) override {
        Phong_material::update_uniform(node, camera, light_setting);
        m_shader->set_uniform<int>("opacity_mask_sampler", 2);
    }
 
};
