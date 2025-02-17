#include "directional_light.h"

// 构造函数
Directional_light::Directional_light() : Light(), Node(Node_type::LIGHT) { }

// 获取方向向量
glm::vec3 Directional_light::light_direction() const {
    return world_node().front();
}

// 实现 set_shader_uniform 函数（无索引）
void Directional_light::set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name) {
    shader->set_uniform_glm<glm::vec3>(var_name + ".color", color());
    shader->set_uniform<float>(var_name + ".intensity", intensity());

    shader->set_uniform_glm<glm::vec3>(var_name + ".direction", light_direction());
}

// 实现 set_shader_uniform 函数（有索引）
void Directional_light::set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name, int index) {

    auto indexed_var = indexed_var_name(var_name, index);

    shader->set_uniform_glm<glm::vec3>(indexed_var + ".color", color());
    shader->set_uniform<float>(indexed_var + ".intensity", intensity());
    
    shader->set_uniform_glm<glm::vec3>(indexed_var + ".direction", light_direction());
    
}