#include "point_light.h"

Point_light::Point_light() : Light(), Node(Node_type::LIGHT) { }

float& Point_light::k1() { return m_k1; }
float& Point_light::k2() { return m_k2; }
float& Point_light::kc() { return m_kc; }

float Point_light::k1() const { return m_k1; }
float Point_light::k2() const { return m_k2; }
float Point_light::kc() const { return m_kc; }

glm::vec3 Point_light::light_position() const { return world_node().position(); }

void Point_light::set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name) {
    shader->set_uniform_glm<glm::vec3>(var_name + ".color", color());
    shader->set_uniform_glm<glm::vec3>(var_name + ".position", light_position());
    shader->set_uniform<float>(var_name + ".intensity", intensity());
    shader->set_uniform<float>(var_name + ".k1", k1());
    shader->set_uniform<float>(var_name + ".k2", k2());
    shader->set_uniform<float>(var_name + ".kc", kc());
}

void Point_light::set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name, int index) {
    std::string indexed_var = indexed_var_name(var_name, index);
    shader->set_uniform_glm<glm::vec3>(indexed_var + ".color", color());
    shader->set_uniform_glm<glm::vec3>(indexed_var + ".position", light_position());
    shader->set_uniform<float>(indexed_var + ".intensity", intensity());
    shader->set_uniform<float>(indexed_var + ".k1", k1());
    shader->set_uniform<float>(indexed_var + ".k2", k2());
    shader->set_uniform<float>(indexed_var + ".kc", kc());
}
