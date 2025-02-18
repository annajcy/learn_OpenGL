#include "renderer.h"

Renderer::Renderer(const std::shared_ptr<Scene> &scene, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) 
    : m_scene(scene), m_camera(camera), m_light_settings(light_setting) { }

std::shared_ptr<Scene>& Renderer::scene() { return m_scene; }
std::shared_ptr<Camera>& Renderer::camera() { return m_camera; }
std::shared_ptr<Light_setting>& Renderer::light_setting() { return m_light_settings; }

void Renderer::set_clear_color(const glm::vec3& color) {
    glClearColor(color.r, color.g, color.b, 1.0f);
}

void Renderer::init_state() {
    Depth_test_setting::reset_to_default();
    Polygon_offset_setting::reset_to_default();
    Stencil_test_setting::reset_to_default();
}

void Renderer::clear() {
    init_state();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::render_mesh(const std::shared_ptr<Mesh>& mesh) {

    mesh->material()->depth_test_setting().apply();
    mesh->material()->polygon_offset_setting().apply();
    mesh->material()->stencil_test_setting().apply();

    mesh->material()->shader()->attach_program();
    mesh->material()->update_uniform(mesh, m_camera, m_light_settings);

    // Update uniforms
    if (mesh->material()->type() == Material::Material_type::PHONG) {

        auto phong_mat = std::dynamic_pointer_cast<Phong_material>(mesh->material());

        phong_mat->main_texture()->attach_texture();
        phong_mat->specular_mask_texture()->attach_texture();
	
        mesh->geometry()->attach_geometry();
        mesh->geometry()->draw();
        mesh->geometry()->detach_geometry();

        phong_mat->main_texture()->detach_texture();
        phong_mat->specular_mask_texture()->detach_texture();

    } else if (mesh->material()->type() == Material::Material_type::EDGE) {

        mesh->geometry()->attach_geometry();
        mesh->geometry()->draw();
        mesh->geometry()->detach_geometry();
    } else {

        mesh->geometry()->attach_geometry();
        mesh->geometry()->draw();
        mesh->geometry()->detach_geometry();
        
    }

    mesh->material()->shader()->detach_program();
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

