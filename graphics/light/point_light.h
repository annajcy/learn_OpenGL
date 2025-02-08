#pragma once

#include "light.h"
#include "graphics/node.h"
#include <memory>
#include <string>

class Point_light : public Light, public Node
{
private:
    float m_k1 {1.0f};
    float m_k2 {1.0f};
    float m_kc {1.0f};

public:
    Point_light();
    ~Point_light() = default;

    float& k1();
    float& k2();
    float& kc();

    [[nodiscard]] float k1() const;
    [[nodiscard]] float k2() const;
    [[nodiscard]] float kc() const;

    void set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name) override;
    void set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name, int index) override;
};
