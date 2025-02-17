#pragma once

#include "global/core.h"
#include "graphics/shader/shader_program.h"
#include "graphics/node.h"

class Light
{
protected:
    glm::vec3 m_color = glm::one<glm::vec3>();
    float m_intensity { 1.0f };

    static std::string indexed_var_name(const std::string &var_name, int index);

public:
    Light() = default;
    virtual ~Light() = default;

    glm::vec3& color();
    float& intensity();

    [[nodiscard]] glm::vec3 color() const;
    [[nodiscard]] float intensity() const;

    virtual void set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name) = 0;
    virtual void set_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::string &var_name, int index) = 0;
};
