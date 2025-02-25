#include "phong_opacity_mask_material.h"

Phong_opacity_mask_material::Phong_opacity_mask_material() : 
    Phong_material(
        Material_type::PHONG_OPACITY_MASK, 
        Shader_program::create_shader_program(
            "assets/shaders/shading/phong_opacity_mask/phong_opacity_mask.vert", 
            "assets/shaders/shading/phong_opacity_mask/phong_opacity_mask.frag")) { 
                m_color_blend_setting = Color_blend_setting::enable_setting();
                m_depth_test_setting = Depth_test_setting::disable_write_setting();
            }

Phong_opacity_mask_material::~Phong_opacity_mask_material() = default;

std::shared_ptr<Texture>& Phong_opacity_mask_material::opcacity_mask_texture() { 
    return m_opacity_mask_texture; 
}

void Phong_opacity_mask_material::update_uniform(const std::shared_ptr<Node>& node, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) {
    Phong_material::update_uniform(node, camera, light_setting);
    m_shader->set_uniform<int>("opacity_mask_sampler", 1);
}

void Phong_opacity_mask_material::before_geometry_draw() {
    Phong_material::before_geometry_draw();
    if (m_opacity_mask_texture) {
        m_opacity_mask_texture->attach_texture();
    }
}

void Phong_opacity_mask_material::after_geometry_draw() {
    Phong_material::after_geometry_draw();
    if (m_opacity_mask_texture) {
        m_opacity_mask_texture->detach_texture();
    }
}

void Phong_opacity_mask_material::load_from_assimp(const aiScene* scene, const aiMaterial* assimp_material) {
    m_main_texture = Texture::create_texture_from_path("assets/image/grass.jpg", 0, "assets/image/grass.jpg");
    m_opacity_mask_texture = Texture::create_texture_from_path("assets/image/grassMask.png", 1, "assets/image/grassMask.png");
}
