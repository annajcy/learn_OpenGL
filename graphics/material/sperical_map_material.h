#pragma once

#include "material.h"
#include "graphics/texture.h"

class Sperical_map_material : public Material
{

private:
    std::shared_ptr<Texture> m_sperical_map;
public:
    std::shared_ptr<Texture>& sperical_map() { return m_sperical_map; }

public:
    Sperical_map_material() : Material(Material_type::SPERICAL_MAP, Shader_program::create_shader_program("assets/shaders/skybox/sperical_map/sperical_map.vert", "assets/shaders/skybox/sperical_map/sperical_map.frag")) {
        m_depth_test_setting = Depth_test_setting::disable_write_setting();
        m_depth_test_setting.depth_test_function = Depth_test_setting::Depth_test_function::LEQUAL;
        m_sperical_map = Texture::create_texture_from_path("assets/image/bk.jpg", 0, "assets/image/bk.jpg");
    }
    
    ~Sperical_map_material() override = default;

    void update_uniform(const std::shared_ptr<Node>& node, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) override {
        m_shader->set_uniform_glm<glm::mat4>("model_matrix", glm::translate(glm::identity<glm::mat4>(), camera->position()));
        m_shader->set_uniform_glm<glm::mat4>("view_matrix", camera->view_matrix());
        m_shader->set_uniform_glm<glm::mat4>("projection_matrix", camera->projection_matrix());
        m_shader->set_uniform<int>("sperical_map_sampler", 0);
    }

    void before_geometry_draw() override {
        m_sperical_map->attach_texture();
    }

    void after_geometry_draw() override {
        m_sperical_map->detach_texture();
    }

};


