#include "spot_light.h"

Spot_light::Spot_light() : Light(), Node(Node_type::LIGHT) { }

float& Spot_light::inner_angle() { return m_inner_angle; }
float& Spot_light::outer_angle() { return m_outer_angle; }
glm::vec3& Spot_light::direction() { return m_direction; }

float Spot_light::inner_angle() const { return m_inner_angle; }
float Spot_light::outer_angle() const { return m_outer_angle; }
glm::vec3 Spot_light::direction() const { return m_direction; }

void Spot_light::set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name) {
    shader->set_uniform_glm<glm::vec3>(var_name + ".color", m_color);
    shader->set_uniform_glm<glm::vec3>(var_name + ".direction", m_direction);
    shader->set_uniform_glm<glm::vec3>(var_name + ".position", m_position);
    shader->set_uniform<float>(var_name + ".intensity", m_intensity);
    shader->set_uniform<float>(var_name + ".outer_angle", glm::cos(glm::radians(m_outer_angle)));
    shader->set_uniform<float>(var_name + ".inner_angle", glm::cos(glm::radians(m_inner_angle)));
}

void Spot_light::set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name, int index) {
    std::string indexed_var = var_name + "[" + std::to_string(index) + "]";
    shader->set_uniform_glm<glm::vec3>(indexed_var + ".color", m_color);
    shader->set_uniform_glm<glm::vec3>(indexed_var + ".direction", m_direction);
    shader->set_uniform_glm<glm::vec3>(indexed_var + ".position", m_position);
    shader->set_uniform<float>(indexed_var + ".intensity", m_intensity);
    shader->set_uniform<float>(indexed_var + ".outer_angle", glm::cos(glm::radians(m_outer_angle)));
    shader->set_uniform<float>(indexed_var + ".inner_angle", glm::cos(glm::radians(m_inner_angle)));
}
