#include "phong_material.h"

Phong_material::Phong_material() : Material(Material_type::PHONG, Shader_program::create_shader_program("assets/shaders/shading/phong/phong.vert", "assets/shaders/shading/phong/phong.frag")) { }
Phong_material::Phong_material(Material_type type, const std::shared_ptr<Shader_program>& shader) : Material(type, shader) {}

float Phong_material::kd() const { return m_kd; }
float Phong_material::ks() const { return m_ks; }
float Phong_material::ka() const { return m_ka; }
float Phong_material::shiness() const { return m_shiness; }

float& Phong_material::kd() { return m_kd; }
float& Phong_material::ks() { return m_ks; }
float& Phong_material::ka() { return m_ka; }
float& Phong_material::shiness() { return m_shiness; }

std::shared_ptr<Texture>& Phong_material::main_texture() { return m_main_texture; }

void Phong_material::update_uniform(const std::shared_ptr<Node>& node, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) {

    auto &als = light_setting->ambient_lights();
    auto &dls = light_setting->directional_lights();
    auto &pls = light_setting->point_lights();
    auto &spls = light_setting->spot_lights();

    m_shader->set_uniform<float>("time", glfwGetTime());
    m_shader->set_uniform<int>("main_sampler", 0);
    m_shader->set_uniform_glm<glm::vec4>("material", glm::vec4(ka(), kd(), ks(), shiness()));

    m_shader->set_uniform_glm<glm::mat4>("model_matrix", node->model_matrix());
    m_shader->set_uniform_glm<glm::mat4>("view_matrix", camera->view_matrix());
    m_shader->set_uniform_glm<glm::mat4>("projection_matrix", camera->projection_matrix());
    auto normal_matrix = glm::mat3(glm::transpose(glm::inverse(node->model_matrix())));
    m_shader->set_uniform_glm<glm::mat3>("normal_matrix", normal_matrix);
    
    m_shader->set_uniform_glm<glm::vec3>("camera_position", camera->position());
    m_shader->set_uniform_glm<glm::ivec4>("light_count", glm::ivec4((int)als.size(), (int)dls.size(), (int)pls.size(), (int)spls.size()));

    for (int i = 0; i < als.size(); i++) {
        auto &al = als[i];
        al->set_shader_uniform(m_shader, "ambient_lights", i);
    }

    for (int i = 0; i < dls.size(); i++) {
        auto &dl = dls[i];
        dl->set_shader_uniform(m_shader, "directional_lights", i);
    }

    for (int i = 0; i < pls.size(); i++) {
        auto &pl = pls[i];
        pl->set_shader_uniform(m_shader, "point_lights", i);
    }

    for (int i = 0; i < spls.size(); i++) {
        auto &spl = spls[i];
        spl->set_shader_uniform(m_shader, "spot_lights", i);
    }
}

void Phong_material::before_geometry_draw() {
    if (m_main_texture != nullptr) {
        m_main_texture->attach_texture();
    }
}

void Phong_material::after_geometry_draw() {
    if (m_main_texture!= nullptr) {
        m_main_texture->detach_texture();
    }
}

void Phong_material::load_from_assimp(const aiScene* scene, const aiMaterial* assimp_material) {
    auto diffuse = Assimp_utils::process_texture(scene, assimp_material, aiTextureType::aiTextureType_DIFFUSE, 0);
    m_main_texture = diffuse ? diffuse : Texture::create_default_texture(0);
    m_main_texture->generate_mipmaps();
    m_main_texture->set_filter(Texture::Filter::MIN, Texture::Filter_type::LINEAR_MIPMAP_LINEAR);
    m_main_texture->set_filter(Texture::Filter::MAG, Texture::Filter_type::LINEAR);
}