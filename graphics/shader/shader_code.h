#pragma once

#include <global/core.h>
#include <string>
#include <iostream>

#define LOG_STR_LEN 1024

class Shader_code
{
public:

    enum class Shader_type {
        VERTEX, FRAGMENT, GEOMETRY, TESS_CONTROL, COMPUTE,
    };

    static constexpr const char* shader_type_to_string(Shader_type type);
    static constexpr GLenum shader_type_to_gl_enum(Shader_type type);

private:
    GLuint m_code_id{};
    std::string m_code{};
    Shader_type m_type{};
public:
    Shader_code(const std::string &code, Shader_type type);
    ~Shader_code();

    void init(const std::string &code, Shader_type type);
    void compile();
    void check_compile_error();
    void destroy(); 

    [[nodiscard]] GLuint get_id() const;
    [[nodiscard]] Shader_type get_type() const;
    [[nodiscard]] const std::string& get_code() const;

};


