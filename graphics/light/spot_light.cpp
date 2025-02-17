#include "spot_light.h"

Spot_light::Spot_light() : Light(), Node(Node_type::LIGHT) { }

float& Spot_light::inner_angle() { return m_inner_angle; }
float& Spot_light::outer_angle() { return m_outer_angle; }

float Spot_light::inner_angle() const { return m_inner_angle; }
float Spot_light::outer_angle() const { return m_outer_angle; }
glm::vec3 Spot_light::light_direction() const { return world_node().front(); }
glm::vec3 Spot_light::light_position() const { return world_node().position(); }

void Spot_light::set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name) {
    shader->set_uniform_glm<glm::vec3>(var_name + ".color", color());
    shader->set_uniform_glm<glm::vec3>(var_name + ".direction", light_direction());
    shader->set_uniform_glm<glm::vec3>(var_name + ".position", light_position());
    shader->set_uniform<float>(var_name + ".intensity", intensity());
    shader->set_uniform<float>(var_name + ".outer_angle", glm::cos(glm::radians(outer_angle())));
    shader->set_uniform<float>(var_name + ".inner_angle", glm::cos(glm::radians(inner_angle())));
}

void Spot_light::set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name, int index) {
    std::string indexed_var = indexed_var_name(var_name, index);
    
    shader->set_uniform_glm<glm::vec3>(indexed_var + ".color", color());
    shader->set_uniform_glm<glm::vec3>(indexed_var + ".direction", light_direction());
    shader->set_uniform_glm<glm::vec3>(indexed_var + ".position", light_position());
    shader->set_uniform<float>(indexed_var + ".intensity", intensity());
    shader->set_uniform<float>(indexed_var + ".outer_angle", glm::cos(glm::radians(outer_angle())));
    shader->set_uniform<float>(indexed_var + ".inner_angle", glm::cos(glm::radians(inner_angle())));
}
