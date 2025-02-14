#pragma once

#include "light.h"       // 包含 Light 基类的定义

class Directional_light : public Light
{
private:
    glm::vec3 m_direction = glm::one<glm::vec3>(); // 方向向量

public:
    Directional_light(); // 构造函数
    ~Directional_light() = default; // 析构函数

    // 获取和设置方向向量
    [[nodiscard]] glm::vec3 direction() const;
    glm::vec3& direction();

    // 设置着色器 uniform 变量的函数
    void set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name) override;
    void set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name, int index) override;
};