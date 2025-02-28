#include "sperical_map_material.h"

std::shared_ptr<Texture>& Sperical_map_material::sperical_map() { 
    return m_sperical_map; 
}

Sperical_map_material::Sperical_map_material() : 
    Material(Material_type::SPERICAL_MAP, 
    Shader_program::create_shader_program("assets/shaders/skybox/sperical_map/sperical_map.vert", 
    "assets/shaders/skybox/sperical_map/sperical_map.frag")) 
{
    m_depth_test_setting = Depth_test_setting::disable_write_setting();
    m_depth_test_setting.depth_test_function = Depth_test_setting::Depth_test_function::LEQUAL;
    m_sperical_map = Texture::create_texture_from_path("assets/image/bk.jpg", 0, "assets/image/bk.jpg");
}

Sperical_map_material::~Sperical_map_material() = default;

void Sperical_map_material::update_uniform(const std::shared_ptr<Node>& node, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) {
    m_shader->set_uniform_glm<glm::mat4>("model_matrix", glm::translate(glm::identity<glm::mat4>(), camera->position()));
    m_shader->set_uniform_glm<glm::mat4>("view_matrix", camera->view_matrix());
    m_shader->set_uniform_glm<glm::mat4>("projection_matrix", camera->projection_matrix());
    m_shader->set_uniform<int>("sperical_map_sampler", 0);
}

void Sperical_map_material::before_geometry_draw() {
    m_sperical_map->attach_texture();
}

void Sperical_map_material::after_geometry_draw() {
    m_sperical_map->detach_texture();
}
