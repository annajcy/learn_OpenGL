#include "renderer.h"
#include <iostream>

Renderer::Renderer(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) 
    : m_camera(camera), m_light_settings(light_setting), 
      m_phong_shader(Shader_program::create_vs_fs_program("assets/shaders/phong/phong.vert", "assets/shaders/phong/phong.frag")), 
      m_white_shader(Shader_program::create_vs_fs_program("assets/shaders/white/white.vert", "assets/shaders/white/white.frag")) { }

std::shared_ptr<Camera>& Renderer::camera() { 
    return m_camera; 
}

std::shared_ptr<Light_setting>& Renderer::light_setting() { 
    return m_light_settings; 
}

std::vector<std::shared_ptr<Mesh>>& Renderer::mesh_list() { 
    return m_mesh_list; 
}

void Renderer::set_clear_color(const glm::vec3& color) {
    glClearColor(color.r, color.g, color.b, 1.0f);
}

void Renderer::init_state() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render() {
    if (!m_camera || !m_light_settings || m_mesh_list.empty()) {
        std::cout << "invalid render params" << std::endl;
        return;
    }

    for (auto &mesh : m_mesh_list) {
        auto &geo = mesh->geometry();
        auto &mat = mesh->material();

        auto shader = pick_shader(mat->type());
        shader->attach_program();

        // Update uniforms
        if (mat->type() == Material::Material_type::PHONG) {
            auto phong_mat = std::dynamic_pointer_cast<Phong_material>(mat);

            phong_mat->main_texture()->attach_texture();
            phong_mat->specular_mask_texture()->attach_texture();

            auto &als = m_light_settings->ambient_lights();
            auto &dls = m_light_settings->directional_lights();
            auto &pls = m_light_settings->point_lights();
            auto &spls = m_light_settings->spot_lights();

            shader->set_uniform<float>("time", glfwGetTime());
            shader->set_uniform<int>("main_sampler", 0);
            shader->set_uniform<int>("specular_mask_sampler", 1);
            shader->set_uniform_glm<glm::vec4>("material", glm::vec4(phong_mat->ka(), phong_mat->kd(), phong_mat->ks(), phong_mat->shiness()));
            shader->set_uniform_glm<glm::mat4>("model_matrix", mesh->model_matrix());
            shader->set_uniform_glm<glm::mat4>("view_matrix", m_camera->view_matrix());
            shader->set_uniform_glm<glm::mat4>("projection_matrix", m_camera->projection_matrix());
            shader->set_uniform_glm<glm::vec3>("camera_position", m_camera->position());
            auto normal_matrix = glm::mat3(glm::transpose(glm::inverse(mesh->model_matrix())));
            shader->set_uniform_glm<glm::mat3>("normal_matrix", normal_matrix);
            shader->set_uniform_glm<glm::ivec4>("light_count", glm::ivec4((int)als.size(), (int)dls.size(), (int)pls.size(), (int)spls.size()));

            for (int i = 0; i < als.size(); i++) {
                auto &al = als[i];
                al->set_shader_uniform(shader, "ambient_lights", i);
            }

            for (int i = 0; i < dls.size(); i++) {
                auto &dl = dls[i];
                dl->set_shader_uniform(shader, "directional_lights", i);
            }

            for (int i = 0; i < pls.size(); i++) {
                auto &pl = pls[i];
                pl->set_shader_uniform(shader, "point_lights", i);
            }

            for (int i = 0; i < spls.size(); i++) {
                auto &spl = spls[i];
                spl->set_shader_uniform(shader, "spot_lights", i);
            }

            geo->attach_geometry();
            geo->draw();
            geo->detach_geometry();

            phong_mat->main_texture()->detach_texture();
            phong_mat->specular_mask_texture()->detach_texture();

        } else {
            auto white_mat = std::dynamic_pointer_cast<White_material>(mat);

            shader->set_uniform_glm<glm::mat4>("model_matrix", mesh->model_matrix());
            shader->set_uniform_glm<glm::mat4>("view_matrix", m_camera->view_matrix());
            shader->set_uniform_glm<glm::mat4>("projection_matrix", m_camera->projection_matrix());

            geo->attach_geometry();
            geo->draw();
            geo->detach_geometry();
        }

        shader->detach_program();
    }
}

std::shared_ptr<Shader_program> Renderer::pick_shader(Material::Material_type type) {
    if (type == Material::Material_type::PHONG) 
        return m_phong_shader;
    else 
        return m_white_shader;
}
