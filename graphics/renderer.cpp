#include "renderer.h"

Renderer::Renderer(const std::shared_ptr<Scene> &scene, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) 
    : m_scene(scene), m_camera(camera), m_light_settings(light_setting), 
      m_phong_shader(Shader_program::create_vs_fs_program("assets/shaders/phong/phong.vert", "assets/shaders/phong/phong.frag")), 
      m_white_shader(Shader_program::create_vs_fs_program("assets/shaders/white/white.vert", "assets/shaders/white/white.frag")) { }

std::shared_ptr<Scene>& Renderer::scene() { return m_scene; }
std::shared_ptr<Camera>& Renderer::camera() { return m_camera; }
std::shared_ptr<Light_setting>& Renderer::light_setting() { return m_light_settings; }

void Renderer::set_clear_color(const glm::vec3& color) {
    glClearColor(color.r, color.g, color.b, 1.0f);
}

void Renderer::init_state() {
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render_mesh(const std::shared_ptr<Mesh>& mesh) {
    auto shader = pick_shader(mesh->material()->type());
    shader->attach_program();

    // Update uniforms
    if (mesh->material()->type() == Material::Material_type::PHONG) {

        update_phong_shader_uniform(shader, mesh);

        auto phong_mat = std::dynamic_pointer_cast<Phong_material>(mesh->material());

        phong_mat->main_texture()->attach_texture();
        phong_mat->specular_mask_texture()->attach_texture();

        if (phong_mat->depth_test()) {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(phong_mat->depth_function());
        } else {
            glDisable(GL_DEPTH_TEST);
        }

        if (phong_mat->depth_write()) glDepthMask(GL_TRUE);
		else glDepthMask(GL_FALSE);
	
        mesh->geometry()->attach_geometry();
        mesh->geometry()->draw();
        mesh->geometry()->detach_geometry();

        phong_mat->main_texture()->detach_texture();
        phong_mat->specular_mask_texture()->detach_texture();

    } else {

        update_white_shader_uniform(shader, mesh);

        mesh->geometry()->attach_geometry();
        mesh->geometry()->draw();
        mesh->geometry()->detach_geometry();
    }

    shader->detach_program();
}

void Renderer::render_node(const std::shared_ptr<Node>& node) {

    if (node == nullptr) return;

    if (node->type() == Node::Node_type::MESH) {
        render_mesh(std::dynamic_pointer_cast<Mesh>(node));
    }

    if (node->children().empty()) return;

    for (auto &child : node->children()) {
        render_node(child);
    }

}

void Renderer::render() {
    if (!m_camera || !m_light_settings || !m_scene) {
        std::cout << "invalid render params" << std::endl;
        return;
    }

    render_node(m_scene);
}

std::shared_ptr<Shader_program> Renderer::pick_shader(Material::Material_type type) {
    if (type == Material::Material_type::PHONG) return m_phong_shader;
    else return m_white_shader;
}

void Renderer::update_white_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::shared_ptr<Mesh> &mesh) {
    auto &geo = mesh->geometry();
    auto &mat = mesh->material();
    auto white_mat = std::dynamic_pointer_cast<White_material>(mat);

    shader->set_uniform_glm<glm::mat4>("model_matrix", mesh->model_matrix());
    shader->set_uniform_glm<glm::mat4>("view_matrix", m_camera->view_matrix());
    shader->set_uniform_glm<glm::mat4>("projection_matrix", m_camera->projection_matrix());
}

void Renderer::update_phong_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::shared_ptr<Mesh> &mesh) {

    auto &geo = mesh->geometry();
    auto &mat = mesh->material();
    auto phong_mat = std::dynamic_pointer_cast<Phong_material>(mat);

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

}
