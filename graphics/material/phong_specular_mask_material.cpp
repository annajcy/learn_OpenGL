#include "phong_specular_mask_material.h"

Phong_specular_mask_material::Phong_specular_mask_material() : 
    Phong_material(
        Material_type::PHONG_SPECULAR_MASK, 
        Shader_program::create_shader_program(
            "assets/shaders/shading/phong_specular_mask/phong_specular_mask.vert", 
            "assets/shaders/shading/phong_specular_mask/phong_specular_mask.frag")) { }

Phong_specular_mask_material::~Phong_specular_mask_material() = default;

std::shared_ptr<Texture>& Phong_specular_mask_material::specular_mask_texture() { 
    return m_specular_mask_texture; 
}

void Phong_specular_mask_material::update_uniform(const std::shared_ptr<Node>& node, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) {
    Phong_material::update_uniform(node, camera, light_setting);
    m_shader->set_uniform<int>("specular_mask_sampler", 1);
}

void Phong_specular_mask_material::before_geometry_draw() {
    Phong_material::before_geometry_draw();
    if (m_specular_mask_texture) {
        m_specular_mask_texture->attach_texture();
    }
}

void Phong_specular_mask_material::after_geometry_draw() {
    Phong_material::after_geometry_draw();
    if (m_specular_mask_texture) {
        m_specular_mask_texture->detach_texture();
    }
}

void Phong_specular_mask_material::load_from_assimp(const aiScene* scene, const aiMaterial* assimp_material) {
    auto diffuse = Assimp_utils::process_texture(scene, assimp_material, aiTextureType::aiTextureType_DIFFUSE, 0);
    m_main_texture = diffuse ? diffuse : Texture::create_default_texture(0);

    auto specular = Assimp_utils::process_texture(scene, assimp_material, aiTextureType::aiTextureType_SPECULAR, 1);
    m_specular_mask_texture = specular ? specular : Texture::create_default_texture(1);
}
