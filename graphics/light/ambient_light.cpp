#include "ambient_light.h"
#include <string> // 包含 std::to_string 的头文件

// 实现 set_shader_uniform 函数
void Ambient_light::set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name) {
    shader->set_uniform_glm<glm::vec3>(var_name + ".color", m_color);
    shader->set_uniform<float>(var_name + ".intensity", m_intensity);
}

void Ambient_light::set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name, int index) {
    shader->set_uniform_glm<glm::vec3>(var_name + "[" + std::to_string(index) + "].color", m_color);
    shader->set_uniform<float>(var_name + "[" + std::to_string(index) + "].intensity", m_intensity);
}