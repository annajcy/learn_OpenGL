#pragma once 

#include "global/core.h"
#include "shader_code.h"
#include <vector>
#include <memory>

class Shader_program
{
private:
    GLuint m_program_id{0};
    std::vector<std::shared_ptr<Shader_code>> m_shaders{};
public:
    Shader_program();
    Shader_program(const Shader_program&) = delete;
    ~Shader_program();

    void init();
    void destroy();
    void attach_shader(const std::shared_ptr<Shader_code>& shader);
    void link();
    void check_link_error();
    void attach_program();
    static void detach_program();

    [[nodiscard]] GLuint get_id() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Shader_code>>& get_shaders() const;
};