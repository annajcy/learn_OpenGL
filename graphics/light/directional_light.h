#pragma once

#include "light.h"       // 包含 Light 基类的定义

class Directional_light : public Light, public Node
{

public:
    Directional_light(); // 构造函数
    ~Directional_light() = default; // 析构函数

    // 获取和设置方向向量
    [[nodiscard]] glm::vec3 light_direction() const;

    // 设置着色器 uniform 变量的函数
    void set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name) override;
    void set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name, int index) override;
};