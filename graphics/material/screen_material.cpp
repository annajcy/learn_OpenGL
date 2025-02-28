#include "screen_material.h"

Screen_material::Screen_material() : 
Material(Material_type::SCREEN, Shader_program::create_shader_program("assets/shaders/screen/screen.vert", "assets/shaders/screen/screen.frag")) {}

Screen_material::~Screen_material() = default;

void Screen_material::update_uniform(const std::shared_ptr<Node>& node, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) {
    m_shader->set_uniform<int>("screen_texture_sampler", 0);
    m_shader->set_uniform_glm<glm::vec2>("resolution", glm::vec2(m_screen_texture->width(), m_screen_texture->height()));
    m_shader->set_uniform<int>("is_invert", 0);
    m_shader->set_uniform<int>("is_blur", 1);
    m_shader->set_uniform<int>("is_grayscale", 0);
}

void Screen_material::before_geometry_draw() {
    if (m_screen_texture) {
        m_screen_texture->attach_texture();
    }
}

void Screen_material::after_geometry_draw() {
    if (m_screen_texture) {
        m_screen_texture->detach_texture();
    }
}

std::shared_ptr<Texture>& Screen_material::screen_texture() {
    return m_screen_texture;
}

void Screen_material::load_from_assimp(const aiScene* scene, const aiMaterial* assimp_material) {
    m_screen_texture = Texture::create_texture_from_path("assets/image/box.png", 0, "assets/image/box.png");
}