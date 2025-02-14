#pragma once

#include "light.h"
#include "graphics/node.h"

class Spot_light : public Light, public Node
{
private:
    float m_inner_angle {30.0f};
    float m_outer_angle {40.0f};
    glm::vec3 m_direction = glm::zero<glm::vec3>();

public:
    Spot_light();
    ~Spot_light() = default;

    float& inner_angle();
    float& outer_angle();
    glm::vec3& direction();

    [[nodiscard]] float inner_angle() const;
    [[nodiscard]] float outer_angle() const;
    [[nodiscard]] glm::vec3 direction() const;

    void set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name) override;
    void set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name, int index) override;
};
