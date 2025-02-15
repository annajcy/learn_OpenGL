#include "shader_code.h"

Shader_code::Shader_code(const std::string &code, Shader_type type){
    init(code, type);
}

Shader_code::~Shader_code(){
    destroy();
}

void Shader_code::init(const std::string &code, Shader_type type) {
    m_code = code;
    m_type = type;
    m_code_id = glCreateShader(shader_type_to_gl_enum(m_type));
    const char* code_ptr = m_code.c_str();
    glShaderSource(m_code_id, 1, &code_ptr, nullptr);
}

void Shader_code::destroy() {
    glDeleteShader(m_code_id);
}

void Shader_code::compile() {
    glCompileShader(m_code_id);
}

void Shader_code::check_compile_error() {
    char info_log[LOG_STR_LEN];
    int success{};
    glGetShaderiv(m_code_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(m_code_id, LOG_STR_LEN, nullptr, info_log);
        std::cerr << "Shader compiled failed" << " --" << shader_type_to_string(m_type) << " " <<  m_code_id << std::endl;
        std::cerr << info_log << std::endl;
    } else {
        std::cout << "Shader compiled successfully" << " --" << shader_type_to_string(m_type) << " " << m_code_id << std::endl;
    }
}

constexpr const char* Shader_code::shader_type_to_string(Shader_type type) {
    switch (type) {
        case Shader_type::VERTEX:
            return "VERTEX";
        case Shader_type::FRAGMENT:
            return "FRAGMENT";
        case Shader_type::GEOMETRY:
            return "GEOMETRY";
        case Shader_type::TESS_CONTROL:
            return "TESS_CONTROL";
        case Shader_type::COMPUTE:
            return "COMPUTE";
        default:
            return "UNKNOWN";
    }
}

constexpr GLenum Shader_code::shader_type_to_gl_enum(Shader_type type) {
    switch (type) {
        case Shader_type::VERTEX:
            return GL_VERTEX_SHADER;
        case Shader_type::FRAGMENT:
            return GL_FRAGMENT_SHADER;
        case Shader_type::GEOMETRY:
            return GL_GEOMETRY_SHADER;
        case Shader_type::TESS_CONTROL:
            return GL_TESS_CONTROL_SHADER;
        case Shader_type::COMPUTE:
            return GL_TESS_CONTROL_SHADER;
        default:
            return 0xFFFF;
    }

}

[[nodiscard]] GLuint Shader_code::get_id() const { return m_code_id; }
[[nodiscard]] Shader_code::Shader_type Shader_code::get_type() const { return m_type; }
[[nodiscard]] const std::string& Shader_code::get_code() const { return m_code; }