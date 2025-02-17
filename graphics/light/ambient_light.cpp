#include "ambient_light.h"

// 实现 set_shader_uniform 函数
void Ambient_light::set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name) {
    shader->set_uniform_glm<glm::vec3>(var_name + ".color", m_color);
    shader->set_uniform<float>(var_name + ".intensity", m_intensity);
}

void Ambient_light::set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name, int index) {
    auto indexed_var = indexed_var_name(var_name, index);
    shader->set_uniform_glm<glm::vec3>(indexed_var + ".color", m_color);
    shader->set_uniform<float>(indexed_var + ".intensity", m_intensity);
}