#include "shader_program.h"

std::unordered_map<std::string, std::shared_ptr<Shader_program>> Shader_program::shader_program_cache{};

Shader_program::Shader_program() { init(); };

Shader_program::Shader_program(const std::string& vs_path, const std::string &fs_path) {

    init();

    std::cout << "Start to compile shader program :" << std::endl;
    std::cout << "Vertex shader path: " << vs_path << std::endl;
    std::cout << "Fragment shader path: " << fs_path << std::endl;

    std::shared_ptr<Shader_code> vs = std::make_shared<Shader_code>(utils::load_from_file(vs_path), Shader_code::Shader_type::VERTEX);
    vs->compile();
    vs->check_compile_error();

    std::shared_ptr<Shader_code> fs = std::make_shared<Shader_code>(utils::load_from_file(fs_path), Shader_code::Shader_type::FRAGMENT);
    fs->compile();
    fs->check_compile_error();

    attach_shader(vs);
    attach_shader(fs);
    
    link();
    check_link_error();



}

Shader_program::~Shader_program() { destroy(); }

void Shader_program::init() { m_program_id = glCreateProgram(); }

void Shader_program::destroy() { 
    glDeleteProgram(m_program_id);
    shader_program_cache.erase(m_key);
}

void Shader_program::link() { glLinkProgram(m_program_id); }
void Shader_program::attach_program() { glUseProgram(m_program_id); }
void Shader_program::detach_program() { glUseProgram(0); }

GLuint Shader_program::get_id() const { return m_program_id; }
const std::vector<std::shared_ptr<Shader_code>>& Shader_program::get_shaders() const { return m_shaders; }

void Shader_program::attach_shader(const std::shared_ptr<Shader_code>& shader) {
    m_shaders.push_back(shader);
    glAttachShader(m_program_id, shader->get_id());
}

void Shader_program::check_link_error() {
    char info_log[LOG_STR_LEN];
    int success{};
    glGetProgramiv(m_program_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_program_id, LOG_STR_LEN, nullptr, info_log);
        std::cerr << "Shader program linked failed" << " --" << m_program_id << std::endl;
        std::cerr << info_log << std::endl;
    } else {
        std::cout << "Shader program linked successfully" << " -- " << m_program_id << std::endl;
    }
}

std::shared_ptr<Shader_program> Shader_program::create_shader_program(const std::string& vs_path, const std::string &fs_path) {
    std::string key = vs_path + fs_path;
    if (shader_program_cache.contains(key)) return shader_program_cache.at(key);
    auto shader = std::make_shared<Shader_program>(vs_path, fs_path);
    shader->m_key = key;
    shader_program_cache.insert({key, shader});
    return shader;
}