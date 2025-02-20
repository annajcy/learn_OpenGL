#include "renderer.h"

Renderer::Renderer(const std::shared_ptr<Scene> &scene, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) 
    : m_scene(scene), m_camera(camera), m_light_settings(light_setting) { }

std::shared_ptr<Scene>& Renderer::scene() { return m_scene; }
std::shared_ptr<Camera>& Renderer::camera() { return m_camera; }
std::shared_ptr<Light_setting>& Renderer::light_setting() { return m_light_settings; }

std::vector<std::shared_ptr<Mesh>> Renderer::opaque_meshes{};
std::vector<std::shared_ptr<Mesh>> Renderer::albedo_meshes{};

void Renderer::set_clear_color(const glm::vec3& color) {
    glClearColor(color.r, color.g, color.b, 1.0f);
}

void Renderer::init_state() {
    Depth_test_setting::reset_to_default();
    Polygon_offset_setting::reset_to_default();
    Stencil_test_setting::reset_to_default();
    Color_blend_setting::reset_to_default();
}

void Renderer::clear() {
    init_state();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::render_mesh(const std::shared_ptr<Mesh>& mesh) {

    mesh->material()->depth_test_setting().apply();
    mesh->material()->polygon_offset_setting().apply();
    mesh->material()->stencil_test_setting().apply();
    mesh->material()->color_blend_setting().apply();

    mesh->material()->shader()->attach_program();
    mesh->material()->update_uniform(mesh, m_camera, m_light_settings);

    mesh->draw();

    mesh->material()->shader()->detach_program();
}

void Renderer::set_render_list(const std::shared_ptr<Node>& node) {
    if (node == nullptr) return;

    if (node->type() == Node::Node_type::MESH) {
        auto mesh = std::dynamic_pointer_cast<Mesh>(node);
        if (mesh->material()->color_blend_setting().enable) {
            opaque_meshes.push_back(mesh);
        } else {
            albedo_meshes.push_back(mesh);
        }
    }

    for (int i = 0; i < node->children().size(); i ++) {
        set_render_list(node->children()[i]);
    }
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

    opaque_meshes.clear();
    albedo_meshes.clear();

    set_render_list(m_scene);

    std::sort(
        opaque_meshes.begin(),
        opaque_meshes.end(),
        [&](const std::shared_ptr<Mesh>& a, const std::shared_ptr<Mesh>& b) {
            auto view_matrix = m_camera->view_matrix();
            
            auto cam_pos_a = view_matrix * a->model_matrix() * glm::vec4(0.0, 0.0, 0.0, 1.0);
            auto cam_pos_b = view_matrix * b->model_matrix() * glm::vec4(0.0, 0.0, 0.0, 1.0);

            return cam_pos_a.z < cam_pos_b.z;
        }  
    );

    for (auto &mesh : albedo_meshes) {
        render_mesh(mesh);
    }

    for (auto &mesh : opaque_meshes) {
        render_mesh(mesh);
    }

    //render_node(m_scene);
}

