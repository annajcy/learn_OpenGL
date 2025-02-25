#include "edge_material.h"

Edge_material::Edge_material() : Material(Material_type::EDGE, Shader_program::create_shader_program("assets/shaders/shading/edge/edge.vert", "assets/shaders/shading/edge/edge.frag")) {
    m_stencil_test_setting = Stencil_test_setting::edge_setting();
}

void Edge_material::update_uniform(const std::shared_ptr<Node>& node, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) {
    m_shader->set_uniform_glm<glm::mat4>("model_matrix", node->model_matrix());
    m_shader->set_uniform_glm<glm::mat4>("view_matrix", camera->view_matrix());
    m_shader->set_uniform_glm<glm::mat4>("projection_matrix", camera->projection_matrix());
}