#pragma once

#include "light.h" 

class Ambient_light : public Light
{
public:
    Ambient_light() = default;
    ~Ambient_light() = default;

    // 设置着色器 uniform 变量的函数
    void set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name) override;
    void set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name, int index) override;
};