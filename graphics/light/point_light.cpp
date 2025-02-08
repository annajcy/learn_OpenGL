#include "point_light.h"

Point_light::Point_light() : Light(), Node(Node_type::LIGHT) { }

float& Point_light::k1() { return m_k1; }
float& Point_light::k2() { return m_k2; }
float& Point_light::kc() { return m_kc; }

float Point_light::k1() const { return m_k1; }
float Point_light::k2() const { return m_k2; }
float Point_light::kc() const { return m_kc; }

void Point_light::set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name) {
    shader->set_uniform_glm<glm::vec3>(var_name + ".color", m_color);
    shader->set_uniform_glm<glm::vec3>(var_name + ".position", m_position);
    shader->set_uniform<float>(var_name + ".intensity", m_intensity);
    shader->set_uniform<float>(var_name + ".k1", m_k1);
    shader->set_uniform<float>(var_name + ".k2", m_k2);
    shader->set_uniform<float>(var_name + ".kc", m_kc);
}

void Point_light::set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name, int index) {
    std::string indexed_var = var_name + "[" + std::to_string(index) + "]";
    shader->set_uniform_glm<glm::vec3>(indexed_var + ".color", m_color);
    shader->set_uniform_glm<glm::vec3>(indexed_var + ".position", m_position);
    shader->set_uniform<float>(indexed_var + ".intensity", m_intensity);
    shader->set_uniform<float>(indexed_var + ".k1", m_k1);
    shader->set_uniform<float>(indexed_var + ".k2", m_k2);
    shader->set_uniform<float>(indexed_var + ".kc", m_kc);
}
