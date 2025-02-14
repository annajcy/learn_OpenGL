#include "directional_light.h"

// 构造函数
Directional_light::Directional_light() : Light() { }

// 获取方向向量
glm::vec3 Directional_light::direction() const {
    return m_direction;
}

// 设置方向向量
glm::vec3& Directional_light::direction() {
    return m_direction;
}

// 实现 set_shader_uniform 函数（无索引）
void Directional_light::set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name) {
    shader->set_uniform_glm<glm::vec3>(var_name + ".color", m_color);
    shader->set_uniform_glm<glm::vec3>(var_name + ".direction", m_direction);
    shader->set_uniform<float>(var_name + ".intensity", m_intensity);
}

// 实现 set_shader_uniform 函数（有索引）
void Directional_light::set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name, int index) {
    shader->set_uniform_glm<glm::vec3>(var_name + "[" + std::to_string(index) + "].color", m_color);
    shader->set_uniform_glm<glm::vec3>(var_name + "[" + std::to_string(index) + "].direction", m_direction);
    shader->set_uniform<float>(var_name + "[" + std::to_string(index) + "].intensity", m_intensity);
}