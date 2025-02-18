#pragma once 

#include "global/core.h"
#include "shader_code.h"
#include "utils/string_utils.h"


class Shader_program : public std::enable_shared_from_this<Shader_program>
{
private:
    GLuint m_program_id{0};
    std::vector<std::shared_ptr<Shader_code>> m_shaders{};
    std::string m_key{};
public:
    Shader_program();
    Shader_program(const std::string& vs_path, const std::string &fs_path);
    Shader_program(const Shader_program&) = delete;
    virtual ~Shader_program();

    void init();
    void destroy();
    void attach_shader(const std::shared_ptr<Shader_code>& shader);
    void link();
    void check_link_error();

    template<typename T>
    void set_uniform(const std::string& name, T value) {
        GLint location = glGetUniformLocation(m_program_id, name.c_str());
        if (std::is_same<T, int>::value) {
            glUniform1i(location, value);
        } else if (std::is_same<T, float>::value) {
            glUniform1f(location, value);
        } else {
            std::cerr << "Unsupported uniform type" << std::endl;
        }
    }

    template<typename T>
    void set_uniform_glm(const std::string& name, const T& value) {
        GLint location = glGetUniformLocation(m_program_id, name.c_str());
        if constexpr (std::is_same<T, glm::vec2>::value) {
            glUniform2fv(location, 1, glm::value_ptr(value));
        } else if constexpr (std::is_same<T, glm::vec3>::value) {
            glUniform3fv(location, 1, glm::value_ptr(value));
        } else if constexpr (std::is_same<T, glm::vec4>::value) {
            glUniform4fv(location, 1, glm::value_ptr(value));
        } else if constexpr (std::is_same<T, glm::ivec2>::value) {
            glUniform2iv(location, 1, glm::value_ptr(value));
        } else if constexpr (std::is_same<T, glm::ivec3>::value) {
            glUniform3iv(location, 1, glm::value_ptr(value));
        } else if constexpr (std::is_same<T, glm::ivec4>::value) {
            glUniform4iv(location, 1, glm::value_ptr(value));
        } else if constexpr (std::is_same<T, glm::mat2>::value) {
            glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
        } else if constexpr (std::is_same<T, glm::mat3>::value) {
            glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
        } else if constexpr (std::is_same<T, glm::mat4>::value) {
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
        }
    }

    void attach_program();
    void detach_program();

    [[nodiscard]] GLuint get_id() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Shader_code>>& get_shaders() const;

    static std::shared_ptr<Shader_program> create_shader_program(const std::string& vs_path, const std::string &fs_path);
    static std::unordered_map<std::string, std::shared_ptr<Shader_program>> shader_program_cache;
    
};