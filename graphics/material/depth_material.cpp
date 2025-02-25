#include "depth_material.h"

Depth_material::Depth_material() : Material(Material_type::DEPTH, Shader_program::create_shader_program("assets/shaders/shading/depth/depth.vert", "assets/shaders/shading/depth/depth.frag")) {}
Depth_material::~Depth_material() = default;

void Depth_material::update_uniform(const std::shared_ptr<Node>& node, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) {
    m_shader->set_uniform_glm<glm::mat4>("model_matrix", node->model_matrix());
    m_shader->set_uniform_glm<glm::mat4>("view_matrix", camera->view_matrix());
    m_shader->set_uniform_glm<glm::mat4>("projection_matrix", camera->projection_matrix());

    m_shader->set_uniform<float>("near", camera->m_near_bound);
    m_shader->set_uniform<float>("far", camera->m_far_bound);
}