#include "cube_map_material.h"

std::shared_ptr<Texture>& Cube_map_material::cube_map() { 
    return m_cube_map; 
}

Cube_map_material::Cube_map_material() : 
    Material(Material_type::CUBE_MAP, 
    Shader_program::create_shader_program("assets/shaders/skybox/cube_map/cube_map.vert", 
    "assets/shaders/skybox/cube_map/cube_map.frag")) 
{
    m_depth_test_setting = Depth_test_setting::disable_write_setting();
    m_depth_test_setting.depth_test_function = Depth_test_setting::Depth_test_function::LEQUAL;
    
    m_cube_map = Texture::create_cube_map({
        "assets/image/skybox/right.jpg",
        "assets/image/skybox/left.jpg",
        "assets/image/skybox/top.jpg",
        "assets/image/skybox/bottom.jpg",
        "assets/image/skybox/back.jpg",
        "assets/image/skybox/front.jpg"
    });
}

Cube_map_material::~Cube_map_material() = default;

void Cube_map_material::update_uniform(const std::shared_ptr<Node>& node, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) {
    m_shader->set_uniform_glm<glm::mat4>("model_matrix", glm::translate(glm::identity<glm::mat4>(), camera->position()));
    m_shader->set_uniform_glm<glm::mat4>("view_matrix", camera->view_matrix());
    m_shader->set_uniform_glm<glm::mat4>("projection_matrix", camera->projection_matrix());
    m_shader->set_uniform<int>("cube_map_sampler", 0);
}

void Cube_map_material::before_geometry_draw() {
    m_cube_map->attach_texture();
}

void Cube_map_material::after_geometry_draw() {
    m_cube_map->detach_texture();
}
